#ifndef USERREPOSITORY_HPP
#define USERREPOSITORY_HPP

#include <spdlog/spdlog.h>
#include "IUserRepository.hpp"
#include "../config/Config.hpp"

namespace Softadastra
{
    class UserRepository : public IUserRepository
    {
    public:
        UserRepository(Config &config);
        void saveUser(const User &user) override;
        ~UserRepository();

    private:
        Config &m_config;
    };
} // namespace Softadastra

#endif // USERREPOSITORY_HPP