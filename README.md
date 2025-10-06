# Chucho control con HTTP y aviso a MQTT

# Integrantes
- Esteban Bernal
- Nicolas Almonacid
- Santiago Sánchez

Proyecto que implementa un controlador HTTP para un carro basado en ESP32, con publicación de instrucciones mediante el protocolo MQTT.

Permite enviar órdenes de movimiento (adelante, atrás, izquierda, derecha, detener) junto con parámetros de velocidad y duración, y además publica las instrucciones en un broker MQTT incluyendo la IP del cliente que las envió.

---

## 📋 Objetivos

- Exponer un único **endpoint HTTP** (`/move`) que reciba instrucciones de movimiento con velocidad y duración (máximo 5 segundos).
- Implementar un **endpoint de salud** (`/health`) para verificar el estado del servidor.
- Publicar las instrucciones recibidas en un **broker MQTT**, con los datos del movimiento y la IP del cliente.
- Documentar la API con **OpenAPI 3.0.0**.
- Generar un **diagrama de secuencia** explicativo.
- Publicar el proyecto en **GitHub** con documentación completa, colección Postman y recursos en carpeta `/docs`.

---

## 🧠 Tecnologías utilizadas

- **ESP32** (microcontrolador)
- **Arduino Framework**
- **WiFi.h** → conexión a red
- **WebServer.h** → servidor HTTP embebido
- **PubSubClient.h** → comunicación MQTT
- **HiveMQ** → broker MQTT público (`broker.hivemq.com`)

---

## ⚙️ Configuración del entorno

### 1️⃣ Requisitos

- Arduino IDE o PlatformIO.
- Librerías:
  - `WiFi.h` (incluida por defecto)
  - `WebServer.h`
  - `PubSubClient.h`

### 2️⃣ Configurar WiFi y MQTT en el código

```cpp
const char* ssid = "Santi's Iphone";
const char* password = "farra2abril";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "carroESP32/instrucciones";
