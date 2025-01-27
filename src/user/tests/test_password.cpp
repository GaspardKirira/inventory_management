#include <gtest/gtest.h>
#include "../Password.hpp"
#include "../PasswordValidator.hpp"

using namespace Softadastra;

TEST(PasswordTest, TestPasswordHashing)
{
    std::string password = "123456";
    std::string hash = PasswordValidator::hashPassword(password);
    ASSERT_FALSE(hash.empty());
    std::string hash2 = PasswordValidator::hashPassword(password);
    ASSERT_EQ(hash, hash2);
}

TEST(PasswordTest, TestPasswordValidation)
{
    std::string password = "123456";
    Password pwd(password);
    try
    {
        pwd.validatePassword(password);
    }
    catch (const std::invalid_argument &e)
    {
        FAIL() << "Password validation failed: " << e.what();
    }

    try
    {
        pwd.validatePassword("wrongPassword");
        FAIL() << "Password validation should fail for wrong password.";
    }
    catch (const std::invalid_argument &e)
    {
        ASSERT_STREQ(e.what(), "Password validation failed: Mot de passe invalide.");
    }
}

TEST(PasswordValidatorTest, TestInvalidPassword)
{
    // Tester un cas où le mot de passe est incorrect
    std::string wrongPassword = "wrongPassword";
    std::string storedHash = PasswordValidator::hashPassword("mySecurePassword");

    try
    {
        PasswordValidator::validatePassword(wrongPassword, storedHash);
        FAIL() << "Password validation should fail for wrong password.";
    }
    catch (const std::invalid_argument &e)
    {
        ASSERT_STREQ(e.what(), "Mot de passe invalide.");
    }
}
