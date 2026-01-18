// Replace the following TODO comment with the respective pin location , 
// for example if the left sensor is attached to pin d13 then it should be written as ,
// #define s1 13 

#define s1 TODO  //  defining the sensor according to their pin number 
#define S2 TODO  


void setup() {
  Serial.begin(9600);  // Start Serial Monitor
  pinMode(s1, INPUT);  // setting the sensor pins as input
  pinMode(S2, INPUT);

}

void loop() {
   // IR sensor gives LOW (0) for black and HIGH (1) for white
int a1 = digitalRead(s1); // reading the values recived by the sensor and storing it in a variable 
int a2 = digitalRead(S2);


  Serial.print(a1);  // printing the values in the serial monitor 
  Serial.print(a2);

  delay(200);  // Small delay for readability
}
