#include <ESP8266WiFi.h>
#include <PubSubClient.h>

String ssid     = "Alsacia";
String password = "Creativity on command";

const char* mqtt_server = "172.16.0.111";
const int mqtt_port = 1883;

const int ldrPin = A0;
const int led = D1;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqtt_callback);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  int rawData = analogRead(ldrPin);
  Serial.println(rawData);

  // Publicar el valor del LDR cada 5 segundos
  if (client.connected()) {
    char payload[50];
    sprintf(payload, "LDR Value: %d", rawData);
    client.publish("home/ldr", payload);
  }

  delay(5000);  // Espera de 5 segundos antes de la siguiente publicación
}

// Función para conectar al WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a WiFi...");
  WiFi.begin(ssid.c_str(), password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Conectado a WiFi!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

// Función de reconexión MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    
    if (client.connect("NodeMCUClient")) {
      Serial.println("Conectado a MQTT");

      client.subscribe("home/led/control");
    } else {
      Serial.print("Error de conexión, rc=");
      Serial.print(client.state());
      Serial.println(" Intentando nuevamente en 5 segundos");
      delay(5000);
    }
  }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido en el tema: ");
  Serial.println(topic);

  // Convertir el payload a un string
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.println("Mensaje: " + message);

  // Controlar el LED con el mensaje recibido
  if (String(topic) == "home/led/control") {
    if (message == "ON") {
      digitalWrite(led, HIGH);  // Encender LED
    } else if (message == "OFF") {
      digitalWrite(led, LOW);   // Apagar LED
    }
  }
}
