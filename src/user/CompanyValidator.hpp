#ifndef COMPANYVALIDATOR_HPP
#define COMPANYVALIDATOR_HPP

#include <stdexcept>
#include <string>

namespace Softadastra
{
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
} // namespace Softadastra

#endif