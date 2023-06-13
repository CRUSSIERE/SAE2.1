#include "database.h"

Database::Database() {
    // Constructeur par défaut
}

bool Database::openDataBase() {
    // Crée une instance de la base de données QODBC
    QSqlDatabase bdd = QSqlDatabase::addDatabase("QODBC");

    // Configure les informations de connexion à la base de données
    bdd.setHostName("lakartxela.iutbayonne.univ-pau.fr:3306");
    bdd.setDatabaseName("ggratchev_lakartxela");
    bdd.setUserName("ggratchev_bd");
    bdd.setPassword("ggratchev_bd");

    // Tente d'ouvrir la connexion à la base de données
    bool ok = bdd.open();

    // Affiche le résultat de la tentative d'ouverture dans la console de débogage
    qDebug() << ok;

    // Retourne le résultat de l'ouverture de la base de données (true si la connexion est établie, sinon false)
    return ok;
}

void Database::closeDataBase() {
    // Vérifie si la base de données est ouverte
    if (bdd.open()) {
        // Ferme la connexion à la base de données
        bdd.close();
    }
}
