#include "User.hpp"
#include <iostream>
#include <memory>

int main()
{
    try
    {
        // Création des objets validés pour un utilisateur complet
        auto emailComplete = std::make_shared<Email>("john.doe@example.com");
        auto phoneComplete = std::make_shared<Phone>("123-456-7890");
        auto companyComplete = std::make_shared<Company>("TechCorpsofftadastrakiriragaspard");
        auto locationComplete = std::make_shared<Location>(1, 2, 3); // Exemple : Country, Currency, Language

        // Création d'un utilisateur COMPLET avec toutes les informations
        User userComplete("John Doe", companyComplete, emailComplete, phoneComplete, locationComplete);

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
