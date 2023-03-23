#ifndef HEADER_CAM_CONTROL
#define HEADER_CAM_CONTROL

#include <stdio.h>
#include <string>
#include <stdlib.h>

#include "logger.hpp"

/********************************************************************

                                todos

        -> Fetch le contenu des caméras et le sauvegarder dans le dossier actif
                    
                                notes

        Ce fichier est lié au controle des caméras.

*********************************************************************/

/**
 * Ping une addresse ip pour savoir si une caméra est sur le réseau local.
 * 
 * @param ip : ip de l'appareil a ping (duh)
 * @param ping : determine ce que la fonction va faire (1 = Ping, 0 = télécharger image depuis la caméra)
 * @return : Succès de l'opération (1 = marche, 0 = fail)
*/
int execute(std::string ip, int ping)
{
    // on va essayer de ping l'ip passée une fois

    string cmd;// = 

    if(ping){
        cmd = "ping -c 1 " + ip + " -W 1 -q > /dev/null 2>&1";
    }else{
        cmd = "ffmpeg -y -i rtsp://" + ip + ":554 -frames:v 1 " + ip + ".jpg > /dev/null 2>&1";
    }

    // check le succès de la commande
    int status = system(cmd.c_str());  

    if (-1 != status) 
    {         
        // on retourne l'inverse de WEXITSTATUS (car 0 = succès, mais en C, 0 == false)
        // donc en inversant le status, on retourne 1 si le ping est répondu, 0 si time out
        int ping_ret = WEXITSTATUS(status); 
        return !ping_ret;
    }else{
        return 0;
    }
}

#endif