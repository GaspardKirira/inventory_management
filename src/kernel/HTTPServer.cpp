#include "HTTPServer.hpp"

Softadastra::HTTPServer::HTTPServer(Config &config)
    : config_(config),
      io_context_(std::make_unique<net::io_context>()),
      acceptor_(std::make_unique<tcp::acceptor>(*io_context_,
                                                tcp::endpoint(tcp::v4(), static_cast<unsigned short>(config_.getServerPort()))))
{
}

void Softadastra::HTTPServer::run()
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

    // Route pour "/products/{id}" : attend un entier
    router.add_route(http::verb::get, "/products/{id}",
                     std::static_pointer_cast<IRequestHandler>(
                         std::make_shared<DynamicRequestHandler>(
                             [](const std::unordered_map<std::string, std::string> &params,
                                http::response<http::string_body> &res)
                             {
                                 try
                                 {
                                     std::string product_id = params.at("id"); // Assure-toi que 'id' est fourni
                                     res.result(http::status::ok);
                                     res.set(http::field::content_type, "application/json");
                                     res.body() = json{{"message", "Product details for id: " + product_id}}.dump();
                                 }
                                 catch (const std::out_of_range &e)
                                 {
                                     throw std::invalid_argument("Missing required parameter: 'id'");
                                 }
                             })));

    router.add_route(http::verb::get, "/products/{slug}",
                     std::static_pointer_cast<IRequestHandler>(
                         std::make_shared<DynamicRequestHandler>(
                             [](const std::unordered_map<std::string, std::string> &params,
                                http::response<http::string_body> &res)
                             {
                                 try
                                 {
                                     std::string product_slug = params.at("slug"); // Assure-toi que 'slug' est fourni
                                     res.result(http::status::ok);
                                     res.set(http::field::content_type, "application/json");
                                     res.body() = json{{"message", "Product details for slug: " + product_slug}}.dump();
                                 }
                                 catch (const std::out_of_range &e)
                                 {
                                     throw std::invalid_argument("Missing required parameter: 'slug'");
                                 }
                             })));

    spdlog::info("Server started on port {}", config_.getServerPort());
    spdlog::info("Waiting for incoming connections...");

    // Attendre les connexions et créer un thread pour chaque client
    while (true)
    {
        tcp::socket socket{*io_context_};
        acceptor_->accept(socket);
        spdlog::info("Client connected!");
        std::thread{&HTTPServer::handle_client, this, std::move(socket), std::ref(router)}.detach();
    }
}

void Softadastra::HTTPServer::handle_client(tcp::socket socket, Router &router)
{
    Session(std::move(socket), router).run();
}
