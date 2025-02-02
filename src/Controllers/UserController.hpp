#ifndef USERROUTES_HPP
#define USERROUTES_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include "Controller.hpp"
#include "../user/UserRepository.hpp"
#include "../user/User.hpp"

namespace Softadastra
{
    class UserController : public Controller
    {
    public:
        UserController(const UserRepository &user_repository)
            : m_user_repository(user_repository) {}

        void configure(Router &router) override
        {
            // Route GET pour récupérer un utilisateur par ID
            router.add_route(http::verb::get, "/users/{id}",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<DynamicRequestHandler>(
                                     [this](const std::unordered_map<std::string, std::string> &params,
                                            http::response<http::string_body> &res)
                                     {
                                         try
                                         {
                                             std::string user_id = params.at("id");
                                             int id = std::stoi(user_id); // Conversion en int

                                             std::shared_ptr<User> user = m_user_repository.find(id);

                                             // Renvoi des détails utilisateur au format JSON
                                             res.result(http::status::ok);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"id", id}, {"full_name", user->getFullName()}}.dump();
                                         }
                                         catch (const std::exception &e)
                                         {
                                             res.result(http::status::not_found);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "User not found"}}.dump();
                                         }
                                     })));

            // Route GET pour récupérer tous les utilisateurs
            router.add_route(http::verb::get, "/users",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<DynamicRequestHandler>(
                                     [this](const std::unordered_map<std::string, std::string> &,
                                            http::response<http::string_body> &res)
                                     {
                                         try
                                         {
                                             std::vector<User> users = m_user_repository.findAll();

                                             // Renvoi de la liste des utilisateurs au format JSON
                                             res.result(http::status::ok);
                                             res.set(http::field::content_type, "application/json");
                                             nlohmann::json json_users = nlohmann::json::array();
                                             for (const auto &user : users)
                                             {
                                                 json_users.push_back({{"id", user.getId()}, {"full_name", user.getFullName()}});
                                             }
                                             res.body() = json_users.dump();
                                         }
                                         catch (const std::exception &e)
                                         {
                                             res.result(http::status::internal_server_error);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "Error fetching users"}}.dump();
                                         }
                                     })));

            // Route POST pour créer un utilisateur (exemple de création d'un utilisateur)
            router.add_route(http::verb::post, "/users",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<DynamicRequestHandler>(
                                     [this](const std::unordered_map<std::string, std::string> &,
                                            http::response<http::string_body> &res)
                                     {
                                         try
                                         {
                                             std::string full_name = "New User";
                                             std::shared_ptr<Email> email = std::make_shared<Email>("user@example.com");
                                             std::shared_ptr<Phone> phone = std::make_shared<Phone>("123456789");
                                             std::shared_ptr<Password> password = std::make_shared<Password>("hashed_password");

                                             User new_user(full_name, email, phone, password);

                                             // Sauvegarder l'utilisateur dans la base de données
                                             m_user_repository.saveUser(new_user);

                                             res.result(http::status::created);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "User created successfully"}}.dump();
                                         }
                                         catch (const std::exception &e)
                                         {
                                             res.result(http::status::bad_request);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "Error creating user"}}.dump();
                                         }
                                     })));

            // Route PUT pour mettre à jour un utilisateur
            router.add_route(http::verb::put, "/users/{id}",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<DynamicRequestHandler>(
                                     [this](const std::unordered_map<std::string, std::string> &params,
                                            http::response<http::string_body> &res)
                                     {
                                         try
                                         {
                                             std::string user_id = params.at("id");
                                             int id = std::stoi(user_id);

                                             // Ici, vous récupérez les données de la requête et les utilisez pour mettre à jour l'utilisateur
                                             // Exemple simplifié d'une mise à jour de "full_name"
                                             std::string updated_full_name = "Updated User Name";

                                             std::shared_ptr<User> updated_user = m_user_repository.find(id);
                                             updated_user->setFullName(updated_full_name);

                                             // Mettre à jour l'utilisateur dans la base de données
                                             m_user_repository.update(id, *updated_user);

                                             res.result(http::status::ok);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "User updated successfully"}}.dump();
                                         }
                                         catch (const std::exception &e)
                                         {
                                             res.result(http::status::not_found);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "User not found"}}.dump();
                                         }
                                     })));

            // Route DELETE pour supprimer un utilisateur
            router.add_route(http::verb::get, "/users/{id}",
                             std::static_pointer_cast<IRequestHandler>(
                                 std::make_shared<DynamicRequestHandler>(
                                     [this](const std::unordered_map<std::string, std::string> &params,
                                            http::response<http::string_body> &res)
                                     {
                                         try
                                         {
                                             std::string user_id = params.at("id");
                                             int id = std::stoi(user_id);

                                             // Supprimer l'utilisateur de la base de données
                                             m_user_repository.deleteUser(id);

                                             res.result(http::status::ok);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "User deleted successfully"}}.dump();
                                         }
                                         catch (const std::exception &e)
                                         {
                                             res.result(http::status::not_found);
                                             res.set(http::field::content_type, "application/json");
                                             res.body() = json{{"message", "User not found"}}.dump();
                                         }
                                     })));
        }

    private:
        UserRepository m_user_repository; // Assurez-vous d'instancier votre repository ici
    };
}

#endif // USERROUTES_HPP
