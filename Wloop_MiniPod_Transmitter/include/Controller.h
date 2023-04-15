#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {

private:

    // Analog values
    int x_val;
    int y_val;
    int yaw_val;
    int potPower;

    // Digital values
    bool mode1;
    bool mode2;
    bool EStop;
    bool functionBtn;

public:

    // Default contructor
    Controller();

    // returns the value of the joystick's x-axis (min: -100, max: 100)
    int getxVal();
    // returns the value of the joystick's y-axis (min: -100, max: 100)
    int getyVal();
    // returns the value of the joystick's yaw value (min: -100, max: 100)
    int getYawVal();
    // returns the value of the potentiometer (min: 0, max: 100)
    int getPower();

    // returns the state of the mode1 switch
    bool getMode1();
    // returns the state of the mode2 switch
    bool getMode2();
    // returns the state of the E-Stop button
    bool getEStop();
    // returns the state of the function button
    bool getFunctionBtn();

    // prints all controller input readings
    void printAll();

};
#endif