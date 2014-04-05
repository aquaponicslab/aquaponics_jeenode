#include <JeeLib.h>
#include "BatterySensor.h"
#include "SHT11Sensor.h" 

int voltagePin = A1; // for battery
int controlPin = 5;  // for battery
byte port = 1;       // for SHT11

/*****************************************************
  EDIT FOR DIFFERENT COMBINATIONS OF SENSORS
*****************************************************/
  
BatterySensor batterySensor(voltagePin, controlPin);
SHT11Sensor sht11Sensor(port);

Sensor* sensors[] = {
  &batterySensor,
  &sht11Sensor
};

/*****************************************************/

int nodeId = 25;
int additionalDelay = 1000; // between each reading process 

// C way for getting size of array
int numSensors = sizeof(sensors) / sizeof(sensors[0]);

void setup() {
  for (int i = 0; i < numSensors; i ++) {
    sensors[i]->setup(); 
  }
  //setupRadio();
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < numSensors; i ++) {
    Serial.flush();
    delay(2);
    int *readings = sensors[i]->measure(); 
    //Serial.print(sensors[i]->getName());
    //Serial.print(": ");
    int numReadings = sizeof(readings) / sizeof(readings[0]);
    //Serial.println(numReadings);
    //Serial.println(readings[0]);
    //for (int j = 0; j < numReadings; j ++) {
      //Serial.print(readings[j]);
      //Serial.print(" ");
    //sendRadio(reading);
    //}
    //Serial.println("");
  }
  delay(additionalDelay);
}

void setupRadio() {
  rf12_initialize(nodeId, RF12_868MHZ, 101);
  rf12_easyInit(0);  
}

void sendRadio(int reading) {
  rf12_easyPoll();
  rf12_easySend(&reading, sizeof reading); 
}
