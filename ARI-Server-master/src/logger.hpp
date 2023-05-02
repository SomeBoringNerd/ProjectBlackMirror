#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <iostream>

std::string _name;

FILE *_log;

/**
 * Je présente mes plus sincères excuses a ceux qui ont une meilleure idée de comment faire ça
 *
 * @param appname : nom de l'application, doit être unique
 */
int initLogger(std::string appname)
{
    /*
    _name = appname;

    char buffer[128];
    #ifdef __unix__
    snprintf(buffer, sizeof(buffer), "mkdir %s && touch ./%s/log.txt", appname, appname);
    system(buffer);
    #else
    // pourquoi windows permet pas de faire une commande après l'autre comme linux ?
    char _buffer[128];

    snprintf(buffer, sizeof(_buffer), "mkdir %s", appname);
    snprintf(_buffer, sizeof(_buffer), "type nul >> %s/log.txt", appname);

    system(buffer);
    system(_buffer);
    #endif

    char file[256];
    snprintf(file, sizeof(file), "./%s/log.txt", _name);

    _log = fopen(file, "w");
    */
    return 0;
}

void toFile(std::string texte)
{
    printf(texte.c_str());
    // fprintf(_log, texte);
}

void Log(std::string texte)
{
    toFile("[LOG] : " + texte + "\n");
}

void LogError(std::string texte)
{
    printf("\033[0;31m");
    toFile("[ERROR] : " + texte + "\n");
    printf("\n\033[0;0m");
}

void LogWarning(std::string texte)
{
    printf("\033[0;33m");
    toFile("[WARNING] : " + texte + "\n");
    printf("\n\033[0;0m");
}