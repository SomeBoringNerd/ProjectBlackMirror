#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdint.h>
#include <unistd.h>

#include <string>
#include <cstdint>
#include <regex>

#include "logger.hpp"
#include "camControl.hpp"
#include "imgUtil.hpp"
#include "server.hpp"

using namespace std;

/********************************************************************

                                todos

        -> bouger ips, port et plus encore dans un fichier de config
        -> écrire code pour ping ARI-Plaques
                    
                                notes

                                 N/A

*********************************************************************/

#define DEBUG_MODE 0

// ip des deux caméras avec leur port
string ips[2] = {"192.168.1.2", "192.168.0.4"};

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
void * loop(void * data)
{
    int _ip = (intptr_t)data;
    int old_response = 0;
    while(doit_exit)
    {
        if(isClientLoggedIn || !DEBUG_MODE)
        {
            // si la caméra est en ligne
            respond[_ip] = execute(ips[_ip], 1);

            if(!respond[_ip])
            {
                if(old_response != respond[_ip])
                {
                    LogWarning("La caméra " + ips[_ip] + " est hors ligne");
                    send("WARNING_EXCEPTION_NO_CAM_FOUND");
                }
            }
            else 
            {
                if(old_response != respond[_ip])
                {
                    Log("La caméra " + ips[_ip] + " est revenue en ligne");
                }
                if(!execute(ips[_ip], 0))
                {
                    send("ERROR_COULDNT_GET_IMAGE");
                    LogError("Impossible de récuperer une image de " + ips[_ip] + "(hors ligne ?)");
                    break;
                }else
                {
                    string plaque = getPlaque(ips[_ip] + ".jpg");

                    if(regex_match(plaque, regex("[A-Z][A-Z]-[0-9][0-9][0-9]-[A-Z][A-Z]")))
                    {
                        Log(plaque);
                    }
                }   
            }    

            old_response = respond[_ip];
            
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

    // système simple pour savoir si les cams sont en ligne

    int cam1 = execute(ips[0], 1);
    int cam2 = execute(ips[1], 1);

    int t2 = pthread_create(&camDeux, NULL, loop, (void *)1);
    if(t2){
        Log("thread 2 n'a pas pu être créé");
        return 1;
    }

    int t1 = pthread_create(&camUn, NULL, loop, (void *)0);
    if(t1){
        Log("thread 1 n'a pas pu être créé");
        return 1;
    }

    initWebSocket();

    char e;
    scanf("%c", &e);

    doit_exit = 0;

    return 0;
}
