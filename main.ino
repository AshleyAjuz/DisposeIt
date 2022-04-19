//libraries
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//classes
#include "CompostIt.h"
#include "RecycleIt.h"
#include "TrashIt.h"
#include "GameFunctions.h"
#include "Commands.h"
#include "Timer.h"

//pin assignments
#define reset 9

//library instantiations
LiquidCrystal_I2C lcd(0x27, 16, 2);

//variables
boolean resetButtonState = LOW;
boolean lastResetButtonState = LOW;
boolean recycleItAction = LOW;
boolean trashItAction = LOW;
boolean compostItAction = LOW;
unsigned long lastResetDebounceTime = 0;
unsigned long resetDebounceDelay = 50;
boolean gameActive = LOW;
boolean resetAction = LOW;
boolean timeUp = LOW;

//object instantiation
GameFunctions game;
RecycleIt recycleit;
TrashIt trashit;
CompostIt compostit;
Commands commands;
Timer timer;

void setup() {
  //pin mode setup
  pinMode(button, INPUT);
  pinMode(fsr, INPUT);
  pinMode(rotaryOutputA, INPUT);
  pinMode(rotaryOutputB, INPUT);
  pinMode(correctLED, OUTPUT);
  pinMode(incorrectLED, OUTPUT);
  pinMode(reset, INPUT);

  //lcd setup
  lcd.begin(0x27, 16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press reset to");
  lcd.setCursor(0,1);
  lcd.print("start a game.");

  //rotary start state
  digitalWrite(rotaryOutputA, HIGH);
  digitalWrite(rotaryOutputB, HIGH);
  rotaryOutputALast = HIGH;
  rotaryOutputBLast = HIGH;

  //random seed for commands
  randomSeed(analogRead(2));
}

void gameplay(){
    //generate command
    commands.generateCommand(lcd);

    //renew timer for this command
    timer.resetTimer();
    timeUp = LOW;
  
    //polling for actions
    recycleItAction = recycleit.action();
    trashItAction = trashit.action();
    compostItAction = compostit.action();
    resetAction = checkReset();
    
    //waiting for action (user input, reset, or timer expiration)
    while(recycleItAction == LOW and trashItAction == LOW and compostItAction == LOW and resetAction == LOW and timeUp == LOW){
      recycleItAction = recycleit.action();
      trashItAction = trashit.action();
      compostItAction = compostit.action();
      resetAction = checkReset();
      timeUp = timer.timeLimitCheck();}
      
    //action taken on command, checking command
    boolean actionCorrect = false;
    
    //selected recycle
    if (recycleItAction and !trashItAction and !compostItAction) {
      actionCorrect = commands.checkCommand(1);
  
      if(actionCorrect){
        game.correctAction(lcd, 1);
        timer.speedUpGame(game.getScore());
      }else{
        gameActive = game.endGame(lcd, commands.getCorrectString(),0,0);
        timer.resetInterval();
      }
    } //selected trash
    else if (!recycleItAction and trashItAction and !compostItAction){
      actionCorrect = commands.checkCommand(0);
  
     if(actionCorrect){
        game.correctAction(lcd, 0);
        timer.speedUpGame(game.getScore());
      }else{
        gameActive = game.endGame(lcd, commands.getCorrectString(),0,0);
        timer.resetInterval();
      }
    } //selected compost
    else if (!recycleItAction and !trashItAction and compostItAction){
      actionCorrect = commands.checkCommand(2);
  
     if(actionCorrect){
        game.correctAction(lcd, 2);
        timer.speedUpGame(game.getScore());
      }else{
        gameActive = game.endGame(lcd, commands.getCorrectString(),0,0);
        timer.resetInterval();
      }
    }//did not answer fast enough
    else if(timeUp){
      gameActive = game.endGame(lcd, commands.getCorrectString(),1,0);
      timer.resetInterval();
    }//reset
    else if(resetAction){
      game.restartGame(lcd);
      timer.resetInterval();
    }else
      lcd.clear();  
}

boolean checkReset(){
  int reading = digitalRead(reset);

  if (reading != lastResetButtonState) {
    lastResetDebounceTime = millis();
  }

  if ((millis() - lastResetDebounceTime) > resetDebounceDelay) {
    if (reading != resetButtonState) {
      resetButtonState = reading;

      if (resetButtonState == HIGH) {
        return HIGH;
      }
    }
  }

  lastResetButtonState = reading;
  return LOW;
}


void loop() {
  resetAction = checkReset();
    
  if(!gameActive and resetAction){ //no game active, and reset hit .. start a game
     gameActive=HIGH;
     timer.resetInterval();
   }
  else if(gameActive and resetAction){ //reset hit in middle of game ... restart 
    game.restartGame(lcd);
    timer.resetInterval();
  }
  else if(gameActive){
    gameplay(); //regular game play}
  }
  
  else if(!gameActive){}
}
