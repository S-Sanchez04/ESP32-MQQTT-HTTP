#pragma once

#define WIFI_SSID "Santi's Iphone"
#define WIFI_PASS "farra2abril"

#define MQTT_BROKER "a3duh4slqgm2xv-ats.iot.us-east-2.amazonaws.com"
#define MQTT_PORT 8883
#define MQTT_TOPIC_CMD "carroESP32/instrucciones"
#define MQTT_TOPIC_SENSOR "carroESP32/sensor/hcsr04"

#define CERT_CA_PATH "/AmazonRootCA1.pem"
#define CERT_CRT_PATH "/certificate.pem.crt"
#define CERT_KEY_PATH "/private.pem.key"

#define HTTP_PORT 80
#define DEVICE_NAME "esp32-chucho"

#define ENA_PIN 25
#define IN1_PIN 26
#define IN2_PIN 27
#define ENB_PIN 14
#define IN3_PIN 12
#define IN4_PIN 13

#define TRIG_PIN 35
#define ECHO_PIN 34

#define SENSOR_PUB_PERIOD_MS 1000UL
