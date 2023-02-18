#ifndef HEADER_LOGGER
#define HEADER_LOGGER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *_name;

FILE *_log;

/**
 * Je présente mes plus sincères excuses a ceux qui ont une meilleure idée de comment faire ça
 * 
 * @param appname : nom de l'application, doit être unique
*/
int initLogger(char* appname)
{
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
    return 0;
}

void toFile(char *texte)
{
    printf(texte);
    fprintf(_log, texte);
}

void Log(char *texte)
{
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "[LOG] : %s\n", texte);
    toFile(buffer);
}

void LogError(char *texte)
{
    printf("\033[0;31m");
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "[ERROR] : %s", texte);
    toFile(buffer);
    printf("\n\033[0;0m");
}

void LogWarning(char *texte)
{
    printf("\033[0;33m");
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "[WARNING] : %s", texte);
    toFile(buffer);
    printf("\n\033[0;0m");
}

#endif