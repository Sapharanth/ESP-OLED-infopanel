# ESP-OLED-infopanel
The main idea is to turn it on, wait a few seconds, and receive up 7 key-value pairs on a SSD1306-based OLED screen. Written for 128x64 screens, but setting it up to work with smaller or bigger screens shouldn't be too much trouble.
Other than a ESP-01 or a ESP8266 development board of your choosing, a SSD-1306-controlled screen and power, it requires a MQQT broker and Node-RED to function as it is.

## How does this thing work?
- on powerup, connects to Wi-Fi and your MQQT broker using PubSubClient
- after connecting, sends a MQQT packet to your broker to request a properly-formatted JSON string
- (optionally, if you want it to receive updates continously, you can just subscribe to a topic which sends the data periodically)
- prints your data on the display, as demonstrated in the showcase. All values, and the right column's position is taken from the input JSON

## Required libraries

 * [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
 * [pubsubclient](https://github.com/knolleary/pubsubclient)
 * [esp8266-oled-ssd1306](https://github.com/ThingPulse/esp8266-oled-ssd1306)

## Setup

All important parts are commented in code. "ESP-SSD1306_infostation" is code you need to upload to your ESP8266, "Node-RED_function" is my function node which creates and passes the JSON string to a MQQT output node.

If you want to show an image on powerup, I recommend using GIMP to resize a vector image to 128x64 pixels, then exporting as "X Bitmap image". Be sure your file is formatted like "crest.h", include it, and you're done!

## Showcase

Changing the "position" value in source allows for moving the value column


![PIC1](https://github.com/Sapharanth/ESP-OLED-infopanel/blob/master/Images/SSD1306-preview%20(5).jpg)
![PIC2](https://github.com/Sapharanth/ESP-OLED-infopanel/blob/master/Images/SSD1306-preview%20(4).jpg)
![PIC3](https://github.com/Sapharanth/ESP-OLED-infopanel/blob/master/Images/SSD1306-preview%20(3).jpg)

And this is how my use-case looks like. CAQI is doubled until I set up another temperature sensor.


![PIC4](https://github.com/Sapharanth/ESP-OLED-infopanel/blob/master/Images/SSD1306-preview%20(1).jpg)