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
        auto password = std::make_shared<Password>("1234");
        auto company = std::make_shared<Company>("Tech corp");

        User userIncomplete("Gaspard", email, phone, password, company);

        userIncomplete.displayInfo();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
