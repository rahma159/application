#include "RFIDAccessControl.h"

RFIDAccessControl::RFIDAccessControl()
    : lcd(0x27, 16, 2),
      mfrc522(SS_PIN, RST_PIN) {}

void RFIDAccessControl::begin() {
    Serial.begin(9600);
    lcd.begin();
    lcd.backlight();
    SPI.begin();
    mfrc522.PCD_Init();

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    myServo.attach(servoPin);
    myServo.write(0);

    resetDisplay();
}

void RFIDAccessControl::loop() {
    if (getID()) {
        lcd.clear();
        lcd.setCursor(0, 0);

        Serial.println("TAG:" + tagID);

        if (tagID == MasterTag) {
            displayAccessGranted();
        } else {
            displayAccessDenied();
        }

        lcd.setCursor(0, 1);
        lcd.print(" ID: " + tagID);

        delay(2000);
        digitalWrite(led2, LOW);
        digitalWrite(led1, LOW);
        myServo.write(0);

        resetDisplay();
    }
}

bool RFIDAccessControl::getID() {
    if (!mfrc522.PICC_IsNewCardPresent()) return false;
    if (!mfrc522.PICC_ReadCardSerial()) return false;

    tagID = "";
    for (uint8_t i = 0; i < 4; i++) {
        tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    tagID.toUpperCase();
    mfrc522.PICC_HaltA();
    return true;
}

void RFIDAccessControl::displayAccessGranted() {
    lcd.print(" Access Granted!");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    myServo.write(90);
    delay(1000);
}

void RFIDAccessControl::displayAccessDenied() {
    lcd.print(" Access Denied!");
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
}

void RFIDAccessControl::resetDisplay() {
    lcd.clear();
    lcd.print(" Access Control ");
    lcd.setCursor(0, 1);
    lcd.print("Scan Your Card>>
