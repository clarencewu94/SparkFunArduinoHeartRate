# SparkFunArduinoHeartRate
For Arduino

HEART RATE SENSOR: 
In this case, the SparkFun provides some example code to use which can be altered to match the specific functionality required. 
In this case, the example code used is Example1_config_BPM_MODE. 
Also on there website, the Library used is Sparkfun_bio_Sensor_Hub_library, both header and CPP file. 
Here are the links: Sparkfun bio sensor: 
1. https://learn.sparkfun.com/tutorials/sparkfun-pulse-oximeter-and-heart-rate-monitor-hookup-guide/all#sparkfun-bio-sensor-arduino-library 
or through their github: 
2.https://github.com/sparkfun/SparkFun_Bio_Sensor_Hub_Library

As this the Mbed libraries are currently being made and in progress, for now use the Arduino IDE with the indicated libraries.
The Libraries are too large and so there are two options to use in this project. 

Click on the Arduino IDE once Downloaded and open the Example1_config_BPM_MODE but change the extension to ino file. 
If needed the file is also included here as well. 

Once that is done, time to download the libraries. 
1. Launch the Arduino IDE, select File and then Preferences, then the Preference Dialog and add the following link to the Additional Boards Manager URLS Field:
https://github.com/stm32duino/BoardManagerFiles/raw/master/STM32/package_stm_index.json

![PreferencePAge](Screenshots/PreferencePage.jpg)

Go to Manage Libraries Tab and search for the library:
STM32duino Examples (at this time version 1.0.4) Install and the system should be able to run with STM boards.


For Manual libraries required (SPARKFUN Library cpp and H files), Simply Zip them up in a file. 
Go to Sketch, Include Library, Add a .ZIP and select the Zip file. 
![BoardLib](Screenshots/BoardLib.jpg)

In tools, adjust the board, Upload Method and the Port. 

Then modify the code as needed and upload the program to the board. The board should be able to run the code and will continue execution.
In our case, the heart rate should be running and going to Tools, serial monitor and if in the correct port, can show on console. 

