#ifndef RFID_ACCESS_CONTROL_H
#define RFID_ACCESS_CONTROL_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

class RFIDAccessControl {
public:
    RFIDAccessControl();
    void begin();
    void loop();

private:
    // Pins
    const int led1 = 6;
    const int led2 = 7;
    const int servoPin = 8;
    const int RST_PIN = 9;
    const int SS_PIN = 10;

    // Components
    LiquidCrystal_I2C lcd;
    Servo myServo;
    MFRC522 mfrc522;

    // Tag configuration
    const String MasterTag = "C920D9A3";
    String tagID;

    bool getID();
    void displayAccessGranted();
    void displayAccessDenied();
    void resetDisplay();
};

#endif
