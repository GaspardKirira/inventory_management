#include "DynamicRequestHandler.hpp"

Softadastra::DynamicRequestHandler::DynamicRequestHandler(
    std::function<void(const std::unordered_map<std::string, std::string> &,
                       http::response<http::string_body> &)>
        handler)
    : params_(), handler_(std::move(handler)) // Inverser l'ordre des initialisations
{
}

void Softadastra::DynamicRequestHandler::handle_request(const http::request<http::string_body> &,
                                                        http::response<http::string_body> &res)
{
    handler_(params_, res); // Utiliser params_ pour l'accès aux paramètres dynamiques
}

void Softadastra::DynamicRequestHandler::set_params(
    const std::unordered_map<std::string, std::string> &params)
{
    params_ = params; // Mise à jour des paramètres
}
