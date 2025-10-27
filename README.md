# Chucho Control + Sensor Ultrasonido HC-SR04

## Integrantes
- Esteban Bernal  
- Nicolás Almonacid  
- Santiago Sánchez  

Proyecto basado en **ESP32** que permite **controlar un carro por HTTP**, publicar comandos a **MQTT**, y **medir distancia con un sensor ultrasonido HC-SR04**, reportando periódicamente esa distancia al broker MQTT.

---

## Objetivos

- Exponer un endpoint HTTP `/move` para instrucciones de movimiento del carro.  
- Publicar cada instrucción recibida en el tópico MQTT:  
  - `carroESP32/instrucciones`
- Leer continuamente el sensor HC-SR04 y publicar resultados en:  
  - `carroESP32/sensor/hcsr04`
- Mantener configuración del sistema organizada mediante **variables de preprocesador (`#define`)**, ubicadas en `config.h`.
- Simulación o uso real del sensor físico ⚠️ con precauciones de voltaje en el pin ECHO.

---

## Características principales

| Funcionalidad | Protocolo | Tema / Endpoint |
|---------------|------------|-----------------|
| Control de movimiento | HTTP | `/move` |
| Healthcheck | HTTP | `/health` |
| Publicación de comandos | MQTT | `carroESP32/instrucciones` |
| Publicación de distancia del HC-SR04 | MQTT | `carroESP32/sensor/hcsr04` |

El sensor se ejecuta periódicamente cada `SENSOR_PUB_PERIOD_MS` (1s por defecto).

Ejemplo de JSON publicado:
```json
{
  "device": "esp32-chucho",
  "distance_cm": 25.3,
  "ts": 12345
}
