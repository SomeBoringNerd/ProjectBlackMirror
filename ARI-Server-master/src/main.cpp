#define ALLOW_DATABASE 0

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdint.h>
#include <unistd.h>

#if ALLOW_DATABASE
#include "include/mysql/jdbc.h"
#endif

#include <string>
#include <cstdint>
#include <regex>

#include "logger.hpp"
#include "camControl.hpp"
#include "imgUtil.hpp"
#include "server.hpp"
#include "dataBase.hpp"

#include "mini/ini.h"

/********************************************************************

                                todos

        -> bouger ips, port et plus encore dans un fichier de config
        -> écrire code pour ping ARI-Plaques

                                notes

                                 N/A

*********************************************************************/

#define DEBUG_MODE 0

// ip des deux caméras avec leur port
std::string ips[2] = {"192.168.1.2", "192.168.0.4"};

// note : apparemment mettre les variables pthread_t en local fait un SIGDEV violation
pthread_t camUn, camDeux, exit_listener;

int doit_exit = 1;

int respond[2] = {0, 0};
/**
 * ping la caméra-ip a l'adresse donnée et fetch la dernière image disponible.
 * Celle-ci est sauvegardée dans le dossier d'éxecution
 *
 * @param ip : IP de la caméra
 * @return rien normalement
 */
void *loop(void *data)
{
    int _ip = (intptr_t)data;
    int old_response = 0;
    while (doit_exit)
    {
        if (isClientLoggedIn)
        {
            // si la caméra est en ligne
            respond[_ip] = execute(ips[_ip], 1);

            if (!respond[_ip])
            {
                if (old_response != respond[_ip])
                {
                    LogWarning("La caméra " + ips[_ip] + " est hors ligne");
                    send("WARNING_EXCEPTION_NO_CAM_FOUND");
                }
            }
            else
            {
                if (old_response != respond[_ip])
                {
                    Log("La caméra " + ips[_ip] + " est revenue en ligne");
                }

                if (!execute(ips[_ip], 0))
                {
                    send("ERROR_COULDNT_GET_IMAGE");
                    LogError("Impossible de récuperer une image de " + ips[_ip] + "(hors ligne ?)");
                    break;
                }
                else
                {
                    std::string plaque = getPlaque(ips[_ip] + ".jpg");

                    if (regex_match(plaque, std::regex("[A-Z][A-Z]-[0-9][0-9][0-9]-[A-Z][A-Z]")))
                    {
                        Log(plaque);
#if ALLOW_DATABASE
                        try
                        {
                            if (fetchDatabase(plaque))
                            {
                                Log("La plaque existe");
                                //@TODO : implémenter logique de communication
                            }
                            else
                            {
                                LogError("La plaque " + plaque + " n'existe pas dans la base de donnée");
                            }
                        }
                        catch (sql::SQLException &e)
                        {
                            LogError("Problème de base de donnée");
                            LogError("Erreur : (" + to_string(e.getErrorCode()) + ")\n" + e.what());
                        }
#endif
                    }
                }
            }

            old_response = respond[_ip];

            if (!doit_exit)
            {
                Log("Un thread vient d'être supprimé");
                pthread_exit(0);
            }
        }
    }
    LogWarning("Un thread vient d'être supprimé");
    return 0;
}

void initConfig()
{
    std::cout << "Lecture du fichier de config" << std::endl;

    mINI::INIFile file("config.ini");
    mINI::INIStructure ini;
    file.read(ini);

    ips[0] = ini["devices"]["cam1"];
    ips[1] = ini["devices"]["cam2"];

    port = stoi(ini["wsserver"]["ws_port"]);

    std::string ip_serveur = (ini["database"]["ip"]);
    std::string base_port = (ini["database"]["port"]);

    Log("IP de la première caméra : " + ips[0]);
    Log("IP de la deuxième caméra : " + ips[1]);
    Log("Port du websocket : " + std::to_string(port));
    std::cout << std::endl;
    Log("IP du serveur : " + ip_serveur);
    Log("Port de la base de données : " + base_port);
}

int main()
{
    // Lors du debug, j'ai vu que WSserver a besoin d'être executé en root
    // mais ça empêche le dossier du logger d'être supprimé
    // @TODO : faire en sorte que le dossier des logs n'appartienne pas a root
    if (getuid())
    {
        printf("\033[0;31m");
        printf(" [ERROR] CE LOGICIEL DOIT ÊTRE LANCÉ EN ROOT");
        printf("\n\033[0;0m");
        return 1;
    }

    initLogger("ServerSoftware");
    initConfig();

    doit_exit = 1;

// système simple pour savoir si les cams sont en ligne
#if !DEBUG_MODE

    respond[0] = execute(ips[0], 1);
    respond[1] = execute(ips[1], 1);

    if (respond[0])
    {
        int t1 = pthread_create(&camUn, NULL, loop, (void *)0);
        if (t1)
        {

            Log("thread 1 n'a pas pu être créé");
            return 1;
        }
        else
        {
            Log("Le thread cam 1 a été créé");
        }
    }
    else
    {
        Log("La caméra n'a pas répondu au ping");
    }

    if (respond[1])
    {
        int t2 = pthread_create(&camDeux, NULL, loop, (void *)1);
        if (t2)
        {

            Log("thread 2  n'a pas pu être créé");
            return 1;
        }
        else
        {
            Log("Le thread cam 2 a été créé");
        }
    }
    else
    {
        Log("La caméra n'a pas répondu au ping");
    }

    initWebSocket();

#endif
#if ALLOW_DATABASE
    initDatabase();
#endif
    char e;
#if DEBUG_MODE

    Log("[TEST] SÉRIES DE TESTS POUR LE LOGICIEL SERVEUR");
    std::cout << std::endl;

    Log("[TEST] Cette batterie de tests utilise une image pré-définie pour debug le programme.");
    Log("[TEST] Si vous voyez ce message en production, mettez DEBUG_MODE sur 0");
    std::cout << std::endl;
    Log("[TEST] Plaque choisie pour le test : GD-144-QH");
    Log("[TEST] Nom du fichier : 2.jpg");

    std::string plaque = getPlaque("2.jpg");
    std::string plaque2 = "GD-144-QH";

    Log("[TEST] Texte detecté : " + plaque);
    if (plaque.find(plaque2) != std::string::npos)
    {
        Log("[TEST] L'image test.jpg contient la plaque choisie pour les tests");
        std::cout << std::endl;
        LogError("[TEST] Le logiciel n'est pas encore capable de se connecter a la base de données");
        Log("[TEST] tout les tests sont passés !");
    }
    else
    {
        LogError("[TEST] L'image 3.jpg ne contient pas la plaque, il s'agit d'une erreur.");
    }

    return 0;
#endif

    scanf("%c", &e);

    doit_exit = 0;

    return 0;
}
