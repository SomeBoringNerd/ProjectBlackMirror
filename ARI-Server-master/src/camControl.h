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

    snprintf(commande, sizeof(commande), "ping -c 1 %s -W 1 -q", ip);

    // check commande marche
    int status = system(commande);  

    // a ce niveau là on peut free.
    free(commande);

    if (-1 != status) 
    { 
        // 0 : ping marche
        // 1 : ping échoué
        
        int ping_ret = WEXITSTATUS(status); 
        return !ping_ret;
    }
}

#endif