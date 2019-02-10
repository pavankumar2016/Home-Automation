#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <DoubleResetDetect.h>


#define DRD_TIMEOUT 2.0
#define DRD_ADDRESS 0x00


const char *ssid = "LOCALCONTROL"; // You can change it according to your ease if you need to connect to the local webserver access
const char *password = "localcontrol"; // You can change it according to your ease if you need to connect to the local webserver access

const char *ssid1 = "pavan"; // You can change it according to your ease if you need to connect to the MQTT BROKER
const char *password1 = "pavan0819"; // You can change it according to your ease if you need to connect to the MQTT BROKER
const char* mqtt_server = "18.232.46.180";


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


ESP8266WebServer server(80); // establishing server at port 80 (HTTP protocol's default port)


// Writing a simple HTML page.
char HTML[] = "<html><body><h1>CONTROL</h1><a href=\"http://192.168.4.1/1\"> </a> <button><a href=\"toggle\"><button style=\"display: block; width: 50%;\">SWITCH-1-ON</a></button>   <button><a href=\"toggle1\"><button style=\"display: block; width: 50%;\">SWITCH-1-OFF</a></button>    <button><a href=\"toggle2\"><button style=\"display: block; width: 50%;\">SWITCH-2-ON</a></button>     <button><a href=\"toggle3\"><button style=\"display: block; width: 50%;\">SWITCH-2-OFF</a></button>   <button><a href=\"toggle4\"><button style=\"display: block; width: 50%;\">SWITCH-3-ON</a></button>   <button><a href=\"toggle5\"><button style=\"display: block; width: 50%;\">SWITCH-3-OFF</a></button>   <button><a href=\"toggle6\"><button style=\"display: block; width: 50%;\">SWITCH-4-ON</a></button>   <button><a href=\"toggle7\"><button style=\"display: block; width: 50%;\">SWITCH-4-OFF</a></button>        <button><a href=\"toggle8\"><button style=\"display: block; width: 50%;\">SWITCH-5-ON</a></button>      <button><a href=\"toggle9\"><button style=\"display: block; width: 50%;\">SWITCH-5-OFF</a></button>      <button><a href=\"toggle10\"><button style=\"display: block; width: 50%;\">SWITCH-6-ON</a></button>     <button><a href=\"toggle11\"><button style=\"display: block; width: 50%;\">SWITCH-6-OFF</a></button>     <button><a href=\"toggle12\"><button style=\"display: block; width: 50%;\">SWITCH-7-ON</a></button>     <button><a href=\"toggle13\"><button style=\"display: block; width: 50%;\">SWITCH-7-OFF</a></button>        <button><a href=\"toggle14\"><button style=\"display: block; width: 50%;\">SWITCH-8-ON</a></button>        <button><a href=\"toggle15\"><button style=\"display: block; width: 50%;\">SWITCH-8-OFF</a></button>       </body></html>"; // --> Simple HTML page


DoubleResetDetect drd(DRD_TIMEOUT, DRD_ADDRESS);

SoftwareSerial nodeserial(D1, D0); // RX ! TX

void setup()
{
    Serial.begin(115200);
    nodeserial.begin(115200);
 
  
    Serial.println("***************************************************************");
    Serial.println("** TO CONTROL WITH IN THE ROOM CLICK THE REST BUTTON ONCE  **");
    Serial.println("** TO CONTROL FROM ANYWHERE CLICK THE REST BUTTON DOUBLE  **");
    Serial.println("***************************************************************");



 if (drd.detect())
    {
        Serial.println("** Double reset boot **");
        Serial.println("** NOW YOU CAN CONTROL YOUR APPLICATION THROUGH THE MQTT SERVER **");

        Serial.begin(115200);
        
        client.setServer(mqtt_server, 1883);
        client.setCallback(callback);



        // TO SETUP WIFI
        delay(10);
        // We start by connecting to a WiFi network
        Serial.println();
        Serial.print("Connecting to ");

        Serial.println(ssid1);

        WiFi.begin(ssid1, password1);

        while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        }

        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());

        
        // Function to until we're reconnected
        while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
     
        // Attempt to connect
        if (client.connect("ESP8266Client")) {
        Serial.println("connected");
        // Once connected, publish an announcement...
        client.publish("outTopic", "SYSTEM READY");
        // ... and resubscribe
        client.subscribe("control");
        } 
        //    else {
        //      Serial.print("failed, rc=");
        //      Serial.print(client.state());
        //      Serial.println(" try again in 5 seconds");
        //      // Wait 5 seconds before retrying
        //      delay(5000);
        //         }
                }
              }

else
 {
  Serial.println("** Normal boot **");

  Serial.println("** NOW YOU CAN CONTROL YOUR APPLICATION THROUGH THE IP=[192.168.4.1] **");

          delay(100);
          Serial.begin(115200);
          Serial.println();
          
          Serial.print("Configuring access point...");
          /* You can remove the password parameter if you want the AP to be open. */
          WiFi.softAP(ssid, password); // --> This line will create a WiFi hotspot.
  

          IPAddress myIP = WiFi.softAPIP();
          Serial.print("AP IP address: ");
          Serial.println(myIP);
          server.on("/", handleRoot);
          // server.on("/1",Page1);
          server.on("/toggle",toggle);
          server.on("/toggle1",toggle1);
          server.on("/toggle2",toggle2);
          server.on("/toggle3",toggle3);
          server.on("/toggle4",toggle4);
          server.on("/toggle5",toggle5);
          server.on("/toggle6",toggle6);
          server.on("/toggle7",toggle7);
          server.on("/toggle8",toggle8);
          server.on("/toggle9",toggle9);
          server.on("/toggle10",toggle10);
          server.on("/toggle11",toggle11);
          server.on("/toggle12",toggle12);
          server.on("/toggle13",toggle13);
          server.on("/toggle14",toggle14);
          server.on("/toggle15",toggle15);
          server.begin();
          Serial.println("HTTP server started");
    }
 }


