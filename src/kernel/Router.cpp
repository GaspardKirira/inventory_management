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

std::string Softadastra::Router::convert_route_to_regex(const std::string &route)
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
