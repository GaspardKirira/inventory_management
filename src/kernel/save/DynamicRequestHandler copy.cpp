#include "DynamicRequestHandler.hpp"
#include <spdlog/spdlog.h> // Ajout de spdlog pour les logs
#include <regex>           // Ajout pour la validation avec std::regex

Softadastra::DynamicRequestHandler::DynamicRequestHandler(
    std::function<void(const std::unordered_map<std::string, std::string> &,
                       http::response<http::string_body> &)>
        handler)
    : params_(), handler_(std::move(handler)) // Inverser l'ordre des initialisations
{
    spdlog::info("DynamicRequestHandler initialized.");
}

void Softadastra::DynamicRequestHandler::handle_request(const http::request<http::string_body> &,
                                                        http::response<http::string_body> &res)
{
    spdlog::info("Handling request with parameters: {}", params_.empty() ? "None" : "Available");
    // Vérifier si handler_ est valide avant de l'utiliser
    if (handler_)
    {
        handler_(params_, res); // Utiliser params_ pour l'accès aux paramètres dynamiques
    }
    else
    {
        spdlog::error("Handler is invalid or null.");
        // Retourner une erreur ou prendre d'autres mesures selon ton design
        res.result(http::status::internal_server_error);
        res.body() = "Internal server error: handler is invalid.";
    }
}

void Softadastra::DynamicRequestHandler::set_params(const std::unordered_map<std::string, std::string> &params)
{
    spdlog::info("Validating and setting parameters in DynamicRequestHandler...");

    // Validation des paramètres dynamiques
    for (const auto &[key, value] : params)
    {
        if (key == "id")
        {
            if (!std::regex_match(value, std::regex("^[0-9]+$")))
            {
                spdlog::warn("Invalid 'id' parameter: {}", value);
                throw std::invalid_argument("Invalid parameter value for 'id'. Must be a positive integer.");
            }
        }
        else if (key == "slug")
        {
            if (!std::regex_match(value, std::regex("^[a-zA-Z0-9_-]+$")))
            {
                spdlog::warn("Invalid 'slug' parameter: {}", value);
                throw std::invalid_argument("Invalid parameter value for 'slug'. Must be alphanumeric with hyphens or underscores.");
            }
        }
        else
        {
            spdlog::warn("Unknown parameter: {}", key);
        }
    }

    params_ = params; // Mise à jour des paramètres après validation
    spdlog::info("Parameters set successfully: {}", params.size());
}
