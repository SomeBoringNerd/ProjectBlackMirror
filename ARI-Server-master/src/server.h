#ifndef HEADER_SERVER
#define HEADER_SERVER

#include "include/ws.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

ws_cli_conn_t *client;
int isClientLoggedIn = 0;


int port = 34;


/********************************************************************

		Base de donnée et autre joyeusetées

*********************************************************************/

/**
 * @brief Valide la connexion au serveur. 
 */ 
void Login(char* username, char* password)
{
	
}

/********************************************************************

                    gestion des events du websocket

*********************************************************************/
/**
 * @brief Appelé quand une connexion est effecutée
 * @param client : connexion
 */
void onopen(ws_cli_conn_t *_client)
{
    // Si le client est déjà connecté on ne va pas accepter une connexion
    if(client != NULL) return;

    client = _client;
    isClientLoggedIn = true;
    char *cli;
    cli = ws_getaddress(client);
    Log("Connection opened\n");
}

/**
 * @brief Appelé quand le client se deconnecte
 * @param client Client connection.
 */
void onclose(ws_cli_conn_t *_client)
{
    char *cli;
    isClientLoggedIn = false;
    client = NULL;
    cli = ws_getaddress(client);
    Log("Connection closed, addr\n");
}

/**
 * @brief S'execute quand le serveur reçoit un message
 * @param client : Connexion
 * @param msg    Contenu du message
 */
void onmessage(ws_cli_conn_t *_client, const unsigned char msg, uint64_t size, int type)
{
    char *cli, *con_ip;
    con_ip = ws_getaddress(_client);
    cli =    ws_getaddress(client);

    if(cli != con_ip) return;

    if(msg == "test_comm")
    {
	Log("Message reçu du client");
    }
}


void initWebSocket()
{
    struct ws_events evs;
    evs.onopen    = &onopen;
    evs.onclose   = &onclose;
    evs.onmessage = &onmessage;

    ws_socket(&evs, port, 0, 1000);
}

#endif
