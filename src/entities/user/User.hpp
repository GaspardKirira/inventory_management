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
         const std::shared_ptr<Softadastra::Company> &company = nullptr,
         const std::shared_ptr<Softadastra::Email> &email = nullptr,
         const std::shared_ptr<Softadastra::Phone> &phone = nullptr,
         const std::shared_ptr<Softadastra::Password> &password = nullptr,
         const std::shared_ptr<Softadastra::Location> &location = nullptr);

    ~User() = default;
    User(const User &other);
    User &operator=(const User &other);
    User(User &&other) noexcept;
    User &operator=(User &&other) noexcept;
    const std::string &getFullName() const { return m_full_name; }
    void displayInfo() const;

private:
    std::string m_full_name{};
    std::shared_ptr<Softadastra::Company> m_company{};
    std::shared_ptr<Softadastra::Email> m_email{};
    std::shared_ptr<Softadastra::Phone> m_phone{};
    std::shared_ptr<Softadastra::Password> m_password{}; // Avant m_location
    std::shared_ptr<Softadastra::Location> m_location{}; // Après m_password
};

#endif // USER_HPP