#ifndef _INC_ICSSERVO
#define _INC_ICSSERVO

#include "arduino.h"

//コマンド定義
#define SERVO_SERIAL Serial1    //サーボと通信を行うクラス
#define CMD_POS      0x80       //サーボの角度を決めるコマンド
#define CMD_READ     0xA0       //サーボのパラメータを読み出すコマンド
#define CMD_WRITE    0xC0       //サーボのパラメータを書き込むコマンド
#define CMD_ID       0xE0       //サーボのID番号の読み出し＆書き込みコマンド
//コマンドヘッダ生成マクロ
#define GenCmdHead(cmd, id) ((unsigned char)(cmd)|(0x1F&(unsigned char)(id)))
//サブコマンド定義
#define SC_EEPROM    0x00       //サーボモータのROMに直接アクセスする
#define SC_STRC      0x01       //ストレッチデータを扱う
#define SC_SPD       0x02       //スピードデータを書き込む
#define SC_CUR       0x03       //電流地を読み出す，制限電流値を書き込む
#define SC_TMP       0x04       //サーボモータの温度値を読み出す，制限温度値を書き込む

typedef unsigned int position_t;

class IcsServo {
private:

    
public:

    //IcsServo();
    void init();
    int sendCommand(byte *senddata, int sendbyte, byte *revdata, int revbyte);
    position_t position(unsigned char id, unsigned int pos);
    position_t positionFree(unsigned char id);
    int getID();

};

#endif
