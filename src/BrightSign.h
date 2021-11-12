#include "Arduino.h"

#define BAUD_RATE     115200
#define STX           0x02
#define ETX           0x03

#define ERROR         0x00
#define OK            0x01
#define ONLINE        0x02
#define MEDIA_ENDED   0x08

class BrightSign
{
public:
BrightSign(HardwareSerial &serial);
void    play(String file);
void    volume(int percentage);
void    pause();
void    reboot();
void    resume();
void    update();
void    stop();
void    debug()               {bs_debug = true;}
boolean online()              {return bs_online;}
boolean media_ended()         {return bs_media_ended;}

private:
HardwareSerial* bs_serial;
boolean bs_error = false;
boolean bs_online = false;
boolean bs_media_ended = true;
boolean bs_debug = false;
};
