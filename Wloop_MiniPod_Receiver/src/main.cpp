#include <Arduino.h>
#include <esp_now.h>
#include <Lidar.h>
#include <WiFi.h>
#include <Wire.h>
#include "Constants.h"
#include "Drivetrain.h"

// Create a drivetrain object (which is the pod duh)
Drivetrain pod;

// Create two lidar objects (the sensors)
Lidar l1;
Lidar l2;

// Data structure of received package
typedef struct dataPack {
  int jStick_x;
  int jStick_y;
  int jStick_yaw;
  int BLDCPower;

  int mode;
  bool EStop;
  bool FunctionButton;
} dataPack;

// Create structured dataPack object
dataPack data;

//Callback when data is received
void OnDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));
  // Code that will run everytime data is received -----------------------------------------------

  // E-Stop exception
  if (data.EStop) {
    while(1) {
      pod.stopAll();
      delay(20);
    }
  }

  switch(data.mode) {
  case 1: // Manual mode
    pod.setBLDCSpeed(data.BLDCPower);
    pod.setSteer((data.jStick_x + data.jStick_yaw)/2, 
                  (data.jStick_x - data.jStick_yaw)/2);
    pod.setTravel(data.jStick_y);
    break;

  case 2: // Auto-guidance?
    // code block
    /*pod.setBLDCSpeed(data.BLDCPower);
    pod.setSteer(l1.steer(), l2.steer());
    pod.setTravel(data.jStick_y);
    delay(35);*/
    pod.stopAll();
    break;

  default: // Manual mode
    pod.setBLDCSpeed(data.BLDCPower);
    pod.setSteer((data.jStick_x + data.jStick_yaw)/2, 
                  (data.jStick_x - data.jStick_yaw)/2);
    pod.setTravel(data.jStick_y);

  }

}

void setup() {


  /* Set RX0 and TX0 as GPIO
  Serial.begin(9600); // initialize Serial communication
  Serial.end(); // RX0 & TX0 are no longer used for serial comm.
  pinMode(RX0, OUTPUT);
  pinMode(TX0, OUTPUT); */

  /* Begin I2C comm.
  Wire.begin();
  Wire.setClock(400000); 

  l1.initialize(RX0, 0x29);
  l2.initialize(TX0, 0X30);*/

  pod.initializeAll();
  // Set ESP32 controller board as WiFi station
  WiFi.mode(WIFI_STA);
  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Do not write the main code here, this loop only handles signal loss
  // Pod behavior should be specified in the ESP-NOW callback function
}