#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <sys/wait.h>
#include <string.h>
#include "logger.h"

// ip des deux caméras avec leur port
// @todo : bouger ça dans un fichier de config
char* ips[2] = {"192.168.26.74", "192.168.1.69"};

/**
 * ping la caméra-ip a l'adresse donnée et fetch la dernière image disponible. Celle-ci est sauvegardée dans le dossier d'éxecution
 * 
 * @param ip : IP de la caméra
 * 
 * @return le succès de la demande. 0 = echec, 1 = succès
*/
int loop()
{
    return 0;
}

int pingCam(char* ip)
{
    // tout ce bazard car je peux pas juste "texte " + ip + " texte"
    char* commande = calloc(strlen("ping -c 1 ") + strlen(ip) + strlen(" -W 1 -q") + 1, sizeof(char));

    strcat(commande, "ping -c 1 ");
    strcat(commande, ip);
    strcat(commande, " -W 1 -q");

    // check commande marche
    int status = system(commande);  

    // a ce niveau là on peut free.
    free(commande);

    if (-1 != status) 
    { 
        // 0 : ping marche
        // 1 : ping échoué
        
        int ping_ret = WEXITSTATUS(status); 
        return ping_ret;
    }
}

int main()
{
    initLogger("ServerSoftware");
// système simple pour savoir si les cams sont en ligne

    int cam1 = pingCam(ips[0]);
    int cam2 = pingCam(ips[1]);

    system("clear");

    if(!cam1)
        Log("ping cam 1 réussi");
    else{
        LogError("ping cam 1 échoué");
        return 1;
    }
    
    if(!cam2)
        Log("ping cam 2 réussi");
    else{
        LogError("ping cam 2 échoué");
        return 1;
    }
    // création des threads

    // démarage des threads

    // lancement du serveur websocket via wsServer

    return 0;
}