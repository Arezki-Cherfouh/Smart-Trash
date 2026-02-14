#include <ESP32Servo.h>

// Pin definitions (ESP32 compatible pins)
const int TRIG_PIN = 5;      // Ultrasonic sensor trigger pin (GPIO5)
const int ECHO_PIN = 18;     // Ultrasonic sensor echo pin (GPIO18)
const int SERVO_PIN = 13;    // Servo motor pin (GPIO13)

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
  Serial.begin(115200);  // ESP32 typically uses 115200 baud rate
  
  // Initialize ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize servo - ESP32Servo library handles PWM configuration
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  lidServo.setPeriodHertz(50);      // Standard 50hz servo
  lidServo.attach(SERVO_PIN, 500, 2400);  // Attach with min/max pulse width
  lidServo.write(CLOSED_ANGLE);      // Start with lid closed
  
  delay(500);  // Give servo time to move to initial position
  
  Serial.println("ESP32 Automatic Trash Bin Ready");
  Serial.println("WiFi and Bluetooth modules available for future expansion");
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