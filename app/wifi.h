#include <WiFi.h>

class WifiConnection {
public:
  const char *SSID = "djsk";           // Nombre de la red
  const char *PASSWORD = "contrasena"; // Contraseña de la red

public:
  void init(void);                  // Funcion para inicializar la conexion WiFi
  String getConnectionStatus(void); // Funcion para obtener el estado de la conexión WiFi
};

void WifiConnection::init(void) {
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
}
