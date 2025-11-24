🏎️ Chucho Control + Sensor Ultrasonido HC-SR04
===============================================

Este proyecto implementa un sistema basado en **ESP32** que permite controlar un vehículo robótico mediante peticiones HTTP, publicar comandos y telemetría a un broker MQTT (**AWS IoT Core**), y medir distancias utilizando un sensor ultrasónico **HC-SR04**.

👥 Integrantes
--------------

*   **Esteban Bernal**
    
*   **Nicolás Almonacid**
    
*   **Santiago Sánchez**
    

🎯 Objetivos
------------

*   **API HTTP:** Exponer endpoints /api/v1/\* para recibir instrucciones de movimiento y verificar el estado del sistema (_healthcheck_).
    
*   **Puente MQTT:** Publicar cada instrucción recibida vía HTTP en el tópico carroESP32/instrucciones.
    
*   **Telemetría:** Medir la distancia con el sensor HC-SR04 y reportarla periódicamente en el tópico carroESP32/sensor/hcsr04.
    
*   **Configuración Modular:** Mantener la configuración organizada mediante variables de preprocesador (#define) en config.h.
    

🏗 Arquitectura General
-----------------------

### **ESP32**

1.  Actúa como cliente **WiFi** (Station Mode).
    
2.  Levanta un **servidor HTTP** en el puerto 80.
    
3.  Se conecta a **AWS IoT Core** usando TLS (WiFiClientSecure + certificados en certificates.h).
    

### **Componentes**

*   **API HTTP (On-board):** Controla los motores del carro (/move, /stop) y el estado (/health).
    
*   **MQTT (AWS IoT):**
    
    *   Publica las instrucciones procesadas en carroESP32/instrucciones.
        
    *   Publica mediciones del ultrasonido en carroESP32/sensor/hcsr04.
        

### **Diagrama de Secuencia**

> El flujo detallado se encuentra en la carpeta de documentación.
> 
> *   **Código Mermaid:** docs/diagrama\_secuencia.md
>     
> *   **Imagen:** docs/diagrama\_secuencia.png
>     

**Flujo Principal:**

1.  **Cliente HTTP** (Postman/App) envía POST /api/v1/move.
    
2.  **ESP32** valida parámetros, activa motores y publica el evento en MQTT.
    
3.  **Suscriptor MQTT** (Backend/Script) recibe la notificación del comando.
    
4.  **ESP32 (Paralelo)** lee el sensor HC-SR04 y publica la distancia periódicamente.
    

🔌 Endpoints API
----------------

*   **Base URL:** /api/v1
    
*   **CORS:** Todos los endpoints incluyen headers CORS y soportan el método OPTIONS.
    

### 1\. Mover el Carro

Inicia el movimiento de los motores según los parámetros indicados.

*   **Endpoint:** POST /api/v1/move
    
*   **Parámetros** (Query String o x-www-form-urlencoded):
    

**ParámetroTipoDescripciónValores / Rango**directionStringDirección del movimientoforward, backward, left, rightspeedIntPotencia del motor (PWM)0 - 255durationIntTiempo de ejecución en ms0 - 5000

*   **Respuestas:**
    
    *   200 OK: Movimiento iniciado correctamente.
        
    *   400 Bad Request: Faltan parámetros o dirección inválida.
        

**Ejemplo de llamada:**

HTTP

`   POST http:///api/v1/move?direction=forward&speed=180&duration=1500   `

### 2\. Detener el Carro

Detiene inmediatamente los motores y envía el evento de parada a MQTT.

*   **Endpoint:** POST /api/v1/stop
    
*   **Parámetros:** Ninguno.
    
*   **Respuesta:** 200 OK ("Stopped + sent to AWS").
    

### 3\. Healthcheck

Verifica si el dispositivo está en línea y respondiendo.

*   **Endpoint:** GET /api/v1/health
    
*   **Respuesta:**
    

JSON

`   { "status": "ok" }   `

📡 Interacción MQTT
-------------------

Los tópicos están definidos en config.h. El ESP32 actúa principalmente como **publicador**.

### 1\. Reporte de Instrucciones

Cada vez que se llama a /move o /stop, el ESP32 publica la acción realizada.

*   **Tópico:** carroESP32/instrucciones
    
*   **Payload (Ejemplo Move):**
    

JSON

`   {     "direction": "forward",     "speed": 180,     "duration": 1500,     "source": "http"   }   `

*   **Payload (Ejemplo Stop):**
    

JSON

`   {     "direction": "stop",     "speed": 0,     "duration": 0,     "source": "http"   }   `

### 2\. Sensor Ultrasónico (HC-SR04)

Tarea periódica que reporta la distancia medida frente al vehículo.

*   **Tópico:** carroESP32/sensor/hcsr04
    
*   **Payload:**
    

JSON

`   {     "device": "esp32-chucho",     "distance_cm": 25.3,     "ts": 12345   }   `

🛠 Librerías Utilizadas
-----------------------

El proyecto hace uso de las siguientes librerías en main.ino:

*   WiFi.h: Gestión de conexión WiFi (Core ESP32).
    
*   WebServer.h: Servidor HTTP ligero.
    
*   WiFiClientSecure.h: Cliente con soporte TLS (necesario para AWS IoT).
    
*   PubSubClient.h: Cliente MQTT ligero.
    

**Archivos locales:**

*   config.h: Constantes de configuración (Pines, WiFi, MQTT).
    
*   certificates.h: Certificados CA, Cliente y Llave Privada.
    

⚠️ Limitaciones Actuales
------------------------

*   **Seguridad HTTP:** Los endpoints no tienen autenticación y el tráfico viaja en texto plano.
    
*   **Bloqueo:** La reconexión a WiFi/MQTT usa bucles con delay(), lo que puede bloquear el flujo principal momentáneamente.
    
*   **Movimiento:** La velocidad (0-255) no está calibrada a unidades físicas (m/s).
    
*   **Lógica del Sensor:** El HC-SR04 reporta datos pero no detiene el carro automáticamente ante obstáculos.
    
*   **Actualizaciones:** No soporta OTA; requiere conexión USB para reprogramar.
    

🚀 Posibilidades de Mejora (Roadmap)
------------------------------------

*   \[ \] Implementar Suscripción MQTT para control remoto desde la nube.
    
*   \[ \] Añadir autenticación (API Key) y HTTPS en el servidor web.
    
*   \[ \] Frenado de emergencia local basado en la lectura del HC-SR04.
    
*   \[ \] Interfaz web embebida (HTML/JS) servida directamente desde el ESP32.
    
*   \[ \] Portal de configuración (WiFi Manager) para evitar recompilar al cambiar de red.
    
*   \[ \] Refactorización a una arquitectura de clases (C++) para separar Hardware, Red y API.
    

📊 Uso de Memoria
-----------------

Valores aproximados tras la compilación en Arduino IDE / PlatformIO:

Plaintext

`   Uso de memoria de programa (Flash): xxx.xxx bytes (YY% de la memoria disponible).  Uso de memoria dinámica (RAM):      yyy.yyy bytes (ZZ% de la memoria disponible).   `

_(Reemplazar con los valores reales al compilar)_

🧪 Cómo Probar el Sistema
-------------------------

1.  **Hardware:** Conectar el ESP32 vía USB.
    
2.  **Monitor Serie:** Abrir a 115200 baudios. Verificar conexión a WiFi y AWS IoT.
    
3.  **Healthcheck:** Ir al navegador http:///api/v1/health → Debería retornar {"status":"ok"}.
    
4.  Bashcurl -X POST "http:///api/v1/move?direction=forward&speed=200&duration=1000"
    
5.  **Verificar MQTT:**
    
    *   Usar un cliente como **MQTTX** suscrito a carroESP32/#.
        
    *   Confirmar recepción del JSON de instrucción y lecturas del sensor.
