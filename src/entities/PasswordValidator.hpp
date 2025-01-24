#ifndef PASSWORDVALIDATOR_HPP
#define PASSWORDVALIDATOR_HPP

#include <string>
#include <openssl/sha.h>
#include <stdexcept>
#include <iomanip>
#include <sstream>

class PasswordValidator
{
public:
    // Méthode pour hacher le mot de passe avec SHA-256
    static std::string hashPassword(const std::string &password)
    {
        unsigned char hash[SHA256_DIGEST_LENGTH];

        SHA256_CTX sha256_ctx;
        SHA256_Init(&sha256_ctx);
        SHA256_Update(&sha256_ctx, password.c_str(), password.length());
        SHA256_Final(hash, &sha256_ctx);

        std::ostringstream hex_stream;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        {
            hex_stream << std::setw(2) << std::setfill('0') << std::hex << (int)hash[i];
        }

        return hex_stream.str();
    }

    // Méthode pour vérifier si le mot de passe est valide
    static void validatePassword(const std::string &password, const std::string &stored_hash)
    {
        if (stored_hash != hashPassword(password))
        {
            throw std::invalid_argument("Invalid password");
        }
    }
};

#endif // PASSWORDVALIDATOR_HPP
