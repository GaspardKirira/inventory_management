#include "User.hpp"
#include <iostream>
#include <memory>

using namespace Softadastra;

int main()
{
    try
    {
        auto email = std::make_shared<Email>("gaspard@gmail.com");
        auto phone = std::make_shared<Phone>("256783345232");
        // Le mot de passe respecte maintenant les exigences
        auto password = std::make_shared<Password>("Adastra2022+");
        auto company = std::make_shared<Company>("Tech corp");

        // Créer un utilisateur
        User userIncomplete("Gaspard", email, phone, password, company);

        // Affichage des informations
        userIncomplete.displayInfo();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl; // Capture de l'exception si le mot de passe est trop faible
    }

    return 0;
}
