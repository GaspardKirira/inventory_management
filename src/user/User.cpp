#include "User.hpp"

using namespace Softadastra;

User::User(const std::string &full_name,
           const std::shared_ptr<Company> &company,
           const std::shared_ptr<Email> &email,
           const std::shared_ptr<Phone> &phone,
           const std::shared_ptr<Password> &password,
           const std::shared_ptr<Location> &location)
    : m_full_name(full_name),
      m_company(company),
      m_email(email),
      m_phone(phone),
      m_password(password),
      m_location(location)
{
}

User::User(const User &other)
    : m_full_name(other.m_full_name),
      m_company(other.m_company),
      m_email(other.m_email),
      m_phone(other.m_phone),
      m_password(other.m_password),
      m_location(other.m_location) {}

User &User::operator=(const User &other)
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

User::User(User &&other) noexcept
    : m_full_name(std::move(other.m_full_name)),
      m_company(std::move(other.m_company)),
      m_email(std::move(other.m_email)),
      m_phone(std::move(other.m_phone)),
      m_password(std::move(other.m_password)),
      m_location(std::move(other.m_location)) {}

User &User::operator=(User &&other) noexcept
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

void User::displayInfo() const
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

    if (m_password)
    {
        std::cout << "Password: " << m_password->getPasswordHash() << std::endl;
    }
    else
    {
        std::cout << "Password: Not provided" << std::endl;
    }
}
