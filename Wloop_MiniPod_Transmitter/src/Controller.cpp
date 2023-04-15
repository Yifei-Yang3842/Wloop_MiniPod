#include <Arduino.h>
#include "Controller.h"
#include "Constants.h"

Controller::Controller() {
    x_val = 0;
    y_val = 0;
    yaw_val = 0;
    potPower = 0;

    mode1 = true;
    mode2 = false;
    EStop = false;
    functionBtn = false;

    pinMode(JS_X_PIN, INPUT);
    pinMode(JS_Y_PIN, INPUT);
    pinMode(JS_YAW_PIN, INPUT);
    pinMode(POT_PIN, INPUT);
    pinMode(MODE_1_BTN, INPUT);
    pinMode(MODE_2_BTN, INPUT);
    pinMode(E_STOP_BTN, INPUT);
    pinMode(FN_BTN, INPUT);
}

int Controller::getxVal() {
    x_val = analogRead(JS_X_PIN);
    if (x_val <= 1900 && x_val >= 1850)
        x_val = 0;
    else if (x_val > 1900)
        x_val = map(x_val, MAX_ANLG, 1900, -100, 0);
    else 
        x_val = map(x_val, 1850, 0, 0, 100);
    return x_val;
}

int Controller::getyVal() {
    y_val = analogRead(JS_Y_PIN);
    if (y_val <= 1860 && y_val >= 1830)
        y_val = 0;
    else if (y_val > 1860)
        y_val = map(y_val, 1860, MAX_ANLG, 0, 100);
    else 
        y_val = map(y_val, 1830, 0, 0, -100);
    return y_val;
}

int Controller::getYawVal() {
    yaw_val = analogRead(JS_YAW_PIN);
    if (yaw_val <= 1900 && yaw_val >= 1770)
        yaw_val = 0;
    else if (yaw_val > 1900)
        yaw_val = map(yaw_val, 1900, MAX_ANLG, 0, 100);
    else 
        yaw_val = map(yaw_val, 1770, 0, 0, -100);
    return yaw_val;
}

int Controller::getPower() {
    potPower = analogRead(POT_PIN);
    potPower = map(potPower, 0, 4095, 0, 100);
    return potPower;
}

bool Controller::getMode1() {
    mode1 = analogRead(MODE_1_BTN) > 3000;
    return mode1;
}

bool Controller::getMode2() {
    mode2 = analogRead(MODE_2_BTN) > 3000;
    return mode2;
}

bool Controller::getEStop() {
    EStop = digitalRead(E_STOP_BTN);
    return EStop;
}

bool Controller::getFunctionBtn() {
    functionBtn = digitalRead(FN_BTN);
    return functionBtn;
}

void Controller::printAll() {
    int mode = mode1 ? 1 : 2;
    Serial.printf("Mode: %1d   FnBtn: %1d   EStop: %1d   speed: %3d   xVal: %3d   yVal: %3d   yawVal: %3d",
                    mode, functionBtn, EStop, potPower, x_val, y_val, yaw_val);
    Serial.println();
}