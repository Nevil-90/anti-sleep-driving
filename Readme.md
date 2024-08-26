
# IoT Anti Sleep Driving System

This project monitors a driver's drowsiness using an eye-tracking sensor and takes appropriate actions to ensure safety. The system connects to a Wi-Fi network to send an alert email if drowsiness is detected.

## 🚀 Features

- **Eye-Tracking Sensor**: Monitors the driver's eye state and detects if the eyes are closed for too long.
- **Relay Module Control**: Activates safety mechanisms such as stopping the car if the driver is drowsy.
- **LED & Buzzer Alerts**: Provides visual and audio alerts if the driver is drowsy.
- **Wi-Fi Connectivity**: Connects to a Wi-Fi network to send an email alert when the driver is detected as drowsy.
- **Email Alert**: Sends an email alert to a specified recipient using an SMTP server.

## 🛠 Components Used

- **Arduino Board**
- **ESP8266/ESP32 Module**
- **Eye-Tracking Sensor**
- **Relay Module**
- **LED**
- **Buzzer**
- **Wi-Fi Network**

## 📋 Installation and Setup

1. **Clone the Repository**
   ```bash
   git clone https://github.com/Nevil-90/anti-sleep-driving.git
   ```

2. **Configure Wi-Fi and Email Settings**
   Update the following fields in `node-wifi.ino` with your Wi-Fi and email credentials:
   ```cpp
   #define WIFI_SSID "<your wifi name>"
   #define WIFI_PASSWORD "<password>"

   #define AUTHOR_EMAIL "<sender-mail>"
   #define AUTHOR_PASSWORD "<app password>"
   #define RECIPIENT_EMAIL "<receiver-mail>"
   ```

3. **Upload the Code**
   ```bash
   - Upload `node-wifi.ino` to your ESP8266/ESP32 module.
   - Upload `arduino.ino` to your Arduino board.
   ```

4. **Connect the Components**
   Connect the eye-tracking sensor, relay module, LED, and buzzer to the Arduino board as per the pin configuration in the code.

## 🧑‍💻 Usage

- **Eye-Tracking Monitoring**: The system continuously monitors the driver's eye state. If the eyes are closed for more than 3 seconds, the LED and buzzer are activated. If the eyes are closed for more than 5 seconds, the relay module stops the car, and an email alert is sent.
- **Email Notification**: An email notification is sent to the recipient's email address configured in the code.

## 📂 File Structure

```plaintext
.
├── node-wifi.ino    # Code for Wi-Fi connectivity and email sending
└── arduino.ino      # Code for eye-tracking and safety mechanism
```

## 📜 Code Explanation

### `node-wifi.ino`

This file handles Wi-Fi connectivity and email sending using the ESP8266/ESP32 module.

```cpp
#include <SoftwareSerial.h>
#include <ESP_Mail_Client.h>
#include <WiFi.h> // For ESP32
#include <ESP8266WiFi.h> // For ESP8266
```

- **SoftwareSerial**: Used for communication between Arduino and the Wi-Fi module.
- **WiFi.h/ESP8266WiFi.h**: Used to connect to the Wi-Fi network.
- **ESP_Mail_Client.h**: Handles the SMTP email sending process.

### `arduino.ino`

This file handles the eye-tracking sensor and safety mechanisms, including the relay module, LED, and buzzer.

```cpp
const int eyeSensorPin = 2;         // Eye-tracking sensor pin
const int relayPin = 3;             // Relay module control pin
const int eyeClosedDuration = 3000; // 3 seconds in milliseconds
const int eyeCLOSEDDURATION = 5000; // 5 seconds in milliseconds
const int led = 4;
const int buzzer = 5;
```

- **eyeSensorPin**: Connected to the eye-tracking sensor to monitor the driver's eye state.
- **relayPin**: Controls the relay module, which can stop the car if the driver is drowsy.
- **eyeClosedDuration**: Time duration after which the LED and buzzer are activated if the driver's eyes remain closed.
- **eyeCLOSEDDURATION**: Time duration after which the relay module is triggered to stop the car.

### 🔄 Data Transfer: Arduino to ESP8266/ESP32

The communication between the Arduino and the ESP8266/ESP32 module is achieved using the `SoftwareSerial` library. The Arduino processes data from the eye-tracking sensor and then sends a signal to the ESP8266/ESP32 module via a serial connection.

#### How It Works:

1. **Sensor Data Processing**: The Arduino continuously reads data from the eye-tracking sensor. Based on the sensor input, it determines whether the driver's eyes are closed beyond the predefined thresholds (3 seconds and 5 seconds).

2. **Signal Transmission**: Once the Arduino detects that the driver's eyes have been closed for 5 seconds, it sends a signal to the ESP8266/ESP32 module using the `SoftwareSerial` communication.

3. **Email Alert**: Upon receiving the signal from the Arduino, the ESP8266/ESP32 module connects to the Wi-Fi network and sends an email alert to the recipient.

#### Why This Approach:

- **Separation of Concerns**: By dividing the tasks between the Arduino and the ESP8266/ESP32, the system can efficiently handle both sensor monitoring and network communication. The Arduino focuses on real-time processing of sensor data, while the ESP8266/ESP32 handles the network-intensive task of sending an email.
- **Modular Design**: This approach allows for easier debugging and modification. If the email functionality needs to be updated or replaced, it can be done without altering the core sensor processing code on the Arduino.

### 📝 How It Works

1. **Monitoring Eye State**:
   - The eye-tracking sensor monitors the driver's eye state.
   - If the eyes remain closed for 3 seconds, the system activates the LED and buzzer.
   - If the eyes remain closed for 5 seconds, the relay module stops the car.

2. **Sending Email Alerts**:
   - The system connects to the Wi-Fi network using the ESP8266/ESP32 module.
   - If the driver is detected as drowsy for 5 seconds, an email alert is sent to the recipient's email address.

### 🧪 Testing

- **Testing the Eye-Tracking Sensor**:
  - Simulate closing and opening the eyes by triggering the sensor.
  - Observe the behavior of the LED, buzzer, and relay module.
  - Check if an email notification is sent when the eyes remain closed for 5 seconds.
