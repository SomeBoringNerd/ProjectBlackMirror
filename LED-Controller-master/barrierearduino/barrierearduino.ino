
#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "TRENDnet638";

WebServer server(80);

const int led = 2;
bool etatLed = 0;
char texteEtatLed[2][10] = {"ÉTEINTE!","ALLUMÉE!"};


void toggle()
{
    etatLed = (etatLed == 1 ? 0 : 1);
    digitalWrite(led, etatLed);
    server.sendHeader("Location","/");
    server.send(200);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n");

    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);

    WiFi.persistent(false);
    WiFi.begin(ssid, "");
    Serial.print("Tentative de connexion...");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }

    Serial.println("\n");
    Serial.println("Connexion etablie!");
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());

    server.on("/toggle", toggle);
    server.begin();
    delay(30000);

    Serial.println("Serveur web actif!");
}

void loop()
{
    server.handleClient();
}