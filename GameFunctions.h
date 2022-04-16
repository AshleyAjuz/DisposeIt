#include <LiquidCrystal_I2C.h>

#include "Audio.h"

#define correctLED 3
#define incorrectLED 7

Audio audio;

class GameFunctions {
  private:
    int score;
  public:
  void correctAction(LiquidCrystal_I2C lcd, int action, boolean gameActive);
  void startGame(boolean gameActive);
  void endGame(LiquidCrystal_I2C lcd, char* correctAnswer, boolean gameActive);
  void restartGame(LiquidCrystal_I2C lcd, boolean gameActive);
  void incrementScore();
  void checkScore();
  int getScore();
 };

 void GameFunctions::incrementScore(){
  score++;

  if(score%10 == 0)
    audio.everyTenPoints();
}

int GameFunctions::getScore(){
  return score;
}

void GameFunctions::correctAction(LiquidCrystal_I2C lcd, int action, boolean gameActive){
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

  lcd.clear();
  lcd.print("Score:");
  lcd.setCursor(0,1);
  lcd.print(score);
  delay(1000);
  
  digitalWrite(correctLED, LOW);

  if(score == 99)
    endGame(lcd, "Max score", gameActive);
}

void GameFunctions::endGame(LiquidCrystal_I2C lcd, char* correctAnswer, boolean gameActive){
  gameActive = LOW;

  audio.gameLost();

  lcd.clear();
  lcd.print("Incorrect,");
  lcd.setCursor(0,1);
  lcd.print("Game Over!");
  digitalWrite(incorrectLED, HIGH);
  delay(1000);

  lcd.clear();
  lcd.print("Correct Answer: ");
  lcd.setCursor(0,1);
  lcd.print(correctAnswer);
  delay(1000);
  
  lcd.clear();
  lcd.print("Score:");
  lcd.setCursor(0,1);
  lcd.print(score);
  delay(1000);

  lcd.clear();
  lcd.print("Press reset to");
  lcd.setCursor(0,1);
  lcd.print("start a game.");
  delay(1000);
  
  digitalWrite(incorrectLED, LOW);
}

void GameFunctions::startGame(boolean gameActive){
  score=0;
  gameActive = HIGH;
}

void GameFunctions::restartGame(LiquidCrystal_I2C lcd, boolean gameActive){
  //endGame();
  gameActive = LOW;

  lcd.clear();
  lcd.print("Game Reset!");
  delay(1000);
  
  lcd.clear();
  lcd.print("Score:");
  lcd.setCursor(0,1);
  lcd.print(score);
  delay(1000);

  lcd.clear();
  lcd.print("New game");
  lcd.setCursor(0,1);
  lcd.print("starting...");
  delay(1000);
  
  startGame(gameActive);
}
