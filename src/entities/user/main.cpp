#include "User.hpp"
#include <iostream>
#include <memory>

using namespace Softadastra;

int main3()
{
    try
    {
        // Création des objets validés pour un utilisateur complet
        auto emailComplete = std::make_shared<Email>("john.doe@example.com");
        auto phoneComplete = std::make_shared<Phone>("1234567890");
        auto companyComplete = std::make_shared<Company>("Tech corps");
        auto locationComplete = std::make_shared<Location>(1, 2, 3);
        auto password = std::make_shared<Password>("gaspard");

        // Création d'un utilisateur COMPLET avec toutes les informations
        User userComplete("John Doe", companyComplete, emailComplete, phoneComplete, password, locationComplete);

        std::cout << "--- User Complete ---" << std::endl;
        userComplete.displayInfo();

        std::cout << "\n--- Creating User without Company and Location ---" << std::endl;

        // Création d'un utilisateur INCOMPLET sans spécifier de Company et Location
        User userIncomplete("Jane Doe", nullptr, emailComplete, phoneComplete);

        userIncomplete.displayInfo();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
