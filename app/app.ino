#include <HTTPClient.h>
#include <WiFi.h>

#define EMERGENCY_BUTTON 33
#define LED_ROJO 26
#define LED_VERDE 25

const char *SSID = "djsk";           // Nombre de la red
const char *PASSWORD = "contrasena"; // Contraseña de la red

void setup() {
  Serial.begin(115200);

  WiFi.begin(SSID, PASSWORD);
  delay(1000);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nSuccess WiFi connection");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(EMERGENCY_BUTTON, INPUT_PULLUP);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  if (digitalRead(EMERGENCY_BUTTON) == HIGH) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ROJO, HIGH);
  } else {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ROJO, LOW);
  }

  delay(2000);
}

void loop() {
  // If the button is pressed, turn on the red LED and turn off the green one. Otherwise, leave it as is.
  if (digitalRead(EMERGENCY_BUTTON) == LOW) { // Button is active LOW with pull-up resistor
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ROJO, HIGH);
    // enviar señal/alerta al servidor
  } else {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ROJO, LOW);
  }

  if (WiFi.status() == WL_CONNECTED) { // Check WiFi connection status

    HTTPClient http;
    String datos_a_enviar = "user=" + user + "&pass=" + pass;

    http.begin("http://ioticos.org/esp-post.php");                       // Indicamos el destino
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Preparamos el header text/plain si solo vamos a enviar texto plano sin un paradigma llave:valor.

    int codigo_respuesta = http.POST(datos_a_enviar); // Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)

    if (codigo_respuesta > 0) {
      Serial.println("" + String(codigo_respuesta)); // Print return code

      if (codigo_respuesta == 200) {
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);
      }

    } else {

      Serial.print("Error enviando POST, código: ");
      Serial.println(codigo_respuesta);
    }

    http.end(); // libero recursos

  } else {

    Serial.println("Error en la conexión WIFI");
  }
}
