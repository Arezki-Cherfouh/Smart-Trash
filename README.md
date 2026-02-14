# Automatic Trash Bin

A hands-free trash bin that automatically opens when you approach and closes after a set duration. Includes three Arduino/ESP32 implementations.

## Features

- **Hands-Free Operation**: Ultrasonic sensor detects approaching objects
- **Automatic Lid Control**: Servo opens/closes lid smoothly
- **Configurable Timing**: Adjust detection distance and open duration
- **State Management**: Prevents repeated triggers while lid is open
- **Debug Output**: Serial monitoring for distance readings
- **Three Versions**: Basic, enhanced, and ESP32 (WiFi-ready)

## Hardware Required

- Arduino (Uno/Nano/Mega) **OR** ESP32
- HC-SR04 Ultrasonic Sensor
- Servo motor (SG90 or MG90S)
- Trash bin with hinged lid
- Mounting hardware
- Jumper wires
- Power supply (5V)

## Wiring Diagrams

### Arduino Version (Basic & Enhanced)

```

HC-SR04:
VCC → 5V
GND → GND
Trig → Pin 9
Echo → Pin 10

Servo:
Signal → Pin 6 (or 3 for basic)
VCC → 5V
GND → GND

```

### ESP32 Version

```

HC-SR04:
VCC → 5V
GND → GND
Trig → GPIO5
Echo → GPIO18

Servo:
Signal → GPIO13
VCC → 5V
GND → GND

```

## Code Versions

| Version  | Features                     | Best For        |
| -------- | ---------------------------- | --------------- |
| Basic    | Simple open/close logic      | Beginners       |
| Enhanced | State tracking, configurable | Standard use    |
| ESP32    | WiFi-ready, advanced PWM     | IoT integration |

## How It Works

1. **Distance Measurement**: Ultrasonic sensor checks for objects every 100ms
2. **Detection Logic**: If object < 30cm AND lid is closed → Open lid
3. **Timed Operation**: Lid stays open for 3 seconds
4. **Auto-Close**: After duration, lid closes automatically
5. **Anti-Repeat**: State tracking prevents multiple triggers while open

## Configuration

### Adjust Detection Distance

```cpp
const int DETECTION_DISTANCE = 30;  // Change to desired cm
```

### Modify Open Duration

```cpp
const int OPEN_DURATION = 3000;  // Milliseconds (3000 = 3 seconds)
```

### Change Servo Angles

```cpp
const int OPEN_ANGLE = 90;   // Lid open position
const int CLOSED_ANGLE = 0;  // Lid closed position
```

## Installation

1. Mount ultrasonic sensor at hand height
2. Attach servo to lid mechanism
3. Upload appropriate code version
4. Power the system
5. Test by approaching with hand
6. Adjust angles/durations as needed

## Serial Output Example

```
Automatic Trash Bin Ready
Distance: 45 cm
Distance: 42 cm
Distance: 28 cm  → Opening lid...
Distance: 25 cm
Distance: 30 cm
Distance: 35 cm  → Closing lid...
```

## ESP32 Extras

The ESP32 version includes:

- WiFi and Bluetooth available for IoT integration
- Proper timer allocation for ESP32Servo library
- 115200 baud rate for faster debugging
- Expandable for cloud connectivity

## Troubleshooting

| Problem             | Solution                                          |
| ------------------- | ------------------------------------------------- |
| Lid opens randomly  | Increase `DETECTION_DISTANCE`; check sensor angle |
| Lid won't stay open | Verify `OPEN_DURATION`; check state logic         |
| Servo not moving    | Check power; verify pin connections               |
| Multiple triggers   | Enhanced version prevents this                    |
| No detection        | Check sensor wiring; reduce timeout               |

## Customization Ideas

### Add LED Indicators

```cpp
const int LED_PIN = 13;

if (lidIsOpen) {
  digitalWrite(LED_PIN, HIGH);  // LED on when open
} else {
  digitalWrite(LED_PIN, LOW);
}
```

### Add Buzzer Feedback

```cpp
if (distance <= DETECTION_DISTANCE && !lidIsOpen) {
  tone(BUZZER_PIN, 1000, 100);  // Beep on detection
  openLid();
}
```

### IoT Integration (ESP32)

```cpp
// Connect to WiFi and send status
WiFi.begin(ssid, password);
// Send "Bin opened" notifications
```

## Applications

- Kitchen trash bins
- Medical waste containers
- Touchless recycling stations
- Hygiene-focused environments
- Smart home automation

## License

MIT - Free for learning and modification

```

```
