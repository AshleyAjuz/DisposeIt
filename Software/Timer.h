class Timer {
  private:
    unsigned long interval = 6500;
    unsigned long firstTime, currentTime;
    
  public:
  Timer();
  boolean timeLimitCheck();
  void resetTimer();
  void speedUpGame(int score);
  void resetInterval();
};

Timer::Timer(){
  firstTime = millis();
  currentTime = millis();
}

boolean Timer::timeLimitCheck() {
  currentTime = millis();

  if(currentTime - firstTime >= interval)
    return true;
  else
    return false;
}

void Timer::resetTimer(){
  firstTime = millis();
  currentTime = millis();
}

void Timer::speedUpGame(int score) {
  interval = 6500-(score*50);
}

void Timer::resetInterval(){
  interval = 6500;
}
