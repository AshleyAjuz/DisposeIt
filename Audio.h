#include "pitches.h"

#define speaker 1

class Audio {
  private:
  public:
    void everyTenPoints();
    void gameLost();
    void gameWon();
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
  
}
