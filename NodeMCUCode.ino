#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <BlynkSimpleEsp8266.h>

// Update these with values suitable for your network.

const char* auth = "_COnTjjQz48sXCusaUzxUbMWFqEqrVH5"; //Blynk Auth Token
const char* ssid = "mFi_0563C0"; // Wifi Username
const char* password = "1234567890"; //Wifi Password
const char* mqtt_server = "Broker.mqttdashboard.com";
const char* outTopic = "Group02/outT";
const char* inTopic = "Group02/inT";

int motor = D1; // GPIO5
String incomingByte;

WiFiServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {
  
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started");
}


void callback(char* topic, byte* payload, unsigned int length) {
 
  if ((char)payload[0]=='2'){
    digitalWrite(motor, HIGH);
  }else if ((char)payload[0]=='1'){
    digitalWrite(motor, LOW);
  }
  client.loop();  
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() {
  Serial.begin(115200);

  Blynk.begin(auth, ssid, password);
  
  pinMode(motor, OUTPUT);
  digitalWrite(motor, LOW);
  
  setup_wifi();
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


void loop() {
  Blynk.run();
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  while(!client.available()){
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');

  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/MOTOR=ON") != -1)  {
    digitalWrite(motor, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/MOTOR=OFF") != -1)  {
    digitalWrite(motor, LOW);
    value = LOW;
  }
 
// Set motor according to the request
//digitalWrite(motor, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Motor is now: ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/MOTOR=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/MOTOR=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
}
