//The line follower utilizes 2 ir sensors connected to D34 (left) and D35 (right) in order to keep track of the line.
//It outputs signals for the motor driver from the pins D26, D27 (for left motor) and D32, D33 (for right motor)
//this version assumes that after the motors have stayed off for a certain amount of time, they've lost momentum and need to be kick started on.

// --- CONSTANTS ---
const int MOMENTUM_TIMEOUT = 400; // Time (ms) needed to consider motor "stopped"
const int MOTOR_SPEED = 30; //30 is the sweet spot. when braking isnt working
const int KICK_SPEED = 200;  //the power given to motors to kickstart them on
const int KICK_TIME = 30;    //the time for which kickstart power will be active

// Motor Pins
const int in1 = 26; // Left Motor Pin 1
const int in2 = 27; // Left Motor Pin 2
const int in3 = 32; // Right Motor Pin 1
const int in4 = 33; // Right Motor Pin 2

// IR Sensors
const int sensorL = 34;
const int sensorR = 35;

// PWM Settings
const int freq = 1000; 
const int resolution = 8; 

// --- MOTOR STATE TRACKING --- 
// The motors need to be tracked closely to check if they are closed 
// We track each motor separately 
bool isMovingL = false;
bool isMovingR = false;
unsigned long lastStopTimeL = 0;
unsigned long lastStopTimeR = 0;

void setup() {
  ledcAttach(in1, freq, resolution);
  ledcAttach(in3, freq, resolution);
  
  pinMode(in2, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(sensorL, INPUT);
  pinMode(sensorR, INPUT);
  

  // Initialize stop times so the robot kicks on the very first move
  lastStopTimeL = millis() - 1000;
  lastStopTimeR = millis() - 1000;
}

void loop() {
  int leftVal = digitalRead(sensorL);
  int rightVal = digitalRead(sensorR);

  if (leftVal == LOW && rightVal == LOW) {
    moveForward();
  } else if (leftVal == LOW && rightVal == HIGH) {
    turnLeft();
  } else if (leftVal == HIGH && rightVal == LOW) {
    turnRight();
  } else {
    stopMotors();
  }
  delay(10);
}

// --- MOVEMENT FUNCTIONS ---

void moveForward() {
  bool kickL = false;
  bool kickR = false;

  // CHECK LEFT: Only kick if it wasn't moving AND has been stopped long enough
  if (!isMovingL && (millis() - lastStopTimeL > MOMENTUM_TIMEOUT)) {
    kickL = true;
  }
  
  // CHECK RIGHT: Only kick if it wasn't moving AND has been stopped long enough
  if (!isMovingR && (millis() - lastStopTimeR > MOMENTUM_TIMEOUT)) {
    kickR = true;
  }

  // APPLY KICK if needed
  if (kickL || kickR) {
    if(kickL) ledcWrite(in1, KICK_SPEED);
    else      ledcWrite(in1, MOTOR_SPEED); // If no kick, keep normal
    
    if(kickR) ledcWrite(in3, KICK_SPEED);
    else      ledcWrite(in3, MOTOR_SPEED);

    delay(KICK_TIME); // Quick burst
  }

  // NORMAL RUN
  ledcWrite(in1, MOTOR_SPEED); 
  ledcWrite(in3, MOTOR_SPEED);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);

  // UPDATE STATE: Both are now moving
  isMovingL = true;
  isMovingR = true;
}

void turnLeft() {
  // Turn Left = Left Stop, Right Run
  
  // 1. HANDLE LEFT MOTOR (Stop)
  if (isMovingL) {
    lastStopTimeL = millis(); // Mark the exact moment it stopped
    isMovingL = false;
  }
  ledcWrite(in1, 0); 
  digitalWrite(in2, LOW);

  // 2. HANDLE RIGHT MOTOR (Run)
  // Only kick if it wasn't moving AND has been stopped long enough
  if (!isMovingR && (millis() - lastStopTimeR > MOMENTUM_TIMEOUT)) {
    ledcWrite(in3, KICK_SPEED);
    delay(KICK_TIME);
  }
  
  ledcWrite(in3, MOTOR_SPEED); 
  digitalWrite(in4, LOW);
  isMovingR = true;
}

void turnRight() {
  // Turn Right = Left Run, Right Stop

  // 1. HANDLE LEFT MOTOR (Run)
  if (!isMovingL && (millis() - lastStopTimeL > MOMENTUM_TIMEOUT)) {
    ledcWrite(in1, KICK_SPEED);
    delay(KICK_TIME);
  }
  ledcWrite(in1, MOTOR_SPEED); 
  digitalWrite(in2, LOW);
  isMovingL = true;

  // 2. HANDLE RIGHT MOTOR (Stop)
  if (isMovingR) {
    lastStopTimeR = millis();
    isMovingR = false;
  }
  ledcWrite(in3, 0); 
  digitalWrite(in4, LOW);
}

void stopMotors() {
  // Update timestamps only if they were previously moving
  if (isMovingL) {
    lastStopTimeL = millis();
    isMovingL = false;
  }
  if (isMovingR) {
    lastStopTimeR = millis();
    isMovingR = false;
  }

  ledcWrite(in1, 0);
  ledcWrite(in3, 0);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
}
