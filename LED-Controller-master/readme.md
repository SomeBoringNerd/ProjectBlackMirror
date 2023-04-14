#Code Arduino pour la barrière 

Ce code est destiné à être exécuté sur un microcontrôleur compatible avec la bibliothèque Arduino, utilisant un module WiFi, comme l'ESP32, pour créer un serveur web basé sur le protocole HTTP. Voici une explication détaillée de ce que fait ce code :

Inclusion des bibliothèques : Les bibliothèques WiFi.h et WebServer.h sont incluses pour permettre la communication WiFi et la création du serveur web.

Définition des constantes : La constante "ssid" est définie comme le nom du réseau WiFi auquel le microcontrôleur se connectera.

Création d'un objet WebServer : Un objet WebServer est créé sur le port 80, qui est le port par défaut pour les communications HTTP.

Définition des variables pour la gestion de la LED : Une variable "led" est définie pour stocker le numéro de broche de la LED, et une variable "etatLed" est définie pour stocker l'état actuel de la LED (allumée ou éteinte). Un tableau de chaînes de caractères "texteEtatLed" est également défini pour stocker les messages d'état de la LED.

Définition de la fonction "toggle" : Cette fonction est appelée lorsqu'une requête HTTP est effectuée sur l'URL "/toggle" du serveur. Elle inverse l'état de la LED (de allumée à éteinte ou vice versa), met à jour l'état de la LED et renvoie une réponse HTTP avec un en-tête de redirection vers la page d'accueil ("/") du serveur.

Configuration initiale dans la fonction "setup" : La fonction "setup" est une fonction spéciale de l'environnement Arduino qui est exécutée une seule fois au démarrage du microcontrôleur. Dans cette fonction, la communication série est initialisée, la broche de la LED est configurée en sortie et mise à l'état bas (éteinte), la connexion WiFi est établie en se connectant au réseau WiFi spécifié avec le mot de passe vide (""), et la fonction de gestion des requêtes sur l'URL "/toggle" est définie pour appeler la fonction "toggle". Enfin, le serveur web est démarré.

Boucle principale dans la fonction "loop" : La fonction "loop" est également une fonction spéciale de l'environnement Arduino qui est exécutée en boucle tant que le microcontrôleur est alimenté. Dans cette fonction, la fonction "handleClient" du serveur web est appelée pour gérer les requêtes HTTP entrantes.

En résumé, ce code crée un serveur web basé sur le protocole HTTP avec un microcontrôleur compatible avec la bibliothèque Arduino et un module WiFi, permettant de contrôler l'état d'une LED connectée à la broche 2 du microcontrôleur via un navigateur web. Lorsqu'une requête est effectuée sur l'URL "/toggle" du serveur, l'état de la LED est inversé (allumée ou éteinte), et un en-tête de redirection est renvoyé vers la page d'accueil du serveur.