//this is the basic starter line following code, extremely simple.
// Speed ranges from 0 (Stop) to 255 (Full Speed)
const int MOTOR_SPEED = 128; 

// Motor A (Left)
const int in1 = 26;
const int in2 = 27;

// Motor B (Right)
const int in3 = 32;
const int in4 = 33;

// Sensors
const int sensorL = 34;
const int sensorR = 35;

//PWM SETTINGS
const int freq = 1000; 
const int resolution = 8; // 8-bit resolution (0-255)

void setup() {

  
  ledcAttach(in1, freq, resolution);
  ledcAttach(in3, freq, resolution);
  
  pinMode(in2, OUTPUT);
  pinMode(in4, OUTPUT);

  // Sensors
  pinMode(sensorL, INPUT);
  pinMode(sensorR, INPUT);
  
  Serial.begin(115200);
}

void loop() {
  int leftVal = digitalRead(sensorL);
  int rightVal = digitalRead(sensorR);

  // DEBUG: Uncomment to see what your sensors are seeing
  // Serial.print(leftVal); Serial.print(" - "); Serial.println(rightVal);

  // LOGIC: LOW (0) means Line Detected
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

//\MOVEMENT FUNCTIONS 

void moveForward() {
  
  ledcWrite(in1, MOTOR_SPEED); 
  ledcWrite(in3, MOTOR_SPEED);
  
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
}

void turnLeft() {
  // Stop Left
  ledcWrite(in1, 0); 
  digitalWrite(in2, LOW);
  
  // Run Right
  ledcWrite(in3, MOTOR_SPEED); 
  digitalWrite(in4, LOW);
}

void turnRight() {

  ledcWrite(in1, MOTOR_SPEED); 
  digitalWrite(in2, LOW);
  
 
  ledcWrite(in3, 0); 
  digitalWrite(in4, LOW);
}

void stopMotors() {
  ledcWrite(in1, 0);
  ledcWrite(in3, 0);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
}
