typedef unsigned int position_t;

position_t commandPosition(unsigned char id, unsigned int pos);

position_t commandPositionFree(unsigned char id);

#define SERVO_SERIAL Serial1

#define CMDHEAD_POS     0x80
#define CMDHEAD_READ    0xA0
#define CMDHEAD_WRITE   0xC0
#define CMDHEAD_ID      0xE0
#define GenCmd(cmd_head, id) ((unsigned char)(cmd_head)|(0x1F&(unsigned char)(id)))

// ID 0~31

position_t commandPosition(unsigned char id, unsigned int pos) {
    position_t res = 0;
    {
        char cmd = GenCmd(CMDHEAD_POS, id);
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

position_t commandPositionFree(unsigned char id) {
    return commandPosition(id, 0);
}

void setup() {
    
    Serial.begin(115200);
    SERVO_SERIAL.begin(115200,SERIAL_8E1);

}

void loop() {
    commandPosition(1,5800);
    commandPosition(2,5800);
    delay(3000);
    
    #if 0
    Serial.println("1:" + String(commandPosition(1,7000)));
    Serial.println("2:" + String(commandPosition(2,7000)));
    delay(1000);
    Serial.println("3:" + String(commandPosition(1,8000)));
    Serial.println("4:" + String(commandPosition(2,6000)));
    delay(1000);
    #else
    commandPosition(1,11110);
    delay(350);
    commandPosition(2,11110);
    delay(400);
    commandPosition(2,5800);
    delay(350);
    commandPosition(1,5800);
    delay(350);
    commandPosition(1,9783);
    commandPosition(2,9783);
    delay(400);
    commandPosition(1,5800);
    commandPosition(2,5800);
    delay(400);
    commandPosition(1,9783);
    commandPosition(2,9783);
    delay(400);
    commandPosition(1,5800);
    commandPosition(2,5800);    
    while(1){}
    //Serial.print("1:" + String(commandPosition(1,11110)) + ", ");
    //Serial.println("2:" + String(commandPosition(2,11110)));
    //delay(100);
    #endif

    
}
