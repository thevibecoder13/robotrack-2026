#define ENA 4   // Left motor enable
#define IN1 5
#define IN2 18

#define ENB 2   // Right motor enable
#define IN3 19
#define IN4 21   // Changed from 4 to avoid pin conflict

#define FREQ 1000
#define RESOLUTION 8




void setup() {
  Serial.begin(9600);
  Serial.println("Maze Solver Robot Starting...");


  // Motor driver outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // // PWM setup
  // ledcSetup(ENA, FREQ, RESOLUTION);
  // ledcSetup(ENB, FREQ, RESOLUTION);

  // Attach PWM channels to enable pins
  ledcAttach(ENA, FREQ,RESOLUTION);
  ledcAttach(ENB, FREQ,RESOLUTION);
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
  ledcWrite(ENA, 102);
  ledcWrite(ENB, 102);
}

void left() {
  Serial.println("LEFT");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  ledcWrite(ENA, 102);
  ledcWrite(ENB, 51);
}

void right() {
  Serial.println("RIGHT");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(ENA, 51);
  ledcWrite(ENB, 102);
}


void stopMotors() {
  Serial.println("STOP");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(ENA, 0);
  ledcWrite(ENB, 0);
}
