#include "RouteConfigurator.hpp"

namespace Softadastra
{

    RouteConfigurator::RouteConfigurator(Router &router)
        : router_(router)
    {
    }

    void RouteConfigurator::configure_routes()
    {
        // Configurer les routes ici
        router_.add_route(http::verb::get, "/", std::make_shared<SimpleRequestHandler>([](const auto &, auto &res)
                                                                                       {
        res.result(http::status::ok);
        res.set(http::field::content_type, "application/json");
        res.body() = json{{"message", "home page"}}.dump(); }));

        router_.add_route(http::verb::get, "/users/{id}",
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

        // Ajouter d'autres routes...

        // Route pour "/products/{id}" : attend un entier
        router_.add_route(http::verb::get, "/products/{id}",
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

        router_.add_route(http::verb::get, "/products/{slug}",
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

        router_.add_route(http::verb::get, "/products/{id}/{slug}",
                          std::static_pointer_cast<IRequestHandler>(
                              std::make_shared<DynamicRequestHandler>(
                                  [](const std::unordered_map<std::string, std::string> &params,
                                     http::response<http::string_body> &res)
                                  {
                                      try
                                      {
                                          std::string product_id = params.at("id");
                                          std::string product_slug = params.at("slug");

                                          res.result(http::status::ok);
                                          res.set(http::field::content_type, "application/json");
                                          res.body() = json{{"message", "Product details for id: " + product_id + " and slug: " + product_slug}}.dump();
                                      }
                                      catch (const std::out_of_range &e)
                                      {
                                          throw std::invalid_argument("Missing required parameters: 'id' and/or 'slug'");
                                      }
                                  })));
    }

} // namespace Softadastra
