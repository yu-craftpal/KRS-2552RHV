#include "ics3_servo.h"

IcsServo ics;

void setup() {
    
    Serial.begin(115200);
    ics.init();
}

void loop() {

  Serial.println(ics.commandPositionFree(1));
  Serial.println(ics.commandPositionFree(2));

}
