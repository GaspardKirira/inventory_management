#ifndef USERREPOSITORY_HPP
#define USERREPOSITORY_HPP

#include "IUserRepository.hpp"
#include <spdlog/spdlog.h>

namespace Softadastra
{
    class UserRepository : public IUserRepository
    {
    public:
        void saveUser(const User &user) override;
        ~UserRepository();
    };
} // namespace Softadastra

#endif // USERREPOSITORY_HPP