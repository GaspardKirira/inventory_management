#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <mutex>
#include <stdexcept>
#include <cstdlib>
#include <memory>

class Config
{
public:
    // Supprimer le constructeur par copie et l'opérateur d'affectation pour éviter la duplication
    Config();
    Config(const Config &) = delete;
    Config &operator=(const Config &) = delete;

    // Méthode pour obtenir l'instance unique (Singleton)
    static Config &getInstance()
    {
        static Config instance;
        return instance;
    }

    // Charger la configuration depuis un fichier JSON
    void loadConfig();

    // Connexion à la base de données MySQL
    std::unique_ptr<sql::Connection> getDbConnection();

    // Récupérer le mot de passe depuis les variables d'environnement
    std::string getDbPasswordFromEnv();

    // Getters pour accéder aux valeurs de configuration
    const std::string &getDbHost() const { return db_host; }
    const std::string &getDbUser() const { return db_user; }
    const std::string &getDbName() const { return db_name; }
    int getDbPort() const { return db_port; } // Nouveau getter
    int getServerPort() const { return server_port; }

private:
    // Variables de configuration
    std::string db_host;
    std::string db_user;
    std::string db_pass;
    std::string db_name;
    int db_port; // Nouveau membre pour le port MySQL
    int server_port;
};

#endif // CONFIG_HPP
