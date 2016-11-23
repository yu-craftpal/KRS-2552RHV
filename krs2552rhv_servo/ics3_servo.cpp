#include "ics3_servo.h"

void IcsServo::init(){
    SERVO_SERIAL.begin(115200,SERIAL_8E1);
}

int IcsServo::sendCommand(byte *senddata, int sendbyte, byte *revdata, int revbyte){
    unsigned long timeout = 10;
    int s, r, time1;
    int flag = 0;
    while(SERVO_SERIAL.available() > 0) SERVO_SERIAL.read();
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
    byte cmd_h = GenCmdHead(CMD_POS, id);
    byte pos_h = (pos & 0x3F80) >> 7;
    byte pos_l = (pos & 0x007F);
    byte sd[3] = {cmd_h, pos_h, pos_l};
    byte rev[3];
    if (sendCommand(sd, 3, rev, 3) == 1){
        byte r_cmd, tch_h, tch_l;
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

int IcsServo::getTmp(unsigned char id){
    byte sd[2] = {GenCmdHead(CMD_READ, id), SC_TMP};
    byte rev[3];
    int tmp;
    if (sendCommand(sd, 2, rev, 3) == 1){
        tmp = rev[2];
    }
    else{
        tmp = -1;
    }
    return tmp;
}
int IcsServo::setTmp(unsigned char id, unsigned char tmp){
    byte sd[3] = {GenCmdHead(CMD_WRITE, id), SC_TMP, byte(tmp)};
    byte rev[3];
    int revtmp;
    if (sendCommand(sd, 3, rev, 3) == 1){
        revtmp = rev[2];
    }
    else{
        revtmp = -1;
    }
    return revtmp;
}
int IcsServo::getID(){
    byte sd[4] = {0xFF, 0x00, 0x00, 0x00};
    byte rev[1];
    int id;
    if (sendCommand(sd, 4, rev, 1) == 1){
        id = rev[0] & 0b00011111;
    }
    else{
        id = -1;
    }
    return id;
}
int IcsServo::setID(unsigned char id){
    byte sd[4] = {GenCmdHead(CMD_ID, id), 0x01, 0x01, 0x01};
    byte rev[1];
    int revid;
    if (sendCommand(sd, 4, rev, 1) == 1){
        revid = rev[0] & 0b00011111;
    }
    else{
        revid = -1;
    }
    return revid;
}
