#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <sys/wait.h>
#include <string.h>


#include "logger.h"
#include "camControl.h"
#include "server.h"

/********************************************************************

                                todos

        -> bouger ips, port et plus encore dans un fichier de config
        -> écrire code pour ping ARI-Plaques
                    
                                notes

                                 N/A

*********************************************************************/

// ip des deux caméras avec leur port
char* ips[2] = {"192.168.0.0", "192.168.0.0"};

/**
 * ping la caméra-ip a l'adresse donnée et fetch la dernière image disponible. Celle-ci est sauvegardée dans le dossier d'éxecution
 * 
 * @param ip : IP de la caméra
 * @return le succès de la demande. 0 = echec, 1 = succès
*/
int loop()
{
    return 0;
}


int main()
{
    initLogger("ServerSoftware");
    // système simple pour savoir si les cams sont en ligne

    int ignoreCamResult = 1;

    system("clear");
    if(!ignoreCamResult){

        int cam1 = pingCam(ips[0]);
        int cam2 = pingCam(ips[1]);

        if(cam1)
            Log("ping cam 1 réussi");
        else{
            LogError("ping cam 1 échoué");
            return 1;
        }
        
        if(cam2)
            Log("ping cam 2 réussi");
        else{
            LogError("ping cam 2 échoué");
            return 1;
        }
    }
    // création / gestion des threads

    Log("Création du thread image");

    // lancement du serveur websocket via notre fork de wsServer

    Log("Lancement du serveur websocket");
    
    initServer();

    return 0;
}