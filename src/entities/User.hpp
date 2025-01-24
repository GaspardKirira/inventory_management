#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <memory>
#include <iostream>
#include "Company.hpp"
#include "Email.hpp"
#include "Phone.hpp"
#include "Password.hpp"
#include "Location.hpp"

class User
{
public:
    User(const std::string &full_name,
         const std::shared_ptr<Company> &company = std::make_shared<Company>(),
         const std::shared_ptr<Email> &email = nullptr,
         const std::shared_ptr<Phone> &phone = nullptr,
         const std::shared_ptr<Location> &location = std::make_shared<Location>())
        : m_full_name(full_name),
          m_company(company),
          m_email(email),
          m_phone(phone),
          m_location(location)
    {
    }

    // Destructeur
    ~User() = default;

    // Constructeur de copie
    User(const User &other)
        : m_full_name(other.m_full_name),
          m_company(other.m_company),
          m_email(other.m_email),
          m_phone(other.m_phone),
          m_password(other.m_password),
          m_location(other.m_location) {}

    // Opérateur d'assignation par copie
    User &operator=(const User &other)
    {
        if (this != &other)
        {
            m_full_name = other.m_full_name;
            m_company = other.m_company;
            m_email = other.m_email;
            m_phone = other.m_phone;
            m_password = other.m_password;
            m_location = other.m_location;
        }
        return *this;
    }

    // Constructeur de déplacement
    User(User &&other) noexcept
        : m_full_name(std::move(other.m_full_name)),
          m_company(std::move(other.m_company)),
          m_email(std::move(other.m_email)),
          m_phone(std::move(other.m_phone)),
          m_password(std::move(other.m_password)),
          m_location(std::move(other.m_location)) {}

    // Opérateur d'assignation par déplacement
    User &operator=(User &&other) noexcept
    {
        if (this != &other)
        {
            m_full_name = std::move(other.m_full_name);
            m_company = std::move(other.m_company);
            m_email = std::move(other.m_email);
            m_phone = std::move(other.m_phone);
            m_password = std::move(other.m_password);
            m_location = std::move(other.m_location);
        }
        return *this;
    }

    const std::string &getFullName() const { return m_full_name; }

    void displayInfo() const
    {
        std::cout << "Full Name: " << m_full_name << std::endl;

        if (m_company)
        {
            std::cout << "Company: " << m_company->getCompanyName() << std::endl;
        }
        else
        {
            std::cout << "Company: Not provided" << std::endl;
        }

        if (m_email)
        {
            std::cout << "Email: " << m_email->getEmail() << std::endl;
        }
        else
        {
            std::cout << "Email: Not provided" << std::endl;
        }

        if (m_phone)
        {
            std::cout << "Phone: " << m_phone->getPhone() << std::endl;
        }
        else
        {
            std::cout << "Phone: Not provided" << std::endl;
        }

        if (m_location)
        {
            std::cout << "Location - Country ID: " << m_location->getCountryId()
                      << ", Currency ID: " << m_location->getCurrencyId()
                      << ", Language ID: " << m_location->getLanguageId() << std::endl;
        }
        else
        {
            std::cout << "Location: Not provided" << std::endl;
        }
    }

private:
    std::string m_full_name{};
    std::shared_ptr<Company> m_company{};
    std::shared_ptr<Email> m_email{};
    std::shared_ptr<Phone> m_phone{};
    std::shared_ptr<Password> m_password{};
    std::shared_ptr<Location> m_location{};
};

#endif // USER_HPP