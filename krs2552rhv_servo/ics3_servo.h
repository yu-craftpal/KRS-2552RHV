#ifndef _INC_ICSSERVO
#define _INC_ICSSERVO

#include "arduino.h"

#define SERVO_SERIAL Serial1
#define CMDHEAD_POS     0x80
#define CMDHEAD_READ    0xA0
#define CMDHEAD_WRITE   0xC0
#define CMDHEAD_ID      0xE0
#define GenCmd(cmd_head, id) ((unsigned char)(cmd_head)|(0x1F&(unsigned char)(id)))

typedef unsigned int position_t;

class IcsServo {
private:
    

public:

    //IcsServo();
    void init();
    position_t commandPosition(unsigned char id, unsigned int pos);
    position_t commandPositionFree(unsigned char id);

};

#endif
