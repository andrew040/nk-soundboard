#include "Arduino.h"
#include "Audio.h"
#include "SPIFFS.h"
#include "FS.h"
 
#define I2S_DOUT           21  //MAX98357 pin DIN
#define I2S_BCLK           22  //MAX98357 pin BLCK
#define I2S_LRC            23  //MAX98357 pin LRCLK
#define I2S_SD             19  //MAX98357 pin ~SD

#define BUTTON             0
#define NUMBER_OF_FILES    16  //16 goeie stukskes

Audio audio;

volatile bool buttonPressed = false;
int number = 0;

void IRAM_ATTR handleButtonPress() {
  buttonPressed = true;
}

void onButtonPress() {
  switch(number){
    case 0:   audio.connecttoFS(SPIFFS,"/grill.mp3"); break;
    case 1:   audio.connecttoFS(SPIFFS,"/jajongekut.mp3"); break;
    case 2:   audio.connecttoFS(SPIFFS,"/naarhuis.mp3"); break;
    case 3:   audio.connecttoFS(SPIFFS,"/niereageren.mp3"); break;
    case 4:   audio.connecttoFS(SPIFFS,"/wannehomojoh.mp3"); break;
    case 5:   audio.connecttoFS(SPIFFS,"/kuteind.mp3"); break;
    case 6:   audio.connecttoFS(SPIFFS,"/lillukding.mp3"); break;
    case 7:   audio.connecttoFS(SPIFFS,"/kutwout.mp3"); break;
    case 8:   audio.connecttoFS(SPIFFS,"/werk.mp3"); break;
    case 9:   audio.connecttoFS(SPIFFS,"/goedgedaan.mp3"); break;
    case 10:  audio.connecttoFS(SPIFFS,"/bots.mp3"); break;
    case 11:  audio.connecttoFS(SPIFFS,"/700Wspeakers.mp3"); break;
    case 12:  audio.connecttoFS(SPIFFS,"/alleendebeste.mp3"); break;
    case 13:  audio.connecttoFS(SPIFFS,"/busgemist.mp3"); break;
    case 14:  audio.connecttoFS(SPIFFS,"/bendegijgekofzo.mp3"); break;
    case 15:  audio.connecttoFS(SPIFFS,"/woensel.mp3"); break;
    default:  audio.connecttoFS(SPIFFS,"/wannehomojoh.mp3"); break;
  }
  
  if(number<NUMBER_OF_FILES-1){
    number++;
  } else{
    number=0;
  }

}

void setup() {
    Serial.begin(115200);
    delay(10);

    pinMode(BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON), handleButtonPress, FALLING);
    
    if(!SPIFFS.begin(true)){
     Serial.println("SPIFFS not available");
     while(1);
    }

    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(5);
}
 
void loop()
{
    audio.loop();
    if (buttonPressed) {
        buttonPressed = false;
        onButtonPress();
        Serial.print("Playing file ");
        Serial.println((String)number);
    }
}