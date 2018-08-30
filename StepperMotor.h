class StepperMotor {
  public:
    StepperMotor(int stepPin, int dirPin, int enablePin, unsigned long pulseDuration = 1000);
    void setSteps(int steps, bool dir);
    bool isMoving() {return mSteps > 0;};
    void step();
    void enable(bool value) {digitalWrite(mEnablePin, !value);};
  private:
    int mStepPin;
    int mDirPin;
    int mEnablePin;
    bool clkWise = true;
    int mSteps = 0;
    bool stepping = false;
    unsigned long mPulseDuration = 0;
    unsigned long mStepStartTime = 0;
};

StepperMotor::StepperMotor(int stepPin, int dirPin, int enablePin, unsigned long pulseDuration = 1000){
  mStepPin = stepPin; 
  mDirPin = dirPin;
  mEnablePin = enablePin;
  
  pinMode(mStepPin, OUTPUT);
  pinMode(mDirPin, OUTPUT);
  pinMode(mEnablePin, OUTPUT);

  digitalWrite(mEnablePin, LOW);
  digitalWrite(mDirPin, HIGH);

  mPulseDuration = pulseDuration;
}

void StepperMotor::setSteps(int steps, bool clkWise){
  //set motor direction
  digitalWrite(mDirPin, clkWise);
  mSteps = steps;
}

void StepperMotor::step(){
  if (mSteps > 0 ) {
    if(!stepping) {
      digitalWrite(mStepPin, HIGH);
      stepping = true;
      mStepStartTime = micros();
    }
    else if(mPulseDuration < micros() - mStepStartTime) {
      digitalWrite(mStepPin, LOW);
      stepping = false;
      mSteps--;
    }
  }
}


