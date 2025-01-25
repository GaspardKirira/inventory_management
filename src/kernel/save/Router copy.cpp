#include "DynamicRequestHandler.hpp"
#include "Router.hpp"

void Softadastra::Router::add_route(http::verb method, const std::string &route, std::shared_ptr<IRequestHandler> handler)
{
    routes_[{method, route}] = std::move(handler);
}

bool Softadastra::Router::handle_request(const http::request<http::string_body> &req, http::response<http::string_body> &res)
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

bool Softadastra::Router::matches_dynamic_route(const std::string &route_pattern, const std::string &path, std::shared_ptr<IRequestHandler> handler, http::response<http::string_body> &res)
{
    // Créer des copies locales des chaînes pour éviter des accès après libération
    std::string path_copy = path;
    std::string route_pattern_copy = route_pattern;

    // Convertir le modèle de route en regex
    std::string regex_pattern = convert_route_to_regex(route_pattern_copy);
    boost::regex dynamic_route(regex_pattern);
    boost::smatch match;

    // Vérifier la correspondance avec le chemin
    if (boost::regex_match(path_copy, match, dynamic_route))
    {
        std::unordered_map<std::string, std::string> params;

        // Utiliser une regex pour extraire les paramètres dynamiques du modèle de route
        boost::regex param_regex("\\{(\\w+)\\}");
        boost::sregex_iterator begin(route_pattern_copy.begin(), route_pattern_copy.end(), param_regex), end;

        int i = 1;
        for (auto it = begin; it != end; ++it)
        {
            params[it->str(1)] = match[i++].str();
        }

        // Valider les paramètres extraits
        if (!validate_params(params, res))
        {
            return false;
        }

        // Assurer-toi que le handler est valide
        if (auto dynamic_handler = std::dynamic_pointer_cast<DynamicRequestHandler>(handler))
        {
            dynamic_handler->set_params(params); // Utilisation du handler dynamique
        }
        else
        {
            spdlog::error("Handler is not of type DynamicRequestHandler.");
            return false;
        }

        // Préparer la réponse avec les paramètres extraits
        res.set(http::field::content_type, "application/json");
        res.body() = json{{"message", "Dynamic route matched."}, {"params", params}}.dump();

        return true;
    }

    return false;
}

std::string Softadastra::Router::convert_route_to_regex(const std::string &route)
{
    std::string regex = "^";
    boost::regex param_regex("\\{(\\w+)\\}"); // Capture les paramètres nommés {id}, {slug}, etc.
    boost::smatch match;

    size_t start = 0;
    while (boost::regex_search(route.substr(start), match, param_regex))
    {
        if (match.empty())
        {
            break;
        }

        regex += route.substr(start, match.position());
        std::string param_name = match[1].str();

        // Mapper les types de paramètres nommés à des expressions régulières spécifiques
        if (param_name == "id")
        {
            regex += "(\\d+)";
        }
        else if (param_name == "slug")
        {
            regex += "([\\w-]+)";
        }
        else if (param_name == "uuid")
        {
            regex += "([a-fA-F0-9\\-]+)";
        }
        else if (param_name == "date")
        {
            regex += "(\\d{4}-\\d{2}-\\d{2})";
        }
        else
        {
            throw std::invalid_argument("Unknown parameter type: " + param_name);
        }

        start += match.position() + match.length();
    }

    regex += route.substr(start);
    regex += "$";

    return regex;
}

bool Softadastra::Router::validate_params(const std::unordered_map<std::string, std::string> &params, http::response<http::string_body> &res)
{
    for (const auto &[key, value] : params)
    {
        if (key == "id")
        {
            if (!std::all_of(value.begin(), value.end(), ::isdigit))
            {
                res.result(http::status::bad_request);
                res.body() = json{{"error", "Invalid parameter: 'id' must be numeric"}}.dump();
                return false;
            }
        }
        else if (key == "date")
        {
            boost::regex date_regex("\\d{4}-\\d{2}-\\d{2}");
            if (!boost::regex_match(value, date_regex))
            {
                res.result(http::status::bad_request);
                res.body() = json{{"error", "Invalid parameter: 'date' must be in YYYY-MM-DD format"}}.dump();
                return false;
            }
        }
    }

    return true;
}