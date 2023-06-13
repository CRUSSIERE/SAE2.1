#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

#define DATABASE_NAME "ggratchev_lakartxela"
#define CONNECT_TYPE "QODBC"

class Database
{
public:
    Database(); // Constructeur par défaut
    bool openDataBase(); // Ouvre la base de données
    void closeDataBase(); // Ferme la base de données

private:
    QSqlDatabase bdd; // Objet représentant la base de données

};

#endif // DATABASE_H
