#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
/*
Notes:
Storing measures of beats:



Playing Sound:
if we can't play multiple sounds at the same time, we can store each combination of sound in the 
We can't store/play complex notes with the ATmega

max bpm = 100;
bpm is measure of quarter notes
minimum note is sixteenth note
minimum period is 60/400 = 0.15 secs



*/

//thse
int beats[1][3][16] = {{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //Cymbal
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //Snare
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}   //Kick
                        }; 


int SNARE_INPUT_PIN = -1;
int KICK_INPUT_PIN = -1;
int CYMBAL_INPUT_PIN = -1;
int SNARE_LED_PIN = -1;
int KICK_LED_PIN = -1;
int CYMBAL_LED_PIN = -1;

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

int MAX_BPM = 100;
int bpm = 20;
int score = 0;

void playSound(int ){
  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(SNARE_INPUT_PIN, INPUT);
  pinMode(KICK_INPUT_PIN, INPUT);
  pinMode(CYMBAL_INPUT_PIN, INPUT);
  pinMode(SNARE_LED_PIN, OUTPUT);
  pinMode(KICK_LED_PIN, OUTPUT);
  pinMode(CYMBAL_LED_PIN, OUTPUT);
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("HIT SNARE TO");
  lcd.setCursor(1, 0);
  lcd.print("BEGIN");
}

void loop() {
  // put your main code here, to run repeatedly:
  // get input to start
  while(digitalRead(SNARE_INPUT_PIN) == 0){
    //busywait
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SCORE: " + std::to_string(score));
  //game
  while(bpm < MAX_BPM){
    int beat = random(0, 1); 
    int millis_per_note = 60000/(bpm*4);
    //Playback
    for(int i = 0; i < 16; i++){
      int note = (beats[beat][0][i] << 0) | (beats[beat][1][i] << 1) | (beats[beat][2][i] << 2);
      if(note & 1){
        digitalWrite(CYMBAL_LED_PIN, HIGH);
      }
      if(note & 2){
        digitalWrite(SNARE_LED_PIN, HIGH);
      }
      if(note & 4){
        digitalWrite(KICK_LED_PIN, HIGH);
      }
      playSound(note);

      delay(millis_per_note);
    }
    //Playing section
    for(int i = 0; i < 16; i++){
      int time = millis();
      int note = (beats[beat][0][i] << 0) | (beats[beat][1][i] << 1) | (beats[beat][2][i] << 2);
      //Indicate which instrument to play
      if(note & 1){
        digitalWrite(CYMBAL_LED_PIN, HIGH);
      }
      if(note & 2){
        digitalWrite(SNARE_LED_PIN, HIGH);
      }
      if(note & 4){
        digitalWrite(KICK_LED_PIN, HIGH);
      }
      int inputs = 0;
      while(millis() < time_now +millis_per_note){  //Get inputs from user
        inputs |= (digitalRead(CYMBAL_INPUT_PIN) << 0) | (digitalRead(SNARE_INPUT_PIN) << 1) | (digitalRead(KICK_INPUT_PIN) << 2);
      }
      if(inputs == note){ //Gets the matching notes from input
        score += (note & inputs & 4 >> 2) + (note & inputs & 2 >> 1) + (note & inputs & 1 >> 0);
      }
      else{
        goto endGame;
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("SCORE: " + std::to_string(score));
    }
    bpm += 5;
  }
endGame:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAME OVER!");
  lcd.setCursor(1, 0);
  lcd.print("SCORE: " + std::to_string(score));
}