#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define NOTE_B0 120
#define NOTE_F5 96
#define NOTE_D7 246
#define NOTE_DS8 179

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
int beats[4][3][16] = {{{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},   //SNARE
                        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},   //TOM
                        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0}},   //Kick
                       {{0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},   //SNARE
                        {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},   //TOM
                        {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0}},   //Kick
                       {{1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},   //SNARE
                        {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},   //TOM
                        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0}},   //Kick
                       {{0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},   //SNARE
                        {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},   //TOM
                        {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0}}   //Kick
                        }; 
int TOM_INPUT_PIN = PC0;   //Analog
int KICK_INPUT_PIN = PD6;
int SNARE_INPUT_PIN = PD4;
int TOM_LED_PIN = PD3;
int KICK_LED_PIN = PD2;
int SNARE_LED_PIN = PD7;
int SPEAKER_PIN = 9;
int snare_before;
int tom_sens = 40;
bool check_snare;
int inputs;

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

int MAX_BPM = 100;
int bpm = 20;
int score = 0;

void playSound(int note){
  noTone(SPEAKER_PIN);
  if(note == 1){
    //tone(SPEAKER_PIN);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(TOM_INPUT_PIN, INPUT);
  pinMode(KICK_INPUT_PIN, INPUT);
  pinMode(SNARE_INPUT_PIN, INPUT);
  pinMode(TOM_LED_PIN, OUTPUT);
  pinMode(KICK_LED_PIN, OUTPUT);
  pinMode(SNARE_LED_PIN, OUTPUT);
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("HIT TOM TO");
  lcd.setCursor(0, 1);
  lcd.print("BEGIN");
}

void loop() {
  // put your main code here, to run repeatedly:
  // get input to start
  while(analogRead(TOM_INPUT_PIN) < tom_sens){
    //busywait
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SCORE: " + String(score));
  //game
  while(bpm < MAX_BPM){
    int beat = random(0, 4); 
    int millis_per_note = 60000/(bpm*4);
    //Playback
    
    for(int i = 0; i < 16; i++){
      digitalWrite(TOM_LED_PIN, LOW);
      digitalWrite(SNARE_LED_PIN, LOW);
      digitalWrite(KICK_LED_PIN, LOW);
      int note = (beats[beat][0][i] << 0) | (beats[beat][1][i] << 1) | (beats[beat][2][i] << 2);
      if(note & 1){
        digitalWrite(SNARE_LED_PIN, HIGH);
        tone(SPEAKER_PIN, NOTE_B0);
      }
      if(note & 2){
        digitalWrite(TOM_LED_PIN, HIGH);
        tone(SPEAKER_PIN, NOTE_F5);
      }
      if(note & 4){
        digitalWrite(KICK_LED_PIN, HIGH);
        tone(SPEAKER_PIN, NOTE_D7);
      }
      //playSound(note);

      delay(millis_per_note/2);
      digitalWrite(TOM_LED_PIN, LOW);
      digitalWrite(SNARE_LED_PIN, LOW);
      digitalWrite(KICK_LED_PIN, LOW);
      
      noTone(SPEAKER_PIN);
      delay(millis_per_note/2);
    }
    
    // Pause section
    tone(SPEAKER_PIN, NOTE_DS8);
    digitalWrite(TOM_LED_PIN, HIGH);
    digitalWrite(SNARE_LED_PIN, HIGH);
    digitalWrite(KICK_LED_PIN, HIGH);
    delay(millis_per_note);
    noTone(SPEAKER_PIN);

    //Playing section
    for(int i = 0; i < 16; i++){
      digitalWrite(TOM_LED_PIN, LOW);
      digitalWrite(SNARE_LED_PIN, LOW);
      digitalWrite(KICK_LED_PIN, LOW);
      snare_before = digitalRead(SNARE_INPUT_PIN);
      int time_now = millis();
      int note = (beats[beat][0][i] << 0) | (beats[beat][1][i] << 1) | (beats[beat][2][i] << 2);
      //Indicate which instrument to play
      if(note & 1){
        digitalWrite(SNARE_LED_PIN, HIGH);
        tone(SPEAKER_PIN, NOTE_B0);
      }
      if(note & 2){
        digitalWrite(TOM_LED_PIN, HIGH);
        tone(SPEAKER_PIN, NOTE_F5);
      }
      if(note & 4){
        digitalWrite(KICK_LED_PIN, HIGH);
        tone(SPEAKER_PIN, NOTE_D7);
      }
      inputs = 0;
      //delay(500);
      
      //digitalWrite(TOM_LED_PIN, LOW);
      //digitalWrite(SNARE_LED_PIN, LOW);
      //digitalWrite(KICK_LED_PIN, LOW);
      
      for(int j = 0; j < millis_per_note; j++){  //Get inputs from user
        check_snare=(digitalRead(SNARE_INPUT_PIN)!=snare_before);
        inputs |=  check_snare|((analogRead(TOM_INPUT_PIN) > tom_sens) << 1) | (digitalRead(KICK_INPUT_PIN) << 2);
        //snare_input = digitalRead(SNARE_INPUT_PIN);
        // if(digitalRead(SNARE_INPUT_PIN)){
        //   tone(SPEAKER_PIN, NOTE_B0);
        // }
        // if(analogRead(TOM_INPUT_PIN) > tom_sens){
        //   tone(SPEAKER_PIN, NOTE_F5);
        // }
        // if(digitalRead(KICK_INPUT_PIN)){
        //   tone(SPEAKER_PIN, NOTE_D7);
        // }
        delay(1);
      }
      if(inputs == note){ //Gets the matching notes from input
        score += ((inputs >> 2) & 0x1) + ((inputs >> 1) & 0x1) + ((inputs >> 0) & 0x1);
      }
      else{
        goto endGame;
      }
      noTone(SPEAKER_PIN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("SCORE: " + String(score));
      lcd.setCursor(0, 1);
      lcd.print(String(inputs));
    }
        // Pause section
    tone(SPEAKER_PIN, NOTE_DS8);
    digitalWrite(TOM_LED_PIN, HIGH);
    digitalWrite(SNARE_LED_PIN, HIGH);
    digitalWrite(KICK_LED_PIN, HIGH);
    delay(millis_per_note);
    noTone(SPEAKER_PIN);
    bpm = bpm + 5;
  }
endGame:
  noTone(SPEAKER_PIN);
  digitalWrite(TOM_LED_PIN, LOW);
  digitalWrite(SNARE_LED_PIN, LOW);
  digitalWrite(KICK_LED_PIN, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAME OVER!");
  lcd.setCursor(0, 1);
  lcd.print("SCORE: " + String(score));
  score = 0;
}
