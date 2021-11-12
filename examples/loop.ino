#include <BrightSign.h>

BrightSign BS(Serial1);

void setup(){

BS.debug();               // Enable debug msg over Serial

Serial.begin(9600);
while(!Serial);

Serial.println("Waiting BrightSign PowerUp");
while(!BS.online())BS.update(); 

BS.volume(20);            //Sel Volume to 20%
}

void loop(){
BS.update();
if(BS.media_ended()) BS.play("AUDIO.M4A");
}
