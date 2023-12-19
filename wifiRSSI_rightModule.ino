#include <SoftwareSerial.h>
SoftwareSerial left(D8,D7);
int data1;
int data2;
#include <ESP8266WiFi.h>
//SSID of your network
char ssid[] = "*********";
//password of your WPA Network
char pass[] = "**********";
void setup() 
{
left.begin(9600);
Serial.begin(9600);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(10);

  WiFi.begin(ssid, pass);
  Serial.print("Connecting...");

  while (WiFi.status() != WL_CONNECTED)
 {
    delay(500);
    Serial.print(".");
  }

  // if you are connected, print out info about the connection:
  Serial.print("\nConnected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
}

void loop() 
{
int rssi = WiFi.RSSI();
int data1 = -(rssi);
Serial.print("LRSSI: ");
Serial.println(data1);
left.write(data1);
int data2 = left.read();
Serial.print("RRSSI: ");
Serial.println(data2);
left.write(data2);
delay(1000);
}
