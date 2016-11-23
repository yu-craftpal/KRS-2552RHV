#include "ics3_servo.h"

IcsServo ics;

void setup() {
    
    Serial.begin(115200);
    ics.init();
    Serial.println(ics.getTmp(2));
}

void loop() {

  //Serial.println(ics.positionFree(1));
  //Serial.println(ics.positionFree(2));

}
