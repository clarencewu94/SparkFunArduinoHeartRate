#include <ArduinoBLE.h>

/*
  This example sketch gives you exactly what the SparkFun Pulse Oximiter and
  Heart Rate Monitor is designed to do: read heart rate and blood oxygen levels.
  This board requires I-squared-C connections but also connections to the reset
  and mfio pins. When using the device keep LIGHT and CONSISTENT pressure on the
  sensor. Otherwise you may crush the capillaries in your finger which results
  in bad or no results. A summary of the hardware connections are as follows:
  SDA -> SDA
  SCL -> SCL
  RESET -> PIN 4
  MFIO -> PIN 5

  Author: Elias Santistevan
  Date: 8/2019
  SparkFun Electronics

  If you run into an error code check the following table to help diagnose your
  problem:
  1 = Unavailable Command
  2 = Unavailable Function
  3 = Data Format Error
  4 = Input Value Error
  5 = Try Again
  255 = Error Unknown
*/

#include <SparkFun_Bio_Sensor_Hub_Library.h>
#include <Wire.h> 


// Reset pin, MFIO pin
int resPin = 4;
int mfioPin = 5;

unsigned int oldHeartRate = 0;

// Takes address, reset pin, and MFIO pin.
SparkFun_Bio_Sensor_Hub bioHub(resPin, mfioPin);

bioData body;
// ^^^^^^^^^
// What's this!? This is a type (like int, byte, long) unique to the SparkFun
// Pulse Oximeter and Heart Rate Monitor. Unlike those other types it holds
// specific information on your heartrate and blood oxygen levels. BioData is
// actually a specific kind of type, known as a "struct".
// You can choose another variable name other than "body", like "blood", or
// "readings", but I chose "body". Using this "body" varible in the
// following way gives us access to the following data:
// body.heartrate  - Heartrate
// body.confidence - Confidence in the heartrate value
// body.oxygen     - Blood oxygen level
// body.status     - Has a finger been sensed?

//ble heart rate service
//BLEService heartService("0x180D");
BLEService heartService("0000180d-0000-1000-8000-00805f9b34fb");

//BLE heart rate characteristic
BLEUnsignedCharCharacteristic heart_rate_measurement("0x2a37", BLERead | BLENotify); //0x2a37    //00002a37-0000-1000-8000-00805f9b34fb
//BLEUnsignedCharCharacteristic confidence("018D2", BLERead | BLENotify);
//BLEUnsignedCharCharacteristic oxygen("018D3", BLERead | BLENotify);
//BLEUnsignedCharCharacteristic fingerStatus("018D4", BLERead | BLENotify);

void setup() {

  Serial.begin(115200);

  // begin BLE initialization`
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  // set the local name peripheral advertises
  BLE.setLocalName("HeartRateMonitor");
  // set the UUID for the service this peripheral advertises
  BLE.setAdvertisedService(heartService);

  // add the characteristic to the service
  heartService.addCharacteristic(heart_rate_measurement);
  //heartService.addCharacteristic(confidence);
  //heartService.addCharacteristic(oxygen);
  //heartService.addCharacteristic(fingerStatus);

  // add service
  BLE.addService(heartService);
  heart_rate_measurement.writeValue(body.heartRate);
  //confidence.writeValue(body.confidence);
  //oxygen.writeValue(body.oxygen);
  //fingerStatus.writeValue(body.status);


  // assign event handlers for connected, disconnected to peripheral
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // start advertising
  BLE.advertise();

  Serial.println(("Bluetooth device active, waiting for connections..."));

  /////heart initialization
  Wire.begin();
  int result = bioHub.begin();
  if (result == 0) // Zero errors!
    Serial.println("Sensor started!");
  else
    Serial.println("Could not communicate with the sensor!!!");

  Serial.println("Configuring Sensor....");
  int error = bioHub.configBpm(MODE_ONE); // Configuring just the BPM settings.
  if (error == 0) { // Zero errors!
    Serial.println("Sensor configured.");
  }
  else {
    Serial.println("Error configuring sensor.");
    Serial.print("Error: ");
    Serial.println(error);
  }

  // Data lags a bit behind the sensor, if you're finger is on the sensor when
  // it's being configured this delay will give some time for the data to catch
  // up.
  Serial.println("Loading up the buffer with data....");
  delay(4000);

}

void loop() {

  // Information from the readBpm function will be saved to our "body"
  // variable.
  body = bioHub.readBpm();


  Serial.print("Heartrate: ");
  Serial.println(body.heartRate);
  Serial.print("Confidence: ");
  Serial.println(body.confidence);
  Serial.print("Oxygen: ");
  Serial.println(body.oxygen);
  Serial.print("Status: ");
  Serial.println(body.status);
  //heart_rate_measurement.writeValue(body.heartRate); 
   updateHeartRate();
  //confidence.writeValue(body.confidence);
  //oxygen.writeValue(body.oxygen);
  //fingerStatus.writeValue(body.status);

  // Slow it down or your heart rate will go up trying to keep up
  // with the flow of numbers
  delay(250);

  BLE.poll();






}


///////ble functions

void blePeripheralConnectHandler(BLEDevice central) {
  // central connected event handler
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
}

void updateHeartRate()
{
  unsigned int heartRate = body.heartRate;
  if(heartRate!= oldHeartRate)
  {
    heart_rate_measurement.writeValue(body.heartRate); 
    oldHeartRate = heartRate;
  }
}

/*don't need to write so we can delete

  ///change this to heart stuff!
  void switchCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  // central wrote new value to characteristic, update LED
  Serial.print("Characteristic event, written: ");

  if (switchCharacteristic.value()) {
    Serial.println("LED on");
    digitalWrite(ledPin, HIGH);
  } else {
    Serial.println("LED off");
    digitalWrite(ledPin, LOW);
  }

*/
