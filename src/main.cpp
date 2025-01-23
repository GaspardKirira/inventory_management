#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <iostream>
#include <thread>
#include <memory>
#include <functional>
#include <spdlog/spdlog.h>
#include "Config.hpp"

namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace net = boost::asio;

using tcp = net::ip::tcp;
using ssl_socket = boost::asio::ssl::stream<tcp::socket>;
using json = nlohmann::json;

constexpr size_t MAX_REQUEST_SIZE = 8192; // Limite de taille de la requête

struct PairHash
{
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Combine les hashs de manière simple
    }
};

// Interface pour les gestionnaires de route HTTP
class IRequestHandler
{
public:
    virtual void handle_request(const http::request<http::string_body> &req,
                                http::response<http::string_body> &res) = 0;
    virtual ~IRequestHandler() = default;
};

// Gestionnaire de route simple
class SimpleRequestHandler : public IRequestHandler
{
public:
    explicit SimpleRequestHandler(std::function<void(const http::request<http::string_body> &,
                                                     http::response<http::string_body> &)>
                                      handler)
        : handler_(std::move(handler)) {}

    void handle_request(const http::request<http::string_body> &req,
                        http::response<http::string_body> &res) override
    {
        handler_(req, res);
    }

private:
    std::function<void(const http::request<http::string_body> &,
                       http::response<http::string_body> &)>
        handler_;
};

// Routeur responsable de l'acheminement des requêtes vers les bons gestionnaires
class Router
{
public:
    using RouteKey = std::pair<http::verb, std::string>;

    // Initialisation de routes_ dans la liste d'initialisation du constructeur
    Router() : routes_() {}

    void add_route(http::verb method, const std::string &route, std::shared_ptr<IRequestHandler> handler)
    {
        routes_[{method, route}] = std::move(handler);
    }

    bool handle_request(const http::request<http::string_body> &req,
                        http::response<http::string_body> &res)
    {
        RouteKey key = {req.method(), std::string(req.target())};
        auto it = routes_.find(key);
        if (it != routes_.end())
        {
            it->second->handle_request(req, res);
            return true;
        }
        return false;
    }

private:
    std::unordered_map<RouteKey, std::shared_ptr<IRequestHandler>, PairHash> routes_;
};

// Classe pour envoyer la réponse HTTP
class ResponseSender
{
public:
    static void send(tcp::socket &socket, http::response<http::string_body> &res)
    {
        http::write(socket, res);
    }

    static void send_error(tcp::socket &socket, const std::string &error_message)
    {
        http::response<http::string_body> res;
        res.result(http::status::bad_request);
        res.set(http::field::content_type, "application/json");
        res.body() = json{{"message", error_message}}.dump();
        send(socket, res);
    }
};

// Classe pour la gestion de la session avec le client
class Session
{
public:
    explicit Session(tcp::socket socket, Router &router)
        : socket_(std::move(socket)), router_(router) {}

    void run()
    {
        try
        {
            beast::flat_buffer buffer{8060};
            http::request<http::string_body> req;
            http::read(socket_, buffer, req);

            // Vérification de la taille de la requête
            if (req.body().size() > MAX_REQUEST_SIZE)
            {
                ResponseSender::send_error(socket_, "Request too large");
                return;
            }

            http::response<http::string_body> res;
            if (!router_.handle_request(req, res))
            {
                ResponseSender::send_error(socket_, "Route not found");
            }
            else
            {
                ResponseSender::send(socket_, res);
            }
        }
        catch (const std::exception &e)
        {
            spdlog::error("Error during session: {}", e.what());
            ResponseSender::send_error(socket_, "Session Error: " + std::string(e.what()));
        }
    }

private:
    tcp::socket socket_;
    Router &router_;
};

// Classe principale du serveur
class HTTPServer
{
public:
    explicit HTTPServer(Config &config)
        : config_(config),
          io_context_(std::make_unique<net::io_context>()),
          acceptor_(std::make_unique<tcp::acceptor>(*io_context_,
                                                    tcp::endpoint(tcp::v4(), static_cast<unsigned short>(config_.getServerPort())))) {}

    void run()
    {
        Router router;

        // Routes d'exemple
        router.add_route(http::verb::get, "/", std::make_shared<SimpleRequestHandler>([](const auto &, auto &res)
                                                                                      {
                res.result(http::status::ok);
                res.set(http::field::content_type, "application/json");
                res.body() = json{{"message", "home page"}}.dump(); }));

        router.add_route(http::verb::get, "/hello", std::make_shared<SimpleRequestHandler>([](const auto &, auto &res)
                                                                                           {
                res.result(http::status::ok);
                res.set(http::field::content_type, "application/json");
                res.body() = json{{"message", "hello page"}}.dump(); }));

        spdlog::info("Server started on port {}", config_.getServerPort());
        spdlog::info("Waiting for incoming connections...");

        while (true)
        {
            tcp::socket socket{*io_context_};
            acceptor_->accept(socket);
            spdlog::info("Client connected!");
            std::thread{&HTTPServer::handle_client, this, std::move(socket), std::ref(router)}.detach();
        }
    }

private:
    void handle_client(tcp::socket socket, Router &router)
    {
        Session(std::move(socket), router).run();
    }

    Config &config_;
    std::unique_ptr<net::io_context> io_context_;
    std::unique_ptr<tcp::acceptor> acceptor_;
};

int main()
{
    try
    {
        // Chargement de la configuration
        Config &config = Config::getInstance();
        config.loadConfig();

        HTTPServer server(config);
        server.run();
    }
    catch (const std::exception &e)
    {
        spdlog::error("Critical error: {}", e.what());
    }

    return 0;
}
