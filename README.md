
# WiFi LED Controller

This project demonstrates how to use an Arduino Uno R4 WiFi to control an LED over Wi-Fi through a simple web interface.

## Features

- Host a web server on the Arduino Uno R4 WiFi board.
- Toggle the built-in LED on or off using the web interface.
- Real-time LED status display.

## Components

- Arduino Uno R4 WiFi
- USB cable
- Wi-Fi network

## Setup

1. Connect the Arduino Uno R4 WiFi board to your computer.
2. Upload the provided sketch (`LED_Control.ino`) to the board.
3. Ensure your Wi-Fi credentials are set correctly in the sketch:
   ```cpp
   const char* ssid = "SSID";
   const char* password = "PASSWORD";
   ```
4. Open the Serial Monitor (baud rate: 9600) to check the connection status.

## How to Use

1. After the board connects to the Wi-Fi, the Serial Monitor will display the assigned IP address.
2. Open a web browser and navigate to the IP address.
3. Use the buttons on the web interface to turn the LED on or off.
4. The current LED status will be displayed on the web page.

## Web Interface

- **Turn On**: Sends a request to `/LED=ON` to turn on the LED.
- **Turn Off**: Sends a request to `/LED=OFF` to turn off the LED.
- **Real-Time Status**: Displays whether the LED is currently on or off.

## Code Overview

### Wi-Fi Connection

The board attempts to connect to the specified Wi-Fi network within 20 seconds. If successful, it starts a web server on port 80.

### Web Server

The server listens for incoming client requests. Based on the request URL:
- `/LED=ON`: Turns the LED on.
- `/LED=OFF`: Turns the LED off.

### Web Page Design

The web interface uses basic HTML and CSS for styling and interactivity.

## Troubleshooting

- Ensure your Wi-Fi credentials are correct.
- Check that the Serial Monitor is set to 9600 baud.
- Ensure no other devices are using the same IP address.

## License

This project is open-source and available under the MIT License. -->
