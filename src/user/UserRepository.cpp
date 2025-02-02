#include "UserRepository.hpp"
#include <memory>
#include <vector>
#include <stdexcept>

namespace Softadastra
{
    UserRepository::UserRepository(Config &config) : m_config(config) {}

    void UserRepository::saveUser(const User &user)
    {
        std::unique_ptr<sql::Connection> con = m_config.getDbConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO users(full_name, email, phone, password_hash, company) VALUES(?,?,?,?,?)"));
        pstmt->setString(1, user.getFullName());
        pstmt->setString(2, user.getEmail()->getEmail());
        pstmt->setString(3, user.getPhone()->getPhone());
        pstmt->setString(4, user.getPassword()->getPasswordHash());
        pstmt->setString(5, user.getCompany()->getCompanyName());

        pstmt->executeUpdate();
    }

    std::vector<User> UserRepository::findAll()
    {
        std::vector<User> users;
        std::unique_ptr<sql::Connection> con = m_config.getDbConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM users"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next())
        {
            auto email = std::make_shared<Email>(res->getString("email"));
            auto phone = std::make_shared<Phone>(res->getString("phone"));
            auto password = std::make_shared<Password>(res->getString("password_hash"));
            auto company = std::make_shared<Company>(res->getString("company"));
            User user(res->getString("full_name"), email, phone, password, company);
            users.push_back(user);
        }

        return users;
    }

    std::shared_ptr<User> UserRepository::find(int userId)
    {
        std::unique_ptr<sql::Connection> con = m_config.getDbConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM users WHERE id = ?"));
        pstmt->setInt(1, userId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next())
        {
            auto user = std::make_shared<User>();
            user->setFullName(res->getString("full_name"));
            user->setEmail(std::make_shared<Email>(res->getString("email")));
            user->setPhone(std::make_shared<Phone>(res->getString("phone")));
            user->setPassword(std::make_shared<Password>(res->getString("password_hash")));
            user->setCompany(std::make_shared<Company>(res->getString("company")));
            return user;
        }
        else
        {
            throw std::runtime_error("User not found");
        }
    }

    void UserRepository::update(int userId, const User &user)
    {
        std::unique_ptr<sql::Connection> con = m_config.getDbConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE users SET full_name = ?, email = ?, phone = ?, password_hash = ?, company = ? WHERE id = ?"));
        pstmt->setString(1, user.getFullName());
        pstmt->setString(2, user.getEmail()->getEmail());
        pstmt->setString(3, user.getPhone()->getPhone());
        pstmt->setString(4, user.getPassword()->getPasswordHash());
        pstmt->setString(5, user.getCompany()->getCompanyName());
        pstmt->setInt(6, userId);

        pstmt->executeUpdate();
    }

    void UserRepository::deleteUser(int userId)
    {
        std::unique_ptr<sql::Connection> con = m_config.getDbConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("DELETE FROM users WHERE id = ?"));
        pstmt->setInt(1, userId);

        pstmt->executeUpdate();
    }

    UserRepository::~UserRepository()
    {
        spdlog::warn("UserRepository Destroyed bien!");
    }

} // namespace Softadastra
