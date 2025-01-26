#include "User.hpp"
#include <spdlog/spdlog.h>

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

void User::warning(const std::string &message) const
{
    spdlog::warn("{} : Not provided", message);
}

void User::displayInfo() const
{
    spdlog::info("FULLNAME: {}", m_full_name);

    if (m_company)
    {
        spdlog::info("COMPANY: {}", m_company->getCompanyName());
    }
    else
    {
        warning("COMPANY");
    }

    if (m_email)
    {
        spdlog::info("EMAIL: {}", m_email->getEmail());
    }
    else
    {
        warning("EMAIL");
    }

    if (m_phone)
    {
        std::cout << "Phone: " << m_phone->getPhone() << std::endl;
        spdlog::info("PHONE: {}", m_phone->getPhone());
    }
    else
    {
        warning("PHONE");
    }

    if (m_location)
    {
        spdlog::info("Location");
        spdlog::info("Country ID: {}", m_location->getCountryId());
        spdlog::info("Currency ID: {}", m_location->getCurrencyId());
        spdlog::info("Language ID: {}", m_location->getLanguageId());
    }
    else
    {
        warning("LOCATION");
    }

    if (m_password)
    {
        spdlog::info("PASSWORD: {}", m_password->getPasswordHash());
    }
    else
    {
        warning("PASSWORD");
    }
}
