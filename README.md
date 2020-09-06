# ESP-OLED-infopanel
The main idea is to turn it on, wait a few seconds, and receive up 7 key-value pairs on a SSD1306-based OLED screen. Written for 128x64 screens, but setting it up to work with smaller or bigger screens should'nt be too much trouble.
Other than a ESP-01 or a development board of your choosing, a SSD-1306-controlled screen and power, it requires a MQQT broker and Node-RED to function. 


## How does this thing work?
- on powerup, connects to Wi-Fi and your MQQT broker using PubSubClient
- after connecting, sends a MQQT packet to your broker to request a properly-formatted JSON string
- (optionally, if you want it to receive updates continously, you can just subscribe to a topic which sends the data periodically)

## Required libraries

 * [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
 * [pubsubclient](https://github.com/knolleary/pubsubclient)
 * [esp8266-oled-ssd1306](https://github.com/ThingPulse/esp8266-oled-ssd1306)


## Showcase

Changing the "position" value in source allows for moving the value column


![PIC1](https://github.com/Sapharanth/ESP-OLED-infopanel/blob/master/Images/SSD1306-preview%20(5).jpg)
![PIC2](https://github.com/Sapharanth/ESP-OLED-infopanel/blob/master/Images/SSD1306-preview%20(4).jpg)
![PIC3](https://github.com/Sapharanth/ESP-OLED-infopanel/blob/master/Images/SSD1306-preview%20(3).jpg)

And this is how my use-case looks like. CAQI is doubled until I set up another temperature sensor.


![PIC4](https://github.com/Sapharanth/ESP-OLED-infopanel/blob/master/Images/SSD1306-preview%20(1).jpg)