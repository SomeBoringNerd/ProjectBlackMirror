#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
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
 * @return rien normalement
*/
int loop(char *ip)
{
    while(true)
    {
        char* message = "";
        // si la caméra est en ligne
        if(!pingCam(ip))
        {
            sprintf(message, sizeof(message), "%s est hors ligne, je ne peux pas assurer le fonctionnement du système donc je vais demander de l'aide au client", ip);
            ws_sendframe_txt(client, "WARNING_EXCEPTION_NO_CAM_FOUND");
            LogError(message);
            break;
        }
        else if(!fetchFromCam(ip))
        {
            sprintf(message, sizeof(message), "Je n'ai pas pu obtenir une image de %s", ip);
            LogError(message);
            break;
        }

        sprintf(message, sizeof(message), "Image obtenue de %s", ip);
        Log(message);
    }
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

    Log("Création des thread image");
    pthread_t camUn, camDeux;
    pthread_create(&camUn, NULL, loop, &ips[0]);
    pthread_create(&camDeux, NULL, loop, &ips[1]);

    pthread_join(camUn, (void**)NULL);
    pthread_join(camDeux, (void**)NULL);


    // lancement du serveur websocket via notre fork de wsServer

    Log("Lancement du serveur websocket");
    
    initServer();

    return 0;
}