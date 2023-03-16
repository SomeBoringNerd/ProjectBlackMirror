#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

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

#define DEBUG 1

// ip des deux caméras avec leur port
char* ips[2] = {"192.168.1.2", "192.168.0.4"};

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
    while(doit_exit)
    {
        if(isClientLoggedIn)
        {
            // si la caméra est en ligne
            if(!pingCam(ips[_ip]))
            {
                sprintf(message, "%s est hors ligne, je ne peux pas assurer le fonctionnement du système donc je vais demander de l'aide au client", ips[_ip]);
                send("WARNING_EXCEPTION_NO_CAM_FOUND");
                LogError(message);
            }
            else if(!fetchFromCam(ips[_ip]))
            {
                sprintf(message, sizeof(message), "Je n'ai pas pu obtenir une image de %s", ips[_ip]);
                send("ERROR_COULDNT_GET_IMAGE");
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
        }
    }
    LogWarning("Un thread vient d'être supprimé");
    return 0;
}

int main()
{
    // Lors du debug, j'ai vu que WSserver a besoin d'être executé en root
    // mais ça empêche le dossier du logger d'être supprimé
    // @TODO : faire en sorte que le dossier des logs n'appartienne pas a root
    if(getuid())
    {
        printf("\033[0;31m");
        printf(" [ERROR] CE LOGICIEL DOIT ÊTRE LANCÉ EN ROOT");
        printf("\n\033[0;0m");
        return 1;
    }
    initLogger("ServerSoftware");
    

    doit_exit = 1;
    system("clear");

    // système simple pour savoir si les cams sont en ligne

    if(!DEBUG)
    {
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
        LogWarning("LE LOGICIEL EST EN MODE DEBUG ! SI VOUS ÊTES SUR LE SERVEUR DE PROD VEUILLEZ CHANGER LA VARIABLE DEBUG DE 1 A 0 !!!!!!!!!!");
    }
    // création / gestion des threads

    Log("Création des thread image");

    int t1 = pthread_create(&camUn, NULL, loop, (void *)0);

    if(t1){
        Log("thread 1 n'a pas pu être créé");
        return 1;
    }
    
    int t2 = pthread_create(&camDeux, NULL, loop, (void *)1);
    if(t2){
        Log("thread 2 n'a pas pu être créé");
        return 1;
    }

    Log("Lancement du serveur websocket");
    
    initWebSocket();

    char e;
    scanf("%c", &e);

    doit_exit = 0;

    return 0;
}
