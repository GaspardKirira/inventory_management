#ifndef HOMEROUTES_HPP
#define HOMEROUTES_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <ctime>
#include "Controller.hpp"

#include "../user/User.hpp"
#include "../user/UserService.hpp"
#include "../user/UserRepository.hpp"
#include "../config/Config.hpp"

using json = nlohmann::json;

namespace Softadastra
{
    class HomeController : public Controller
    {
    public:
        void configure(Router &routes) override
        {
            routes.add_route(
                http::verb::get, "/",
                std::static_pointer_cast<IRequestHandler>(
                    std::make_shared<SimpleRequestHandler>(
                        [](const http::request<http::string_body> &req,
                           http::response<http::string_body> &res)
                        {
                            // Définir la version de HTTP de la réponse
                            res.version(req.version());

                            // Définir le statut de la réponse à 200 OK
                            res.result(http::status::ok);

                            // Définir l'en-tête Content-Type en application/json
                            res.set(http::field::content_type, "application/json");

                            // Ajouter l'en-tête Server
                            res.set(http::field::server, "Softadastra/master");

                            // Générer la date actuelle au format HTTP (RFC 1123)
                            auto now = std::chrono::system_clock::now();
                            std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
                            std::tm tm = *std::gmtime(&now_time_t);

                            std::ostringstream oss;
                            oss << std::put_time(&tm, "%a, %d %b %Y %H:%M:%S GMT");
                            std::string date = oss.str();

                            // Ajouter l'en-tête Date avec la date dynamique
                            res.set(http::field::date, date);

                            // Remplir le corps de la réponse avec un message JSON
                            res.body() = json{{"message", "Welcome to the Softadastra HTTP Server"}}.dump();
                        })));

            // Gestion de la méthode OPTIONS avant la méthode POST
            routes.add_route(http::verb::options, "/create",
                             std::static_pointer_cast<IRequestHandler>(std::make_shared<SimpleRequestHandler>(
                                 [](const http::request<http::string_body> &req, http::response<http::string_body> &res)
                                 {
                                     // Réponse vide avec les en-têtes CORS
                                     res.result(http::status::no_content);
                                     res.set(http::field::access_control_allow_origin, "*");              // Permet toutes les origines (ajuste si nécessaire)
                                     res.set(http::field::access_control_allow_methods, "POST, OPTIONS"); // Autorise les méthodes POST et OPTIONS
                                     res.set(http::field::access_control_allow_headers, "Content-Type");  // Autorise l'en-tête Content-Type
                                 })));

            routes.add_route(http::verb::post, "/create",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<SimpleRequestHandler>(
                                     [](const http::request<http::string_body> &req, http::response<http::string_body> &res)
                                     {
                                         // Vérification si le corps de la requête est vide
                                         if (req.body().empty())
                                         {
                                             res.result(http::status::bad_request);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "Missing request body."}}.dump();
                                             return;
                                         }

                                         try
                                         {
                                             // Tentative de parsing du corps en JSON
                                             auto json_data = json::parse(req.body());

                                             // Validation des champs nécessaires avec messages d'erreur spécifiques
                                             if (json_data.find("full_name") == json_data.end())
                                             {
                                                 res.result(http::status::bad_request);
                                                 res.set(http::field::content_type, "application/json");
                                                 res.body() = json{{"message", "Le champ 'full_name' est manquant."}}.dump();
                                                 return;
                                             }

                                             if (json_data.find("email") == json_data.end())
                                             {
                                                 res.result(http::status::bad_request);
                                                 res.set(http::field::content_type, "application/json");
                                                 res.body() = json{{"message", "Le champ 'email' est manquant."}}.dump();
                                                 return;
                                             }

                                             if (json_data.find("phone") == json_data.end())
                                             {
                                                 res.result(http::status::bad_request);
                                                 res.set(http::field::content_type, "application/json");
                                                 res.body() = json{{"message", "Le champ 'phone' est manquant."}}.dump();
                                                 return;
                                             }

                                             if (json_data.find("password") == json_data.end())
                                             {
                                                 res.result(http::status::bad_request);
                                                 res.set(http::field::content_type, "application/json");
                                                 res.body() = json{{"message", "Le champ 'password' est manquant."}}.dump();
                                                 return;
                                             }

                                             if (json_data.find("company") == json_data.end())
                                             {
                                                 res.result(http::status::bad_request);
                                                 res.set(http::field::content_type, "application/json");
                                                 res.body() = json{{"message", "Le champ 'company' est manquant."}}.dump();
                                                 return;
                                             }

                                             // Récupération des données et création des objets
                                             std::string m_full_name = json_data["full_name"];
                                             std::string m_email = json_data["email"];
                                             std::string m_phone = json_data["phone"];
                                             std::string m_password = json_data["password"];
                                             std::string m_company = json_data["company"];

                                             auto email = std::make_shared<Email>(m_email);
                                             auto phone = std::make_shared<Phone>(m_phone);
                                             auto password = std::make_shared<Password>(m_password);
                                             auto company = std::make_shared<Company>(m_company);

                                             // Chargement de la configuration
                                             Config &config = Config::getInstance();
                                             config.loadConfig();

                                             // Enregistrement de l'utilisateur dans la base de données
                                             UserRepository repo(config);
                                             UserService service(repo);
                                             service.createUser(m_full_name, email, phone, password, company);

                                             // Réponse de succès
                                             res.result(http::status::ok);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "Utilisateur enregistré avec succès dans la base de données."}}.dump();
                                         }
                                         catch (const std::exception &e)
                                         {
                                             // Gestion des erreurs génériques
                                             res.result(http::status::internal_server_error);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", std::string("Erreur lors du traitement de la requête : ") + e.what()}}.dump();
                                         }
                                     })));
        }
    };
} // namespace Softadastra

#endif // HOMEROUTES_HPP
