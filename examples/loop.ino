#include <BrightSign.h>

// Instantiate a BrightSign object and Attach to a Serial1
BrightSign BS(Serial1);   

void setup(){

// Enable debug msg over Serial
BS.debug();               

Serial.begin(9600);
while(!Serial);

Serial.println("Waiting BrightSign Power-Up");
while(!BS.online())BS.update(); 

//Set Volume to 20%
BS.volume(20);            
}

void loop(){
// Update the BrightSign instance
BS.update();
if(BS.media_ended()) BS.play("AUDIO.M4A");
}
