/*
 Name:		NodeMcu.ino
 Created:	2/4/2022 8:45:17 AM
 Author:	Koldborg
*/

#include "Light.h"
#include "LightStates.h"
#include <algorithm>
#include <vector>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <uri/UriBraces.h>


using namespace std;

const char* ssid = "NodeMCU_Station_Mode";
const char* password = "h5pd091121_Styrer";

ESP8266WebServer server(80);

vector<Light> Lights =
{
    Light(D7),
    Light(D6)
};

void setup()
{
    Serial.begin(115200);
    delay(100);

    for (int i = 0; i < Lights.size(); ++i)
        pinMode(Lights[i].Pin(), OUTPUT);

    Serial.println("Connecting to ");
    Serial.println(ssid);

    //connect to your local wi-fi network
    WiFi.begin(ssid, password);

    //check wi-fi is connected to wi-fi network
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected..!");
    Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

    server.on("/", handle_OnConnect);
    server.on(UriBraces("/ledon/{}"), handle_ledon);
    server.on(UriBraces("/ledoff/{}"), handle_ledoff);
    server.on(UriBraces("/ledblink/{}"), handle_ledblink);
    server.onNotFound(handle_NotFound);

    server.begin();
    Serial.println("HTTP server started");
}

void loop()
{
    server.handleClient();

    for (int i = 0; i < Lights.size(); ++i)
        Lights[i].Update();
}

void handle_OnConnect()
{
    for (int i = 0; i < Lights.size(); ++i)
        Lights[i].ChangeState(LightOff::Instance());

    server.send(200, "text/html", SendHTML(Lights));
}

void handle_ledon()
{
    String pin = server.pathArg(0);
    auto iterator = find_if(Lights.begin(), Lights.end(), [&](const Light& light) { return String(light.Pin()) == pin; });

    if (iterator == Lights.end()) {
        handle_NotFound();
    }
    else {
        (*iterator).ChangeState(LightOn::Instance());
        server.send(200, "text/html", SendHTML(Lights));
    }
}

void handle_ledoff()
{
    String pin = server.pathArg(0);
    auto iterator = find_if(Lights.begin(), Lights.end(), [&](const Light& light) { return String(light.Pin()) == pin; });

    if (iterator == Lights.end()) {
        handle_NotFound();
    }
    else {
        (*iterator).ChangeState(LightOff::Instance());
        server.send(200, "text/html", SendHTML(Lights));
    }
}

void handle_ledblink()
{
    String pin = server.pathArg(0);
    auto iterator = find_if(Lights.begin(), Lights.end(), [&](const Light& light) { return String(light.Pin()) == pin; });

    if (iterator == Lights.end()) {
        handle_NotFound();
    }
    else {
        (*iterator).ChangeState(LightBlink::Instance());
        server.send(200, "text/html", SendHTML(Lights));
    }
}

void handle_NotFound()
{
    server.send(404, "text/plain", "Not found");
}

String SendHTML(vector<Light> lights)
{
    String ptr = "<!DOCTYPE html> <html>\n";
    ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr += "<title>LED Control</title>\n";
    ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    ptr += ".button-on {background-color: #1abc9c;}\n";
    ptr += ".button-on:active {background-color: #16a085;}\n";
    ptr += ".button-off {background-color: #34495e;}\n";
    ptr += ".button-off:active {background-color: #2c3e50;}\n";
    ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    ptr += "</style>\n";
    ptr += "</head>\n";
    ptr += "<body>\n";
    ptr += "<h1>ESP8266 Web Server</h1>\n";
    ptr += "<h3>Using Station(STA) Mode</h3>\n";

    for (int i = 0; i < lights.size(); ++i)
    {
        Light light = lights[i];

        ptr += "<p>";
        ptr += String("PIN") + light.Pin() + ' ';
        ptr += String("Status: ") + light.Status ? "ON" : "OFF";
        ptr += "</p>";

        ptr += "<a class=\"button button-";
        ptr += light.Status ? "off" : "on";
        ptr += "\" href=\"/led";
        ptr += light.Status ? "off" : "on";
        ptr += "\\";
        ptr += light.Pin();
        ptr += "\">";
        ptr += light.Status ? "OFF" : "ON";
        ptr += "</a>";
    }

    ptr += "</body>\n";
    ptr += "</html>\n";
    return ptr;
}