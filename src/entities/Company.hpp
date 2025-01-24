#ifndef COMPANY_HPP
#define COMPANY_HPP

#include <string>
#include <stdexcept>

class CompanyValidator
{
public:
    static void validateName(const std::string &company_name)
    {
        if (company_name.empty())
        {
            throw std::invalid_argument("Company name cannot be empty");
        }
        if (company_name.size() > 10)
        {
            throw std::invalid_argument("Company name is too long");
        }
    }
};

class Company
{
public:
    explicit Company(const std::string &company_name = "No Company")
        : m_company_name(company_name)
    {
        CompanyValidator::validateName(company_name);
    }

    const std::string &getCompanyName() const { return m_company_name; }

private:
    std::string m_company_name;
};

#endif // COMPANY_HPP