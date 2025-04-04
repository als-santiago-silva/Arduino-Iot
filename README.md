# Proyecto IOT

Este proyecto utiliza un NodeMCU ESP8266 para leer datos de un sensor LDR (sensor de luz) y enviar esa información a un broker MQTT. También permite controlar un LED de manera remota desde un mensaje MQTT.

# ¿Cómo funciona?

- El NodeMCU se conecta a la red WIFI.
- Se conecta al broker MQTT definido.
- Publica cada 5 segundos el valor leído del sensor LDR en el tema

# ¿Qué se usó?

- ESP8266WiFi.h: conexión WiFi del NodeMCU.
- PubSubClient.h: comunicación para MQTT.
- Broker MQTT local (Mosquitto).
- Sensor LDR conectado al pin A0.
- LED conectado al pin D1.

# ¿Cómo usarlo?

1. Carga el código en tu NodeMCU desde el IDE de Arduino.
2. Asegúrate de tener un broker MQTT funcionando (como mosquitto).
3. Cambia los valores de `ssid`, `password` y `mqtt_server` a los valores que te correspondan.
4. Abre el monitor serie para ver los datos del LDR (Baudios).
5. Publica en el tema `home/led/control` con `"ON"` o `"OFF"` para controlar el LED utilizando un cliente como MQTT explorer.
