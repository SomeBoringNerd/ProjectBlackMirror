#ifndef HEADER_CAM_CONTROL
#define HEADER_CAM_CONTROL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "logger.h"

/********************************************************************

                                todos

        -> Fetch le contenu des caméras et le sauvegarder dans le dossier actif
                    
                                notes

        Ce fichier est lié au controle des caméras.

*********************************************************************/


/**
 * récupère ce que voit la caméra sur l'instant T et le sauvegarde
 * 
 * @param ip : IP de la caméra
 * @return : succès de l'opération
*/
int fetchFromCam(char *ip)
{
    char commande[250];

    //ceci est un hack car en C et C++ on ne peut pas additionner de strings.
    //  "> /dev/null 2>&1" permet de ne pas avoir de logs (avec ffmpeg c'est pratique mdr)
    snprintf(commande, sizeof(commande), "ffmpeg -y -i rtsp://%s:554 -frames:v 1 %s.jpg > /dev/null 2>&1", ip, ip);

    // check le succès de la commande
    int status = system(commande);  

    if (-1 != status) 
    {         
        // on retourne l'inverse de WEXITSTATUS (car 0 = succès, mais en C, 0 == false)
        // donc en inversant le status, on retourne 1 si le ping est répondu, 0 si time out
        return !WEXITSTATUS(status);;
    }
}

/**
 * Ping une addresse ip pour savoir si une caméra est sur le réseau local.
 * 
 * @param ip : ip de l'appareil a ping (duh)
 * @return : Succès de l'opération (1 = marche, 0 = fail)
*/
int pingCam(char* ip)
{
    char commande[128];

    // on va essayer de ping l'ip passée une fois

    //ceci est un hack car en C et C++ on ne peut pas additionner de strings.
    //  "> /dev/null 2>&1" permet de ne pas avoir d'output, pour ne pas remplir les logs
    snprintf(commande, sizeof(commande), "ping -c 1 %s -W 1 -q   > /dev/null 2>&1", ip);

    // check le succès de la commande
    int status = system(commande);  

    if (-1 != status) 
    {         
        // on retourne l'inverse de WEXITSTATUS (car 0 = succès, mais en C, 0 == false)
        // donc en inversant le status, on retourne 1 si le ping est répondu, 0 si time out
        int ping_ret = WEXITSTATUS(status); 
        return !ping_ret;
    }
}

#endif