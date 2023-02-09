#ifndef HEADER_SERVER
#define HEADER_SERVER

#include "include/ws.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initWebSocket()
{
    struct ws_events evs;
    evs.onopen    = &onopen;
    evs.onclose   = &onclose;
    evs.onmessage = &onmessage;

    ws_socket(&evs, 1337, 0, 1000);
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
void onmessage(ws_cli_conn_t *client, const unsigned char *msg[10][128], uint64_t size, int type)
{
    char *cli;
    cli = ws_getaddress(client);

    ws_sendframe_txt(client, "hello");
}


#endif