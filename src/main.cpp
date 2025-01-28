#include "user/User.hpp"
#include <iostream>
#include <memory>
#include "user/UserService.hpp"
#include "user/UserRepository.hpp"

using namespace Softadastra;

int main()
{
    try
    {
        std::string full_name{"Gaspard"};
        auto email = std::make_shared<Email>("gaspard@gmail.com");
        auto phone = std::make_shared<Phone>("256783345232");
        auto password = std::make_shared<Password>("Adastra2022+");
        auto company = std::make_shared<Company>("Tech corp");

        // Créer un utilisateur
        UserRepository repo;
        UserService service(repo);

        service.createUser(full_name, email, phone, password, company);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
