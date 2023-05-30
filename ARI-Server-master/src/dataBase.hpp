#pragma once

#include <stdio.h>
#include <stdlib.h>

#if ALLOW_DATABASE

#include <sqlite3.h>

sqlite3 *db;
#include <algorithm>

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s)
{
    return rtrim(ltrim(s));
}

void initDatabase()
{

    // ouvre la db
    int rc;
    rc = sqlite3_open("BlackMirror", &db);

    std::string sql = "CREATE TABLE IF NOT EXISTS CLIENT (NAME TEXT NOT NULL, PLAQUE TEXT NOT NULL);";
    char *feedback;

    // execute la request a la recherche d'erreur
    if (!sqlite3_exec(db, sql.c_str(), 0, 0, &feedback) == SQLITE_OK)
    {
        LogError("La base de données n'a pas pu être créée");
    }
}

/**
 * Regarde dans la base de donnée si cette plaque existe.
 *
 * @param plaque le texte sur la plaque d'immatriculation au format AA-123-BB
 * @return techniquement, cette requête retourne 0 (SQLITE_OK) si elle réussit
 * @todo : implémentation de la date limite, et d'autres mesures de sécurité
 */
int fetchDatabase(std::string plaque)
{
    std::string request = "SELECT * FROM CLIENT WHERE PLAQUE='" + trim(plaque) + "';";
    char *feedback_reg;
    return sqlite3_exec(db, request.c_str(), 0, 0, &feedback_reg) == SQLITE_OK;
}
#endif