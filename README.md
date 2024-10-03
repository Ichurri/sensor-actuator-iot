# ESP32 Sensor-Actuator System with TCP Server

## Project Overview

This project involves an **ESP32-based system** where a **sensor** and an **actuator** communicate with a **TCP server**. The sensor measures distances using an **ultrasonic sensor** and sends corresponding states to the server. The actuator then receives these states and activates the appropriate **LED** based on the distance detected. The system operates over a **WiFi network** and uses the **TCP protocol** for communication.

### Features

- **Distance Measurement**: The sensor measures distance using an ultrasonic sensor and determines the state based on predefined distance ranges.
- **LED Control**: The actuator receives the state from the server and controls the LEDs accordingly (red, yellow, green, or blue).
- **TCP Communication**: Both the sensor and the actuator connect to the server via TCP, and the server forwards the sensor’s state to the actuator in real time.

## Requirements

- **Hardware**:
  - 2x ESP32 modules
  - 1x Ultrasonic sensor (e.g., HC-SR04)
  - 4x LEDs (Red, Yellow, Green, Blue)
  - Jumper wires, breadboard
  - WiFi connection

- **Software**:
  - Arduino IDE (for programming the ESP32)
  - Python 3.x (for running the TCP server)
  - Python libraries: `socket`, `threading`

## Distance-Based States

The system operates using four states based on the distance measured by the sensor:

| **State**      | **LED**        | **Distance Range** |
|----------------|----------------|--------------------|
| `STATE_BLUE`   | Blue LED       | `d > 40 cm`        |
| `STATE_GREEN`  | Green LED      | `25 cm ≤ d < 40 cm`|
| `STATE_YELLOW` | Yellow LED     | `15 cm ≤ d < 25 cm`|
| `STATE_RED`    | Red LED        | `d < 15 cm`        |
| `STATE_OFF`    | All LEDs off   | No valid distance  |

## System Architecture

- **ESP32 Sensor**:
  - Measures distance using the ultrasonic sensor.
  - Sends the corresponding state to the server based on the distance range.
  
- **TCP Server**:
  - Receives the state from the sensor.
  - Forwards the state to the actuator.
  
- **ESP32 Actuator**:
  - Receives the state from the server.
  - Turns on the appropriate LED based on the state.

## Project Structure

        sensor-actuator-iot
        │
        ├── Actuator
        │   ├── Actuator.ino             # ESP32 actuator code
        │   ├── Led.h                    # LED control class
        │   ├── WiFiConnection.h         # WiFi connection class
        │   └── TcpClient.h              # TCP client class
        ├── Diagrams
        │   ├── Class.ino             # Class diagram
        │   ├── Flowchart.h           # Flowchart diagram
        │   ├── Sequence.h            # Sequence diagram
        │
        ├── Docs
        │   ├── Report.pdf             
        │   ├── Rubric.pdf             
        │
        ├── Sensor
        │   ├── Sensor.ino               # ESP32 sensor code
        │   ├── UltrasonicSensor.h       # Ultrasonic sensor class
        │   ├── WiFiConnection.h         # WiFi connection class
        │   └── TcpClient.h              # TCP client class
        │
        ├── TcpServer
        │   └── TcpServer.py             # TCP server code in Python
        │
        └── README.md                    # Project documentation

## Setup Instructions

### 1. Flashing the Sensor and Actuator Code

1. Open **Sensor.ino** and **Actuator.ino** in the **Arduino IDE**.
2. Modify the `WiFiConnection` class to include your **SSID** and **password**.
3. Upload the **Sensor** code to the first ESP32.
4. Upload the **Actuator** code to the second ESP32.

### 2. Running the TCP Server

1. Navigate to the `TcpServer` folder in the terminal.
2. Run the Python server with the following command:
   ```bash
   python TcpServer.py
    ```
3. The server will listen on the specified IP and port for connections from both the sensor and actuator.

### 3. Testing system

- Sensor
    - Move an object at varying distances from the ultrasonic sensor.
    - The sensor will send the state to the server based on the measured distance.

- Actuator
    - The actuator receives the state from the server and lights up the corresponding LED based on the state.

## Troubleshooting

- Sensor or actuator not connecting:
    - Check th WiFi credentials and ensure both ESP32s are in range of the Wifi network.
    - Verify the server IP address matches the one printed when running `TcpServer.py`.

- LED not responding:
    - Ensure the LEDs are connected to the correct pins as specified in `Led.h`.

- TCP connecetion drops:
    - Ensure the server is running and is reachable by both the sensor and actuator.

## Future Improvements

- Implement MQTT for more robust messaging between devices.
- Add feedback from the actuator to the server to confirm action completion.
- Expand the system to include more sensors and actuators for a larger IoT network.
