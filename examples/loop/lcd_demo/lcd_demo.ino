#include <LiquidCrystal.h>

#define BS_SERIAL     Serial1
#define STX           0x02
#define ETX           0x03

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

boolean online = false;
boolean media_ended = true;

unsigned char current_track = 1;

void setup() {

    Serial.begin(115200);
    BS_SERIAL.begin(115200);

    while (!Serial);
    Serial.println("BSuControl Serial Port Control 1.0");    

    lcd.begin(16, 2);
    lcd.print("BSuControl");
}

void status_bs() {
    if (BS_SERIAL.available()>2)
    {
          if (BS_SERIAL.read() != STX) return;
          byte cmd = BS_SERIAL.read(); 
          if (BS_SERIAL.read() == ETX)
          {
          lcd.setCursor(0,0);
          Serial.print("BS : ");
          lcd.print("BS : ");
          if(cmd == 0x00) {Serial.println("error"); lcd.print("error      ");}
          if(cmd == 0x01) {Serial.println("ok"); lcd.print("ok         ");}
          if(cmd == 0x02) {Serial.println("online"); lcd.print("online     "); online = true;}
          if(cmd == 0x08) {Serial.println("media_ended"); lcd.print("media_ended"); media_ended = true;}
          }
    }   
}


void loop(){

  while(!online) status_bs();
  
  delay(1000);
  
  while(1)
  {
        status_bs();

        if(media_ended == true)
        {
        lcd.setCursor(0,1);
        lcd.print("PLAY " + (String)current_track + ".MP4");
        Serial.println("PLAY " + (String)current_track + ".MP4");
        BS_SERIAL.print("PLAY " + (String)current_track + ".MP4\r");
  
        current_track ++;
        if(current_track == 9)current_track = 1;
        media_ended = false;
        }
 }
 


}
