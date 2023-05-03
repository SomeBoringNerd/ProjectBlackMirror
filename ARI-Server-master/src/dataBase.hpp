#pragma once

#include <stdio.h>
#include <stdlib.h>

#if !ALLOW_DATABASE
#include "jdbc/mysql_connection.h"

#include "include/jdbc/cppconn/driver.h"
#include "include/jdbc/cppconn/exception.h"
#include "include/jdbc/cppconn/resultset.h"
#include "include/jdbc/cppconn/statement.h"
#include "include/jdbc/cppconn/prepared_statement.h"

#define HOST "192.168.1.3"
#define USER "root"
#define PASS ""
#define DB "PlaqueSystem"

sql::Driver *driver;
std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
std::auto_ptr<sql::Statement> stmt(con->createStatement());

/**
 * Initialise la base de donnée
 */
void initDatabase()
{
    driver = get_driver_instance();

    con->setSchema(DB);
}

/**
 * Regarde dans la base de donnée si cette plaque existe.
 *
 * @param plaque le texte sur la plaque d'immatriculation au format AA-123-BB
 * @return 1 si la plaque existe.
 */
int fetchDatabase(std::string plaque)
{
    int e = 0;
    stmt->execute("SELECT * FROM Utilisateurs WHERE Plaque=\"" + plaque + "\";");

    std::auto_ptr<sql::ResultSet> res;
    do
    {
        res.reset(stmt->getResultSet());
        while (res->next())
        {
            e++;
        }
    } while (stmt->getMoreResults());

    return e >= 1;
}
#endif