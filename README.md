# esp-netpie-serial

How to use
- Don't forget to set an aias i nthe code
- Connect any MCU to ESP8266 via RX and TX pins
- Send a message to an MCU using a usual microgear chat. The MCU will see the incoming serial message of this format :
```
TOPIC|MESSAGE
```
- The MCU can publish the message by writing its serial with the text of the same format i.e.
```
TOPIC|MESSAGE
```
- If needed, you may use TX1 instead of TX by
```
#defining TX Serial1
```
