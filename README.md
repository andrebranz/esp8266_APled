# esp8266APled
Allows to switch the integrated LED of the ESP8266 module on and off via the WiFi network created by the module.

To do this project we need:
- ESP8266 module
- Arduino software (https://www.arduino.cc/en/software)
- micro-USB cable

______
Set UP Arduino Software:

1- go to File > Settings and in the cell "Additional URLs for the tab manager" put this link : http://arduino.esp8266.com/stable/package_esp8266com_index.json
   press "Ok"
   
2- go to Tools > Board > Board Manager, search "wemos" and install the latest version

3- on Tools > Board > "upload speed" choose 115200

______________
Flash Code On Our device:

1- in the same page where we have done the set-up of arduino Software, paste the code

2- press Ctrl + Shift + s to save as a name, everywhere you want 

3- on Tools > Board > "port" choose the correct COM usb-Port

4- Press Ctrl + u to compile and flash the code on our ESP8266 module 

At the end of loading, we have to connect to our AP
Then we can go to the printed IP (on our serial monitor) and That's it 

