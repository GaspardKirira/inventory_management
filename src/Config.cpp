#include "Config.hpp"

// Initialisation des membres avec des valeurs par défaut
Config::Config()
    : db_host("localhost"),
      db_user("root"),
      db_pass(),
      db_name("web243_adastra"),
      db_port(3306),
      server_port(8080)
{
}

using json = nlohmann::json; 

void Config::loadConfig()
{
    std::ifstream config_file("../src/config.json", std::ios::in);

    if (!config_file.is_open())
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier de configuration : config.json");
    }

    json config;
    try
    {
        config_file >> config; // Charger le fichier JSON
    }
    catch (const json::parse_error &e)
    {
        throw std::runtime_error("Erreur de parsing du fichier JSON : " + std::string(e.what()));
    }

    // Vérification des sections principales
    if (!config.contains("database") || !config.contains("server"))
    {
        throw std::runtime_error("Fichier JSON invalide : sections 'database' ou 'server' manquantes.");
    }

    // Validation des clés et des types
    try
    {
        db_host = config.at("database").at("host").get<std::string>();
        db_user = config.at("database").at("user").get<std::string>();
        db_pass = config.at("database").at("password").get<std::string>();
        db_name = config.at("database").at("name").get<std::string>();
        server_port = config.at("server").at("port").get<int>();
    }
    catch (const json::type_error &e)
    {
        throw std::runtime_error("Types incorrects dans le fichier JSON : " + std::string(e.what()));
    }

    std::cout << "Configuration chargée avec succès. Serveur démarré sur le port " << server_port << std::endl;
}

std::unique_ptr<sql::Connection> Config::getDbConnection()
{
    try
    {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> con(
            driver->connect("tcp://" + db_host + ":" + std::to_string(db_port), db_user, db_pass));

        // Définir le schéma de la base de données
        con->setSchema(db_name);
        return con;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "Erreur de connexion à la base de données : " << e.what() << std::endl;
        throw std::runtime_error("Erreur de connexion à la base de données.");
    }
}

std::string Config::getDbPasswordFromEnv()
{
    const char *password = std::getenv("DB_PASSWORD");
    if (password == nullptr)
    {
        // Si aucun mot de passe n'est défini, retourne une chaîne vide
        return "";
    }
    return std::string(password);
}
