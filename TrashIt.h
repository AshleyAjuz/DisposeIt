#define button 2

boolean lastButtonState = LOW;
boolean buttonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

class TrashIt {
  private:
  public:
  boolean action();
};

boolean TrashIt::action(){
  int reading = digitalRead(button);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        return HIGH;
      }
    }
  }

  lastButtonState = reading;
  return LOW;
}
