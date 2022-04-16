//libraries
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//class header files
#include "CompostIt.h"
#include "RecycleIt.h"
#include "TrashIt.h"
#include "GameFunctions.h"
#include "Commands.h"
#include "Timer.h"
//#include "Audio.h"

//pin assignments
#define reset 9

//library instantiations
//SoftwareSerial mySoftwareSerial(audioRx, audioTx);
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

//object instantiation
GameFunctions game;
RecycleIt recycleit;
TrashIt trashit;
CompostIt compostit;
Commands commands;
//Timer timer;
//Audio audio;

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
  
    //polling for actions
    recycleItAction = recycleit.action();
    trashItAction = trashit.action();
    compostItAction = compostit.action();
    
    while(recycleItAction == LOW and trashItAction == LOW and compostItAction == LOW and resetAction == LOW){
      recycleItAction = recycleit.action();
      trashItAction = trashit.action();
      compostItAction = compostit.action();
      resetAction = checkReset(); }
      
    if(resetAction) //just checking reset since we were hanging in a while loop
      game.restartGame(lcd, gameActive);
      
    //action taken on command, checking command
    boolean actionCorrect = false;
    
    //selected recycle
    if (recycleItAction and !trashItAction and !compostItAction) {
      actionCorrect = commands.checkCommand(1);
  
      if(actionCorrect)
        game.correctAction(lcd, 1, gameActive);
      else{
        char* correctAnswer = commands.getCorrectString();
        game.endGame(lcd, correctAnswer, gameActive);
      }
    } //selected trash
    else if (!recycleItAction and trashItAction and !compostItAction){
      actionCorrect = commands.checkCommand(0);
  
     if(actionCorrect){
        game.correctAction(lcd, 0, gameActive);
      }else{
        char* correctAnswer = commands.getCorrectString();
        game.endGame(lcd, correctAnswer, gameActive);
      }
    } //selected compost
    else if (!recycleItAction and !trashItAction and compostItAction){
      actionCorrect = commands.checkCommand(2);
  
     if(actionCorrect){
        game.correctAction(lcd, 2, gameActive);
      }else{
        char* correctAnswer = commands.getCorrectString();
        game.endGame(lcd, correctAnswer, gameActive);
      }
    }//no action
    else
      lcd.clear();  
}

boolean checkReset(){
  int reading = digitalRead(reset);
  if (reading != lastResetButtonState) 
  lastResetDebounceTime = millis();

  if ((millis() - lastResetDebounceTime) > resetDebounceDelay) {
    if (reading != resetButtonState) {
      resetButtonState = reading;

      if (resetButtonState == HIGH){
        if(gameActive == LOW) {//no game, well start one
          gameActive = HIGH;}

        lcd.clear();
        lcd.print("Reset");
       
        return true;
      }
      else{
        lcd.clear();
        return false;}
    }
  }

  lastResetButtonState = reading;
}

void loop() {
  boolean initialGameActive = gameActive;
  resetAction = checkReset();
  
   if(!initialGameActive and resetAction) //no game active, and reset hit .. start a game
     game.startGame(gameActive);
   else if(resetAction) //reset hit in middle of game ... restart 
    game.restartGame(lcd, gameActive);
  else if(initialGameActive){
    gameplay(); }//regular game play}
}
