#include "ics3_servo.h"

void IcsServo::init(){
    SERVO_SERIAL.begin(115200,SERIAL_8E1);
}

// ID 0~31
position_t IcsServo::position(unsigned char id, unsigned int pos) {
    position_t res = 0;
    {
        char cmd = GenCmdHead(CMD_POS, id);
        char pos_h = (pos & 0x3F80) >> 7;
        char pos_l = (pos & 0x007F);
        
        SERVO_SERIAL.write(cmd);
        while(!SERVO_SERIAL.available());SERVO_SERIAL.read();
        SERVO_SERIAL.write(pos_h);
        while(!SERVO_SERIAL.available());SERVO_SERIAL.read();
        SERVO_SERIAL.write(pos_l);
        while(!SERVO_SERIAL.available());SERVO_SERIAL.read();
    }
    {
        char r_cmd, tch_h, tch_l;
        while(!SERVO_SERIAL.available());r_cmd = SERVO_SERIAL.read();
        while(!SERVO_SERIAL.available());tch_h = SERVO_SERIAL.read();
        while(!SERVO_SERIAL.available());tch_l = SERVO_SERIAL.read();
        res = (tch_h << 7) | tch_l;
    }
    return res;
}

position_t IcsServo::positionFree(unsigned char id) {
    return position(id, 0);
}
