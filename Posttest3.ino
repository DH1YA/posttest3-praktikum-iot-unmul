#include <ThingSpeak.h> 
#include <ESP8266WiFi.h> 
#include <WiFiClient.h> 
#include <DHT.h> 
#include<ESP8266WebServer.h>

#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

unsigned int value;
const char *ssid = "Universitas Mulawarman"; //setting nama wifi 
const char *password = ""; //password wifi 
WiFiClient client;

ESP8266WebServer server(80);
String webpage; 

unsigned long channel = 2477540; //ID akun ThingSpeak
const char * myWriteAPIKey = "SNCYYXR5E1XY9OPD"; //memasukan apikey
uint8_t temperature; //temperature dengan tipe unsigned 8-bit.

const int BUZZER_PIN = D6;
const int YELLOW_LED = D2;
const int GREEN_LED = D3;
const int RED_LED = D1;

void setup() {
  Serial.begin(9600); //memulai komunikasi serial dengan baud rate 115200
  dht.begin(); //memulai sensor DHT.
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //menghubungkan dengan wifi router
  while (WiFi.status() != WL_CONNECTED){ //Cek koneksi Wifi.
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);

}

void loop() {

  float t = dht.readTemperature();

  if (t > 36){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    tone(BUZZER_PIN, 10);
  }
  else if(t < 30){
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    noTone(BUZZER_PIN);
  }
  else {
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    noTone(BUZZER_PIN);
  }

  ThingSpeak.writeField(channel, 1, t, myWriteAPIKey); 

  delay(100);

}