void callback(char* topic, byte* payload, unsigned int length) {
  
  Serial.print("Message arrived [");
  
  Serial.print(topic);
  Serial.print("] ");
  
  String recv_mesg;
   
  for (int i=0;i<length;i++) {
    Serial.println((char)payload[i]);
    recv_mesg+=(char)payload[i];
  }
  
  if (recv_mesg == "21"){
      Serial.println("ON");
      nodeserial.print(21);
      delay(500);
    }
  else if (recv_mesg == "20"){
      Serial.println("OFF");
      nodeserial.print(20);
      delay(500);
    }

    if (recv_mesg == "31"){
      Serial.println("ON");
      nodeserial.print(31);
      delay(500);
    }
  else if (recv_mesg == "30"){
      Serial.println("OFF");
      nodeserial.print(30);
      delay(500);
    }

   if (recv_mesg == "41"){
      Serial.println("ON");
      nodeserial.print(41);
      delay(500);
    }
  else if (recv_mesg == "40"){
      Serial.println("OFF");
      nodeserial.print(40);
      delay(500);
    }
    
   if (recv_mesg == "51"){
      Serial.println("ON");
      nodeserial.print(51);
      delay(500);
    }
  else if (recv_mesg == "50"){
      Serial.println("OFF");
      nodeserial.print(50);
      delay(500);
    }

  if (recv_mesg == "61"){
      Serial.println("ON");
      nodeserial.print(61);
      delay(500);
    }
  else if (recv_mesg == "60"){
      Serial.println("OFF");
      nodeserial.print(60);
      delay(500);
    }

    if (recv_mesg == "71"){
      Serial.println("ON");
      nodeserial.print(71);
      delay(500);
    }
  else if (recv_mesg == "70"){
      Serial.println("OFF");
      nodeserial.print(70);
      delay(500);
    }

    if (recv_mesg == "81"){
      Serial.println("ON");
      nodeserial.print(81);
      delay(500);
    }
  else if (recv_mesg == "80"){
      Serial.println("OFF");
      nodeserial.print(80);
      delay(500);
    }

   if (recv_mesg == "91"){
      Serial.println("ON");
      nodeserial.print(91);
      delay(500);
    }
  else if (recv_mesg == "90"){
      Serial.println("OFF");
      nodeserial.print(90);
      delay(500);
    }

    
}


void handleRoot() 
{
  server.send(200, "text/html",HTML);
}


void toggle()
{
 // LIGHT-01 ON
  nodeserial.print(21);
  server.send(200, "text/html",HTML);
}

void toggle1()
{
  //LIGHT-01-OFF
  nodeserial.print(20);
  server.send(200, "text/html",HTML);
}

void toggle2()
{
  //LIGHT-02-ON
  nodeserial.print(31);
  server.send(200, "text/html",HTML);
}


void toggle3()
{
  //LIGHT-02-OFF
  nodeserial.print(30);
  server.send(200, "text/html",HTML);
}

void toggle4()
{
  //LIGHT-03-ON
  nodeserial.print(41);
  server.send(200, "text/html",HTML);
}

void toggle5()
{
  //LIGHT-03-OFF
  nodeserial.print(40);
  server.send(200, "text/html",HTML);
}

void toggle6()
{
  //LIGHT-04-ON
  nodeserial.print(51);
  server.send(200, "text/html",HTML);
}

void toggle7()
{
  //LIGHT-04-OFF
  nodeserial.print(50);
  server.send(200, "text/html",HTML);
}


void toggle8()
{
  //LIGHT-05-ON
  nodeserial.print(61);
  server.send(200, "text/html",HTML);
}

void toggle9()
{
  //LIGHT-05-OFF
  nodeserial.print(60);
  server.send(200, "text/html",HTML);
}

void toggle10()
{
  //LIGHT-06-ON
  nodeserial.print(71);
  server.send(200, "text/html",HTML);
}

void toggle11()
{
  //LIGHT-06-OFF
  nodeserial.print(70);
  server.send(200, "text/html",HTML);
}

void toggle12()
{
  //LIGHT-07-OFF
  nodeserial.print(81);
  server.send(200, "text/html",HTML);
}

void toggle13()
{
  //LIGHT-07-OFF
  nodeserial.print(80);
  server.send(200, "text/html",HTML);
}

void toggle14()
{
  //LIGHT-08-OFF
  nodeserial.print(91);
  server.send(200, "text/html",HTML);
}

void toggle15()
{
  //LIGHT-08-OFF
  nodeserial.print(90);
  server.send(200, "text/html",HTML);
}
void loop() {
  server.handleClient();
  client.loop();


client.loop();

  if (!client.connected()) {
    drd.detect();
  }


   while (nodeserial.available() > 0) {
    float val = nodeserial.parseFloat();

    if (val == 10){
       client.publish("outTopic", "LED - 1 - FAULT ");
    }
    if (val == 20){
       client.publish("outTopic", "LED - 2 - FAULT ");
    }
    if (val == 30){
       client.publish("outTopic", "LED - 3 - FAULT ");
    }
    if (val == 40){
       client.publish("outTopic", "LED - 4 - FAULT ");
    }
    if (val == 50){
       client.publish("outTopic", "LED - 5 - FAULT ");
    }
    if (val == 60){
       client.publish("outTopic", "LED - 6 - FAULT ");
    }
    if (val == 70){
       client.publish("outTopic", "LED - 7 - FAULT ");
    }
    if (val == 80){
       client.publish("outTopic", "LED - 8 - FAULT ");
    }
   }   
}
