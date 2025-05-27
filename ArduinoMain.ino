#include "RFIDAccessControl.h"

RFIDAccessControl accessControl;

void setup() {
    accessControl.begin();
}

void loop() {
    accessControl.loop();
}
