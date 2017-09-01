/*  A simple ESP-NETPIE serial proxy            */

#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = <SSID;
const char* password = <PASSWORD>;

#define APPID   <APPID>
#define KEY     <KEY>
#define SECRET  <SECRET>
#define ALIAS   <ALIAS>

#define RX Serial
#define TX Serial

char *p;
char buff[1024];
long lastconnect = 0;

WiFiClient client;

int timer = 0;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    msg[msglen] = '\0';
    strcpy(buff, topic);
    strcat(buff, "|");
    strcat(buff, (char *)msg);
    TX.println(buff);
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    microgear.setAlias(ALIAS);
}

void setup() {
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);
    RX.begin(115200);
    TX.begin(115200);
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
        }
    }
    microgear.init(KEY,SECRET,ALIAS);
    microgear.connect(APPID);
}

void loop() {
    if (microgear.connected()) {
        if (RX.available()) {
          RX.readBytesUntil('\n', buff, 1023);
          for (p=buff; *p!='\0'; p++)
            if (*p=='|') {
              *(p++) = '\0';
              break;
            }
          microgear.publish(buff, p);
        }
        microgear.loop();
      }
    else {
        if (millis() - lastconnect > 5000) {
            microgear.connect(APPID);
            lastconnect = millis();
        }
    }
}

