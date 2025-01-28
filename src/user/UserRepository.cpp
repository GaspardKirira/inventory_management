#include "UserRepository.hpp"

namespace Softadastra
{
    void UserRepository::saveUser(const User &user)
    {
        spdlog::warn("User created successfull !");
        std::cout << "**********************************" << std::endl;
        user.displayInfo();
        std::cout << "**********************************" << std::endl;
    }

    UserRepository::~UserRepository()
    {
        spdlog::warn("UserRepository Destroyed !");
    }
} // namespace Softadastra
