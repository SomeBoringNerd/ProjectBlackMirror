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
char* ips[2] = {"192.168.0.0", "192.168.0.1"};

// note : apparemment mettre les variables pthread_t en local fait un SIGDEV violation
pthread_t camUn, camDeux, exit_listener;

int doit_exit = 1;

int respond[2] = {0,0};
/**
 * ping la caméra-ip a l'adresse donnée et fetch la dernière image disponible. Celle-ci est sauvegardée dans le dossier d'éxecution
 * 
 * @param ip : IP de la caméra
 * @return rien normalement
*/
static void * loop(void * data)
{
    int _ip = (int)data;
    char* message = malloc(sizeof(char) * 256);
    while(doit_exit == 1)
    {
        if(isClientLoggedIn)
        {
            // si la caméra est en ligne
            if(!pingCam(ips[_ip]))
            {
                sprintf(message, "%s est hors ligne, je ne peux pas assurer le fonctionnement du système donc je vais demander de l'aide au client", ips[_ip]);
                ws_sendframe_txt(client, "WARNING_EXCEPTION_NO_CAM_FOUND");
                LogError(message);
            }
            else if(!fetchFromCam(ips[_ip]))
            {
                sprintf(message, sizeof(message), "Je n'ai pas pu obtenir une image de %s", ips[_ip]);
                ws_sendframe_txt(client, "ERROR_COULDNT_GET_IMAGE");
                LogError(message);
                break;
            }else
            {
                sprintf(message, sizeof(message), "Image obtenue de %s", ips[_ip]);    
            }        
            
            if(!doit_exit)
            {
                Log("Un thread vient d'être supprimé");
                pthread_exit(0);
            }
            printf("doit_exit = %d", doit_exit);

        }
    }
    LogWarning("Un thread vient d'être supprimé");
    free(message);
    return 0;
}

int main()
{
    initLogger("ServerSoftware");
    // système simple pour savoir si les cams sont en ligne

    int ignoreCamResult = 1;
    doit_exit = 1;
    system("clear");
    if(!ignoreCamResult){

        int cam1 = pingCam(ips[0]);
        int cam2 = pingCam(ips[1]);

        if(cam1){
            Log("ping cam 1 réussi");
	        respond[0] = 1;
        }
        else{
            LogError("ping cam 1 échoué");
            return 1;
        }
        
        if(cam2){
            Log("ping cam 2 réussi");
	        respond[1] = 1;
        }
        else{
            LogError("ping cam 2 échoué");
            return 1;
        }
    }else{
        LogWarning("LE LOGICIEL EST EN MODE DEBUG !");
    }
    // création / gestion des threads

    Log("Création des thread image");

    int t1 = pthread_create(&camUn, NULL, loop, (void *)0);

    if(t1){
        Log("thread 1 n'a pas pu être créé");
    }
    
    int t2 = pthread_create(&camDeux, NULL, loop, (void *)1);
    if(t2){
        Log("thread 2 n'a pas pu être créé");
    }

    Log("Lancement du serveur websocket");
    
    initWebSocket();

    char e;
    scanf("%c", &e);

    doit_exit = 0;

    return 0;
}
