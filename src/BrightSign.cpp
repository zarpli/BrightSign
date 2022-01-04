#include "BrightSign.h"

BrightSign::BrightSign(HardwareSerial &serial) {
    bs_serial = &serial;
    bs_serial->begin(BAUD_RATE);
}

void BrightSign::update(){

    if (bs_serial->available()>2)
    {
          if (bs_serial->read() != STX) return;
          byte cmd = bs_serial->read(); 
          if (bs_serial->read() == ETX)
          {
            if(cmd == ERROR) {
                if(bs_debug) Serial.println("BS : error"); 
                bs_error = true;
            }
            if(cmd == OK) {
                if(bs_debug) Serial.println("BS : ok");
                bs_error = false;
            }
            if(cmd == ONLINE) {
                if(bs_debug) Serial.println("BS : online"); 
                bs_online = true;
            }
            if(cmd == MEDIA_ENDED) {
                if(bs_debug) Serial.println("BS : media_ended");
                bs_media_ended = true;
            }
          }
    }   
}

void BrightSign::play(String file){
bs_serial->print("PLAY " + file + "\r");
bs_media_ended = false;
}

void BrightSign::volume(int percentage){
bs_serial->print("VOLUME " + (String)percentage + "\r");
}

void BrightSign::loop(String option){
bs_serial->print("LOOP " + option + "\r");
}

void BrightSign::stop(){
bs_serial->print("STOP\r");
}

void BrightSign::pause(){
bs_serial->print("PAUSE\r");
}

void BrightSign::resume(){
bs_serial->print("RESUME\r");
}

void BrightSign::reboot(){
bs_serial->print("REBOOT\r");
}
