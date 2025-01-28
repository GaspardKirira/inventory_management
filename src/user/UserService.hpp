#ifndef USERSERVICE_HPP
#define USERSERVICE_HPP

#include "IUserRepository.hpp"

namespace Softadastra
{
    class UserService
    {
    public:
        UserService(IUserRepository &repo) : m_repo(repo) {}

        void createUser(const std::string &full_name,
                        std::shared_ptr<Email> email,
                        std::shared_ptr<Phone> phone,
                        std::shared_ptr<Password> password,
                        std::shared_ptr<Company> company)
        {
            std::unique_ptr<User> user = std::make_unique<User>(full_name, email, phone, password, company);
            m_repo.saveUser(*user);
        }

    private:
        IUserRepository &m_repo;
    };
} // namespace Softadastra

#endif // USERSERVICE_HPP