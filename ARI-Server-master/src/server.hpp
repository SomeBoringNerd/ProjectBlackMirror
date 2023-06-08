#pragma once

#include "include/ws.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "logger.hpp"

ws_cli_conn_t *client;
int isClientLoggedIn = 0;

int port = 0;

/********************************************************************

        Base de donnée et autre joyeusetées

*********************************************************************/

/**
 * @brief Valide la connexion au serveur.
 */
void Login(char *username, char *password)
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
    if (client != NULL)
        return;

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
void onmessage(ws_cli_conn_t *_client, const unsigned char *msg, uint64_t msg_size, int type)
{
    char *cli, *con_ip;
    con_ip = ws_getaddress(_client);
    cli = ws_getaddress(client);

    if (cli != con_ip)
        return;
}
/**
 * @brief Wrapper de la fonction ws_sendframe_txt avec un check pour savoir si le client est connecté
 * @param message : message a envoyer au client actif
 */
void send(char *message)
{
    if (client != NULL || !isClientLoggedIn)
    {
        ws_sendframe_txt(client, message);
    }
    else
    {
        LogError("Tentative d'envoyer un message au serveur mais aucun client n'est connecté");
    }
}

void initWebSocket()
{
    struct ws_events evs;
    evs.onopen = &onopen;
    evs.onclose = &onclose;
    evs.onmessage = &onmessage;

    ws_socket(&evs, port, 0, 1000);
}