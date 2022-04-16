class Timer {
  private:
    int startingInterval = 5000;
    int endInterval = 1000; 
    int waitingInterval;
    int decrementRatio;
    
  public:
  Timer();
  void waiting();
};

Timer::Timer(){
  waitingInterval = startingInterval;
  decrementRatio = (startingInterval-endInterval)/100;
}

void Timer::waiting() {
  delay(waitingInterval);
  waitingInterval -= decrementRatio;
}
