#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <sys/wait.h>
#include <string.h>


#include "logger.h"

#include "include/ws.h"

/********************************************************************

                    todos

            -> bouger ips, port et plus encore dans un fichier de config

*********************************************************************/

// ip des deux caméras avec leur port
char* ips[2] = {"192.168.0.0", "192.168.0.0"};

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
/**
 * Ping une addresse ip pour savoir si une caméra est sur le réseau local.
 * 
 * @param ip : ip de l'appareil a ping (duh)
*/
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
/********************************************************************

                    gestion des events du websocket

*********************************************************************/
/**
 * @brief This function is called whenever a new connection is opened.
 * @param client Client connection.
 */
void onopen(ws_cli_conn_t *client)
{
    char *cli;
    cli = ws_getaddress(client);
    printf("Connection opened, addr: %s\n", cli);
}

/**
 * @brief This function is called whenever a connection is closed.
 * @param client Client connection.
 */
void onclose(ws_cli_conn_t *client)
{
    char *cli;
    cli = ws_getaddress(client);
    printf("Connection closed, addr: %s\n", cli);
}

/**
 * @brief Message events goes here.
 * @param client Client connection.
 * @param msg    Message content.
 * @param size   Message size.
 * @param type   Message type.
 */
void onmessage(ws_cli_conn_t *client, const unsigned char *msg, uint64_t size, int type)
{
    char *cli;
    cli = ws_getaddress(client);
    printf("I receive a message: %s (%zu), from: %s\n", msg,
        size, cli);

    sleep(2);
    ws_sendframe_txt(client, "hello");
    sleep(2);
    ws_sendframe_txt(client, "world");
}

/********************************************************************

                        fin events du socket

*********************************************************************/

int main()
{
    initLogger("ServerSoftware");
// système simple pour savoir si les cams sont en ligne

    int ignoreCamResult = 1;

    system("clear");
    if(!ignoreCamResult){

        int cam1 = pingCam(ips[0]);
        int cam2 = pingCam(ips[1]);

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
    }
    // création / gestion des threads

    // lancement du serveur websocket via notre fork de wsServer
    struct ws_events evs;
    evs.onopen    = &onopen;
    evs.onclose   = &onclose;
    evs.onmessage = &onmessage;

    ws_socket(&evs, 1337, 0, 1000);

    return 0;
}