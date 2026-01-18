/*
 * ESP32 Ultrasonic Sensor Test (HC-SR04)
 * Prints distance to Serial Monitor
 */

// Define the GPIO pins for the sensor
const int trigPin = 5;
const int echoPin = 18;

// Define variables for sound speed calculations
// Speed of sound is approx 343m/s or 0.0343 cm/microsecond
#define SOUND_SPEED 0.0343

long duration;
float distanceCm;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200); 
  
  // Set pin modes
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  
  Serial.println("Ultrasonic Sensor Test Started...");
}

void loop() {
  // 1. Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // 2. Send a 10 microsecond HIGH pulse to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 3. Read the duration of the sound wave reflection (in microseconds)
  duration = pulseIn(echoPin, HIGH);
  
  // 4. Calculate the distance
  // Distance = (Time x Speed of Sound) / 2 (because the wave goes out and back)
  distanceCm = (duration * SOUND_SPEED) / 2;
  
  // 5. Print to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");
  
  // Delay before the next reading
  delay(500);
}