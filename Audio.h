//libraries
#include "pitches.h"

//pin assignments
#define speaker 1

class Audio {
  private:
  public:
    void everyTenPoints();
    void gameLost();
    void gameWon();
    void gameStart();
    void trombone();
 };

void Audio::everyTenPoints(){
  tone(speaker,NOTE_B5,100);
  delay(40);
  tone(speaker,NOTE_E6,850);
  delay(320);
  noTone(speaker);
}
void Audio::gameLost(){
  tone(speaker,NOTE_G4);
  delay(250);
  tone(speaker,NOTE_C4);
  delay(500);
  noTone(speaker);
}
void Audio::gameWon(){
  tone(speaker, NOTE_C5);
  delay(250);
  tone(speaker, NOTE_D5);
  delay(250);
  tone(speaker, NOTE_E5);
  delay(250);
  noTone(speaker);
}

void Audio::trombone(){
  //d, c#, c, b
  tone(speaker, NOTE_D5);
  delay(300);
  tone(speaker, NOTE_CS4);
  delay(200);
  tone(speaker, NOTE_C4);
  delay(200);
  tone(speaker, NOTE_B4);
  delay(200);
  noTone(speaker);
}
