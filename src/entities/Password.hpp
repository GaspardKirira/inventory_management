#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <string>
#include "PasswordValidator.hpp"

namespace Softadastra
{
    class Password
    {
    public:
        // Constructeur par défaut
        Password() = default;

        // Constructeur avec le mot de passe
        explicit Password(const std::string &password)
            : m_password_hash(Softadastra::PasswordValidator::hashPassword(password))
        {
        }

        // Getter pour le hash du mot de passe
        const std::string &getPasswordHash() const { return m_password_hash; }

        // Méthode pour valider un mot de passe donné
        void validatePassword(const std::string &password) const
        {
            try
            {
                Softadastra::PasswordValidator::validatePassword(password, m_password_hash);
            }
            catch (const std::invalid_argument &e)
            {
                throw std::invalid_argument("Password validation failed: " + std::string(e.what()));
            }
        }

    private:
        std::string m_password_hash{};
    };
} // namespace Softadastra

#endif // PASSWORD_HPP
