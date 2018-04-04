/************
ESP8266 Arduino Tutorial - Push notification messages example
Arduino code example


- replace the dots with your Wi-fi credentials and
- your deviceId from pushingBox account
Push Notifications using https://www.pushbullet.com

access token for tripathimanoj67@gmail.com --   o.bipNsBxg6cO6qbJwREAVOLDsihhZk3Pg
access token for tripathiarchana7571@gmail.com --   o.D7SdM4CGqoytH8MsEYmBMlMvUblK4Buz

“PushingBox is a cloud that can send notification, emails, tweets based on API calls in real time.”
*/
#include <ESP8266WiFi.h>
#include <gpio.h>

uint8_t PIN_1 = D0;
uint8_t PIN_2 = D1;
uint8_t PIN_3 = D2;
uint8_t PIN_4 = D3;

    // PushingBox scenario DeviceId code and API
    String deviceId = "vBFCE8905845D0BE";
const char *logServer = "api.pushingbox.com";

const char *ssid = "Annu";
const char *password = "rhicha04";

void setup()
{
    Serial.begin(115200);
    // Sending a notification to your mobile phone
    // function takes the message as a parameter
    //sendNotification("9 o'clock", "please take your Blood Pressure Medicin");
    pinMode(PIN_1, INPUT);
    pinMode(PIN_2, INPUT);
    pinMode(PIN_3, INPUT);
    pinMode(PIN_4, INPUT);
    initWifiClient();
}

void initWifiClient(){
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("- succesfully connected");
}

void sendNotification(String msg)
{

    Serial.println("- connecting to Home Router SID: " + String(ssid));
    Serial.println("- starting client");

    WiFiClient client;

    Serial.println("- connecting to pushing server: " + String(logServer));
    if (client.connect(logServer, 80))
    {
        Serial.println("- succesfully connected");

        String postStr = "devid=";
        postStr += String(deviceId);
        // postStr += "&time_from_msg=";
        // postStr += String(time);
        postStr += "&msg_text=";
        postStr += String(msg);

        Serial.println("- sending data...");

        client.print("POST /pushingbox HTTP/1.1\n");
        client.print("Host: api.pushingbox.com\n");
        client.print("Connection: close\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(postStr.length());
        client.print("\n\n");
        client.print(postStr);
    }
    client.stop();
    Serial.println("- stopping the client");
}

void loop() {
    if (digitalRead(PIN_1) == 1)
    {
        Serial.println("PIN_1");
        sendNotification("Its time To take your morning pill.");
    }
    if (digitalRead(PIN_2) == 1)
    {
        Serial.println("PIN_2");
        sendNotification("Its time To take your afternoon pill.");
    }
    if (digitalRead(PIN_3) == 1)
    {
        Serial.println("PIN_3");
        sendNotification("Its time To take your evening pill.");
    }
    if (digitalRead(PIN_4) == 1)
    {
        Serial.println("PIN_4");
        sendNotification("Its time To take your night pill.");
    }
}