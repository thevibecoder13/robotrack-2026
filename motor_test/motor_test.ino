#define IN1 26
#define IN2 27


#define IN3 32
#define IN4 33   // Changed from 4 to avoid pin conflict

void setup() {
  Serial.begin(9600);
  Serial.println("Maze Solver Robot Starting...");


  // Motor driver outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);



}

void loop() {

forward();
left();
right();

  delay(100); // small delay for stable readings
}

// Movement functions
void forward() {
  Serial.println("FORWARD");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
 
}

void left() {
  Serial.println("LEFT");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

}

void right() {
  Serial.println("RIGHT");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
 
}


void stopMotors() {
  Serial.println("STOP");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
 
}