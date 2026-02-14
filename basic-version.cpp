#include <Servo.h>

// Pins
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 3;

// Variables
Servo myServo;
long duration;
int distance;
int threshold = 20; // Distance in cm to trigger the lid

void setup() {
  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myServo.write(0); // Start with bin closed
  Serial.begin(9600);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  // Logic to open/close
  if (distance > 0 && distance <= threshold) {
    Serial.println("Object Detected! Opening...");
    myServo.write(90);  // Open lid
    delay(3000);        // Wait 3 seconds
  } else {
    myServo.write(0);   // Close lid
  }
  
  delay(100); 
}