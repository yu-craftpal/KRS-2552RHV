#include "ics3_servo.h"

IcsServo ics;

void setup() {
    
    Serial.begin(115200);
    ics.begin();

}

void loop() {

	Serial.println(ics.positionFree(1));

}
