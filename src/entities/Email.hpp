#ifndef EMAIL_HPP
#define EMAIL_HPP

#include <string>
#include <regex>
#include <stdexcept>

class EmailValidator
{
public:
    static void validateEmail(const std::string &email)
    {
        std::regex email_regex(R"((\w+)(\.[\w]+)*@(\w+)(\.[a-zA-Z]{2,3})+)");

        if (!std::regex_match(email, email_regex))
        {
            throw std::invalid_argument("Invalid email format");
        }
    }
};

class Email
{
public:
    explicit Email(const std::string &email) : m_email(email)
    {
        EmailValidator::validateEmail(email);
    }

    const std::string &getEmail() const { return m_email; }

private:
    std::string m_email;
};

#endif // EMAIL_HPP
