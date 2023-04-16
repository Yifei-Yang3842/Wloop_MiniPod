#include <Wire.h>
#include <VL53L1X.h>
#include "Constants.h"
#include "Lidar.h"

Lidar::Lidar() {
    target = 150.0; // Default target distance is 150 mm
    VL53L1X sensor;
}

void Lidar::initialize(int XShutPin, int I2CAddress) {

    sensor.setTimeout(500);
    sensor.init();
    Serial.print("hello");
    sensor.setDistanceMode(VL53L1X::Long);
    sensor.setMeasurementTimingBudget(30000);
    sensor.startContinuous(30);
    Serial.print("HHH");

    /*digitalWrite(XShutPin, LOW);
    pinMode(XShutPin, INPUT);
    delay(10);
    if (!sensor.init())
        while(1);
    sensor.setDistanceMode(VL53L1X::Long);
    sensor.setMeasurementTimingBudget(30000);
    sensor.setAddress(I2CAddress);
    sensor.startContinuous(40);*/
}

void Lidar::setTarget(float newTarget) {
    target = newTarget;
}

int Lidar::measureDistance() {
    distance = sensor.read();
    return distance;
}

int Lidar::steer() {
    distance = measureDistance();
    int error = (distance - target);
    if (error > target)
        error = target;
    else if (error <  -target)
        error = -target;
    return (error/target)*100*LIDAR_Kp;
}