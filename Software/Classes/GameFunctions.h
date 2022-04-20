//libraries
#include <LiquidCrystal_I2C.h>

//classes
#include "Audio.h"

//pin assignments
#define correctLED 3
#define incorrectLED 7

//class objects
Audio audio;

class GameFunctions {
  private:
    int score;
  public:
  void correctAction(LiquidCrystal_I2C lcd, int action);
  boolean endGame(LiquidCrystal_I2C lcd, char* correctAnswer, boolean timeUp, boolean maxScore);
  void restartGame(LiquidCrystal_I2C lcd);
  void incrementScore();
  void checkScore();
  int getScore();
 };

 void GameFunctions::incrementScore(){
  score++;

  if(score%10 == 0)
   audio.everyTenPoints();
  else
    audio.everyPoint();
}

int GameFunctions::getScore(){
  return score;
}

void GameFunctions::correctAction(LiquidCrystal_I2C lcd, int action){
  lcd.clear();
  
  if(action==0){
    lcd.clear();
    lcd.print("Correct,"); 
    lcd.setCursor(0,1);
    lcd.print("trashed!");
  }else if(action == 1){
    lcd.clear();
    lcd.print("Correct,"); 
    lcd.setCursor(0,1);
    lcd.print("recycled!");
  }else if(action == 2){
    lcd.clear();
    lcd.print("Correct,"); 
    lcd.setCursor(0,1);
    lcd.print("composted!");
  }
  incrementScore();
  digitalWrite(correctLED, HIGH);
  delay(1000);
  
  digitalWrite(correctLED, LOW);

  if(score == 99)
    endGame(lcd, "", 0, 1);
}
boolean GameFunctions::endGame(LiquidCrystal_I2C lcd, char* correctAnswer, boolean timeUp, boolean maxScore){
  //audio.gameLost();

  if(timeUp){
    lcd.clear();
    lcd.print("Time's up,");
    lcd.setCursor(0,1);
    lcd.print("Game Over!");
    digitalWrite(incorrectLED, HIGH);
    audio.trombone();
  }else if(maxScore){
    lcd.clear();
    lcd.print("Score = 99,");
    lcd.setCursor(0,1);
    lcd.print("You win!");
    digitalWrite(correctLED, HIGH);
    audio.gameWon();
  }
  else{
    lcd.clear();
    lcd.print("Incorrect,");
    lcd.setCursor(0,1);
    lcd.print("Game Over!");
    digitalWrite(incorrectLED, HIGH);
    audio.trombone();
  }
  delay(2500);

  if(maxScore){
    
  }else{
    lcd.clear();
    lcd.print("Correct Answer: ");
    lcd.setCursor(0,1);
    lcd.print(correctAnswer);
    delay(2500);
    
    lcd.clear();
    lcd.print("Score:");
    lcd.setCursor(0,1);
    lcd.print(score);
    delay(2500);
   }

  lcd.clear();
  lcd.print("Press reset to");
  lcd.setCursor(0,1);
  lcd.print("start a game.");

  score=0;
  digitalWrite(correctLED, LOW);
  digitalWrite(incorrectLED, LOW);
  return LOW;
}

void GameFunctions::restartGame(LiquidCrystal_I2C lcd){
  lcd.clear();
  lcd.print("Game Reset!");
  delay(1500);
  
  lcd.clear();
  lcd.print("Score:");
  lcd.setCursor(0,1);
  lcd.print(score);
  delay(1500);

  lcd.clear();
  lcd.print("New game");
  lcd.setCursor(0,1);
  lcd.print("starting...");
  delay(1500);

  score=0;
}
