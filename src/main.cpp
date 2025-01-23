#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <nlohmann/json.hpp>

#include <boost/regex.hpp>
#include <string>

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

class DynamicRequestHandler : public IRequestHandler
{
public:
    explicit DynamicRequestHandler(std::function<void(const std::unordered_map<std::string, std::string> &,
                                                      http::response<http::string_body> &)>
                                       handler)
        : params_(), handler_(std::move(handler)) // Inverser l'ordre des initialisations
    {
    }

    // Implémente la méthode handle_request de IRequestHandler
    void handle_request(const http::request<http::string_body> &,
                        http::response<http::string_body> &res) override
    {
        handler_(params_, res); // Utiliser params_ pour l'accès aux paramètres
    }

    // Méthode pour mettre à jour les paramètres dynamiques
    void set_params(const std::unordered_map<std::string, std::string> &params)
    {
        params_ = params;
    }

private:
    std::unordered_map<std::string, std::string> params_;
    std::function<void(const std::unordered_map<std::string, std::string> &,
                       http::response<http::string_body> &)>
        handler_;
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

    // Initialisation de routes_
    Router() : routes_() {}

    // Ajout d'une route avec des paramètres dynamiques (par ex. /users/{id})
    void add_route(http::verb method, const std::string &route, std::shared_ptr<IRequestHandler> handler)
    {
        routes_[{method, route}] = std::move(handler);
    }

    bool handle_request(const http::request<http::string_body> &req,
                        http::response<http::string_body> &res)
    {
        RouteKey key = {req.method(), std::string(req.target())};

        // Recherche de la route exacte
        auto it = routes_.find(key);
        if (it != routes_.end())
        {
            std::cout << "Exact match found!" << std::endl;
            it->second->handle_request(req, res);
            return true;
        }

        // Recherche de route dynamique
        std::cout << "Exact match not found, trying dynamic routes..." << std::endl;

        for (auto &[route_key, handler] : routes_)
        {
            if (matches_dynamic_route(route_key.second, std::string(req.target()), handler, res))
            {
                return true;
            }
        }

        std::cout << "Route not found" << std::endl;
        return false;
    }

private:
    bool matches_dynamic_route(const std::string &route_pattern, const std::string &path,
                               std::shared_ptr<IRequestHandler> handler, // Ajout du handler
                               http::response<http::string_body> &res)
    {
        std::string regex_pattern = convert_route_to_regex(route_pattern);
        boost::regex dynamic_route(regex_pattern);
        boost::smatch match;

        if (boost::regex_match(path, match, dynamic_route))
        {
            std::unordered_map<std::string, std::string> params;
            params["id"] = match[1].str(); // Utilisation de "id" comme clé

            // Mettre à jour les paramètres dans le gestionnaire de route dynamique
            dynamic_cast<DynamicRequestHandler *>(handler.get())->set_params(params);

            res.set(http::field::content_type, "application/json");
            res.body() = json{{"message", "Dynamic route matched."}, {"params", params}}.dump();

            return true;
        }
        return false;
    }

    std::string convert_route_to_regex(const std::string &route)
    {
        std::string regex = "^";
        bool inside_placeholder = false;

        for (size_t i = 0; i < route.size(); ++i)
        {
            if (route[i] == '{') // Début du paramètre dynamique
            {
                inside_placeholder = true;
                regex += "(\\w+)"; // Capture un mot comme paramètre
            }
            else if (route[i] == '}') // Fin du paramètre dynamique
            {
                inside_placeholder = false;
            }
            else
            {
                // Si nous sommes à l'intérieur d'un paramètre dynamique, on applique une logique spécifique
                if (inside_placeholder)
                {
                    // Par exemple, si le caractère suivant est un '/', on permet cela
                    if (route[i] == '/')
                    {
                        regex += "\\/"; // Ajouter un / dans le regex
                    }
                    // Si le caractère suivant est un '-', on le permet aussi
                    else if (route[i] == '-')
                    {
                        regex += "\\-"; // Ajouter un - dans le regex
                    }
                    else
                    {
                        // Si c'est un autre caractère, on ignore cette partie ou on pourrait lancer une exception
                        std::cerr << "Caractère invalide après un paramètre dynamique : " << route[i] << std::endl;
                    }
                }
                else
                {
                    // Hors des paramètres dynamiques, ajoute simplement le caractère à la regex
                    regex += route[i];
                }
            }
        }

        regex += "$"; // Fin de l'URL
        return regex;
    }

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

        // Route pour la page d'accueil
        router.add_route(http::verb::get, "/", std::make_shared<SimpleRequestHandler>([](const auto &, auto &res)
                                                                                      {
                res.result(http::status::ok);
                res.set(http::field::content_type, "application/json");
                res.body() = json{{"message", "home page"}}.dump(); }));

        router.add_route(http::verb::get, "/users/{id}",
                         std::static_pointer_cast<IRequestHandler>(
                             std::make_shared<DynamicRequestHandler>(
                                 [](const std::unordered_map<std::string, std::string> &params,
                                    http::response<http::string_body> &res)
                                 {
                                     std::string user_id = params.at("id");
                                     res.result(http::status::ok);
                                     res.set(http::field::content_type, "application/json");
                                     res.body() = json{{"message", "User details for id: " + user_id}}.dump();
                                 })));

        // // Faire de même pour l'autre route
        // router.add_route(http::verb::get, "/products/{slug}",
        //                  std::static_pointer_cast<IRequestHandler>(
        //                      std::make_shared<DynamicRequestHandler>(
        //                          [](const std::unordered_map<std::string, std::string> &params,
        //                             http::response<http::string_body> &res)
        //                          {
        //                              std::string product_slug = params.at("slug");
        //                              res.result(http::status::ok);
        //                              res.set(http::field::content_type, "application/json");
        //                              res.body() = json{{"message", "Product details for slug: " + product_slug}}.dump();
        //                          })));

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
