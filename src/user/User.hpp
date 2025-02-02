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

namespace Softadastra
{
    class User
    {
    public:
        User() = default;

        User(const std::string &full_name,
             const std::shared_ptr<Softadastra::Email> &email,
             const std::shared_ptr<Softadastra::Phone> &phone,
             const std::shared_ptr<Softadastra::Password> &password,
             const std::shared_ptr<Softadastra::Company> &company = nullptr);

        ~User() = default;
        User(const User &other);
        User &operator=(const User &other);
        User(User &&other) noexcept;
        User &operator=(User &&other) noexcept;

        int getId() const { return m_id; }
        const std::string &getFullName() const { return m_full_name; }
        const std::shared_ptr<Email> getEmail() const { return m_email; }
        const std::shared_ptr<Phone> getPhone() const { return m_phone; }
        const std::shared_ptr<Password> getPassword() const { return m_password; }
        const std::shared_ptr<Company> getCompany() const { return m_company; }

        void warning(const std::string &message) const;
        void displayInfo() const;

        void setFullName(const std::string &full_name) { m_full_name = full_name; }
        void setEmail(const std::shared_ptr<Email> &email) { m_email = email; }
        void setPhone(const std::shared_ptr<Phone> &phone) { m_phone = phone; }
        void setPassword(const std::shared_ptr<Password> &password) { m_password = password; }
        void setCompany(const std::shared_ptr<Company> &company) { m_company = company; }

    private:
        int m_id{};
        std::string m_full_name{};
        std::shared_ptr<Softadastra::Email> m_email{};
        std::shared_ptr<Softadastra::Phone> m_phone{};
        std::shared_ptr<Softadastra::Password> m_password{};
        std::shared_ptr<Softadastra::Company> m_company{};
    };
}

#endif // USER_HPP