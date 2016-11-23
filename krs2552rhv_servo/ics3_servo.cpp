#include "ics3_servo.h"

void IcsServo::init(){
    SERVO_SERIAL.begin(115200,SERIAL_8E1);
}

int IcsServo::sendCommand(char *senddata, int sendbyte, char *revdata, int revbyte){
    unsigned long timeout = 10;
    int s, r, time1;
    int flag = 0;
    for (s = 0; s < sendbyte; s++){
        time1 = millis();
        SERVO_SERIAL.write(senddata[s]);
        while(1){
            if((millis() - time1) > timeout){
                return 0;
            }
            if(SERVO_SERIAL.available() > 0){
                SERVO_SERIAL.read();
                break;
            }
        }
        
    }
    for (r = 0; r < revbyte; r++){
        time1 = millis();
        while(1){
            if((millis() - time1) > timeout){
                return 0;
            }
            if(SERVO_SERIAL.available() > 0){
                revdata[r] = SERVO_SERIAL.read();
                break;
            }
        }        
    }
    return 1;
}

// ID 0~31
position_t IcsServo::position(unsigned char id, unsigned int pos) {
    position_t res = 0;
    char cmd_h = GenCmdHead(CMD_POS, id);
    char pos_h = (pos & 0x3F80) >> 7;
    char pos_l = (pos & 0x007F);
    char sd[3] = {cmd_h, pos_h, pos_l};
    char rev[3];
    if (sendCommand(sd, 3, rev, 3) == 1){
        char r_cmd, tch_h, tch_l;
        r_cmd = rev[0]; 
        tch_h = rev[1];
        tch_l = rev[2];
        res = (tch_h << 7) | tch_l;
    }
    else{
        res = 0;
    }
    return res;
}

position_t IcsServo::positionFree(unsigned char id) {
    return position(id, 0);
}
