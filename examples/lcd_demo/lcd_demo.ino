/*
Zarpli - Tecnología Interactiva
12112021 Alejandro Zárate
https://github.com/zarpli/BrightSign/

DESCRIPTION
====================
  
Example of the BrightSign library that play cyclically a series of eight 
videos 1.mp4, 2.mp4 ... 8.mp4, waiting for each one to finish.

LCD 16x2 is Optional and requires the library:
https://github.com/arduino-libraries/LiquidCrystal
  
The BSuControl Script must be installed in the BrightSign unit 
memory unit and must be connected to the Serial1 port.  
https://github.com/zarpli/BSuControl/

Media Files for Testing
https://github.com/zarpli/Media/
*/

#include <BrightSign.h>
#include <LiquidCrystal.h>

// Instantiate a BrightSign object and Attach to Serial1
BrightSign BS(Serial1);

// Instantiate a LiquidCrystal object.
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

unsigned char current_track = 1;

void setup(){

BS.debug();         // Enable debug msg over Serial

lcd.begin(16, 2);
lcd.print("BSuControl");
lcd.setCursor(0,1);
lcd.print("Waiting Power-UP");

Serial.begin(9600);
while(!Serial);

Serial.println("Waiting BrightSign Power-Up");
while(!BS.online())BS.update(); 

lcd.clear();
lcd.print("BSuControl");

BS.volume(20);      //Set Volume to 20%
}

void loop(){
BS.update();        // Update the BrightSign instance

if(BS.media_ended()){
  BS.play("/VIDEO/SEQUENCE/" + (String)current_track + ".MP4");
  lcd.setCursor(0,1);
  lcd.print("PLAY " + (String)current_track + ".MP4");
  Serial.println("PLAY " + (String)current_track + ".MP4");
 
  current_track ++;
  if(current_track == 9)current_track = 1;
  }
}
