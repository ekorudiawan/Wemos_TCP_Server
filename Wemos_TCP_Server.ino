#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

#define PORT 2000

WiFiClient client;
WiFiServer server(PORT);

char c;
String message;

const char *ssid = "WIFE";
const char *password = "15maret91";

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); 
  Serial.begin(115200);
  Serial.println("Wemos TCP Server");
  Serial.print("Listening Port : ");
  Serial.println(PORT);
  delay(100);

  // Koneksi ke akses point
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Access Point ...");
  // Tunggu sampai terkoneksi
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Tampilkan IP Address Wemos
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start TCP Server
  server.begin();
}

void loop()
{
  if (!client.connected()) {
    // Tunngu koneksi dari client
    client = server.available();
  }
  // Client terkoneksi
  while (client.connected()) {
    // Tampilkan data dari client ke serial port
    if (client.available()) {
      while (client.available() > 0) {
        c = (char)client.read();
        //Serial.print(c);
        message += c;
        if (message.equals("on")) {
          digitalWrite(LED_BUILTIN, LOW);
          //Serial.println("LED ON");
        }
        else if (message.equals("off")) {
          digitalWrite(LED_BUILTIN, HIGH);
          //Serial.println("LED OFF");
        }
      }
    }
    message = "";
  }
}
