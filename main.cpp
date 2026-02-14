#include <Servo.h>
// Pin definitions
const int TRIG_PIN = 9;      // Ultrasonic sensor trigger pin
const int ECHO_PIN = 10;     // Ultrasonic sensor echo pin
const int SERVO_PIN = 6;     // Servo motor pin

// Configuration
const int DETECTION_DISTANCE = 30;  // Detection distance in cm
const int OPEN_ANGLE = 90;          // Lid open angle (adjust based on your bin)
const int CLOSED_ANGLE = 0;         // Lid closed angle
const int OPEN_DURATION = 3000;     // How long lid stays open (milliseconds)

Servo lidServo;
bool lidIsOpen = false;
unsigned long lidOpenTime = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize servo
  lidServo.attach(SERVO_PIN);
  lidServo.write(CLOSED_ANGLE);  // Start with lid closed
  
  Serial.println("Automatic Trash Bin Ready");
}

void loop() {
  // Get distance measurement
  int distance = getDistance();
  
  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Check if object is detected within range
  if (distance > 0 && distance <= DETECTION_DISTANCE && !lidIsOpen) {
    openLid();
  }
  
  // Check if it's time to close the lid
  if (lidIsOpen && (millis() - lidOpenTime >= OPEN_DURATION)) {
    closeLid();
  }
  
  delay(100);  // Small delay between measurements
}

// Function to measure distance using ultrasonic sensor
int getDistance() {
  // Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Send 10 microsecond pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the echo pin
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // 30ms timeout
  
  // Calculate distance in cm (speed of sound: 343 m/s)
  // Distance = (duration / 2) / 29.1
  if (duration == 0) {
    return -1;  // No echo received
  }
  
  int distance = duration * 0.034 / 2;
  return distance;
}

// Function to open the lid
void openLid() {
  Serial.println("Opening lid...");
  lidServo.write(OPEN_ANGLE);
  lidIsOpen = true;
  lidOpenTime = millis();
}

// Function to close the lid
void closeLid() {
  Serial.println("Closing lid...");
  lidServo.write(CLOSED_ANGLE);
  lidIsOpen = false;
}