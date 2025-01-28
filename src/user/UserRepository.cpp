#include "UserRepository.hpp"

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

        spdlog::info("Utilisateur {} enregistré avec succès dans la base de données.", user.getFullName());
    }

    UserRepository::~UserRepository()
    {
        spdlog::warn("UserRepository Destroyed !");
    }
} // namespace Softadastra
