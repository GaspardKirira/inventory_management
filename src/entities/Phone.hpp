#ifndef PHONE_HPP
#define PHONE_HPP

#include <string>
#include <stdexcept>

class PhoneValidator
{
public:
    static void validatePhoneNumber(const std::string &phone)
    {
        // Le numéro de téléphone doit être entre 10 et 15 caractères (inclus)
        if (phone.size() < 10 || phone.size() > 15)
        {
            throw std::invalid_argument("Invalid phone number format: must be between 10 and 15 characters");
        }

        for (char c : phone)
        {
            if (!isdigit(c))
            {
                throw std::invalid_argument("Invalid phone number format: must contain only digits");
            }
        }
    }
};

class Phone
{
public:
    explicit Phone(const std::string &phone) : m_phone(phone)
    {
        PhoneValidator::validatePhoneNumber(phone);
    }

    const std::string &getPhone() const { return m_phone; }

private:
    std::string m_phone;
};

#endif // PHONE_HPP
