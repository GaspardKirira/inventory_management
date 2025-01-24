#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <string>
#include "PasswordValidator.hpp"

class Password
{
public:
    // Constructeur : hache le mot de passe lors de la création de l'objet
    explicit Password(const std::string &password)
    {
        // On hache le mot de passe à la création de l'objet
        m_password_hash = PasswordValidator::hashPassword(password);
    }

    // Méthode pour récupérer le hachage du mot de passe
    const std::string &getPasswordHash() const { return m_password_hash; }

    // Méthode pour valider un mot de passe en comparant avec le hachage
    void validatePassword(const std::string &password) const
    {
        try
        {
            PasswordValidator::validatePassword(password, m_password_hash); // Utilisation du validateur
        }
        catch (const std::invalid_argument &e)
        {
            // Si le mot de passe est invalide, on peut relancer l'exception ou gérer autrement
            throw std::invalid_argument("Password validation failed: " + std::string(e.what()));
        }
    }

private:
    std::string m_password_hash; // Hachage du mot de passe
};

#endif // PASSWORD_HPP
