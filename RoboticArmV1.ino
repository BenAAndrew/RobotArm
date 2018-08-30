#include "StepperMotor.h"

#define BASE_STEP_PIN           54
#define BASE_DIR_PIN            55
#define BASE_ENABLE_PIN         38

#define ELBOW_STEP_PIN          60
#define ELBOW_DIR_PIN           61
#define ELBOW_ENABLE_PIN        56

#define SHOULDER_STEP_PIN       46
#define SHOULDER_DIR_PIN        48
#define SHOULDER_ENABLE_PIN     62

#define WRIST_ROLL_STEP_PIN     26
#define WRIST_ROLL_DIR_PIN      28
#define WRIST_ROLL_ENABLE_PIN   24

#define WRIST_PITCH_STEP_PIN    36
#define WRIST_PITCH_DIR_PIN     34
#define WRIST_PITCH_ENABLE_PIN  30

#define NUM_OF_MOTORS           5
#define MAX_STEP_PULSE          1000
#define MIN_STEP_PULSE          100

#define INST_ARRAY_LEN          20
//base 0
//shoulder 1
//elbow 2
//wristRoll 3
//wristPitch 4
StepperMotor* motors[NUM_OF_MOTORS];
int instIndex = 0;
int motorIndex = 0;
char instruction[INST_ARRAY_LEN];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  

  motors[0] = new StepperMotor(BASE_STEP_PIN, BASE_DIR_PIN, BASE_ENABLE_PIN, MAX_STEP_PULSE);
  motors[1] = new StepperMotor(SHOULDER_STEP_PIN, SHOULDER_DIR_PIN, SHOULDER_ENABLE_PIN, MAX_STEP_PULSE);
  motors[2] = new StepperMotor(ELBOW_STEP_PIN, ELBOW_DIR_PIN, ELBOW_ENABLE_PIN, MAX_STEP_PULSE);
  motors[3] = new StepperMotor(WRIST_ROLL_STEP_PIN, WRIST_ROLL_DIR_PIN, WRIST_ROLL_ENABLE_PIN, MIN_STEP_PULSE);
  motors[4] = new StepperMotor(WRIST_PITCH_STEP_PIN, WRIST_PITCH_DIR_PIN, WRIST_PITCH_ENABLE_PIN, MAX_STEP_PULSE);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Instruction parser
  if (Serial.available() > 0)
  {
    String input = Serial.readString();
    if(input[0] == 'm'){
      int motor = input[2]-48;
      int steps = input.substring(4).toInt();
      motors[motor]->setSteps(abs(steps), steps > 0);
    } else if (input[0] == 'i'){
      Serial.println("I'm a 6 axis robot arm,Commands:\n>Motor move; m/[motor_number {0..4}]/[steps]\n>Get info; i\n");
    }
      
      /*if(instIndex > 0) {
        for(int i = instIndex; i < INST_ARRAY_LEN; i++)
          instruction[i] = NULL;
        int steps = atol(instruction);
        motors[motorIndex]->setSteps(abs(steps), steps > 0);
        Serial.println(steps);
      }
      instIndex = 0;
      motorIndex++;
      if (motorIndex >= NUM_OF_MOTORS)
        motorIndex = 0;
      if(nextChar == '\n')
        motorIndex = 0;*/
    //add to instruction string
    /*else {
      if(instIndex >= INST_ARRAY_LEN)  
        Serial.println("ERROR - loop() instruction parser: Instruction index out of bounds.");
      else{
        instruction[instIndex] = nextChar;
        instIndex++;
      }
    }
    /*
    String serialString = Serial.readStringUntil('\r\n');
    
    // Convert from String Object to String.
    char buf[serialString.length()];
    serialString.toCharArray(buf, serialString.length());
    char *p = buf;
    char *str;
    int index = 0;
    while ((str = strtok_r(p, " ", &p)) != NULL) {// delimiter is space
      Serial.println(str);
      int steps = atoi(str);
      motors[index]->setSteps(abs(steps), steps > 0);
      index++;
    }*/
  }

  for (int i = 0; i < NUM_OF_MOTORS; i++){
    motors[i]->step();
  }
}
// -1000 -1000 0 -1000 0
// 0 0 0 -1000 0


