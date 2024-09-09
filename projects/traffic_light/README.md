# ESP32 Traffic Light Controller with Micro-ROS

This project implements a traffic light controller using an ESP32 microcontroller and Micro-ROS. It combines hardware control of LED traffic lights with a web interface and ROS 2 communication.

## Features

1. **Traffic Light Control**: Controls a set of LEDs representing traffic lights (green, yellow, red, and blue).
2. **Web Interface**: Provides a web-based user interface for remote control and monitoring.
3. **Micro-ROS Integration**: Utilizes Micro-ROS for communication with ROS 2 systems.
4. **Wi-Fi Connectivity**: Connects to a Wi-Fi network for remote access and control.

## Components

- **Main Application** (`main.c`): Initializes the system, sets up Wi-Fi, and manages the main control loop.
- **Light Control** (`light_control.c`, `light_control.h`): Handles LED control and traffic light sequences.
- **Web Server** (`website.c`): Implements a simple HTTP server for the web interface.
- **Wi-Fi Connection** (`wifi.c`): Manages Wi-Fi connectivity.
- **Micro-ROS Task**: Handles ROS 2 communication using Micro-ROS.

## Setup and Usage

1. Configure the project using `idf.py menuconfig` to set Wi-Fi credentials and other parameters.
2. Build and flash the project to your ESP32 device.
3. Access the web interface via the ESP32's IP address.

## Dependencies

- ESP-IDF
- Micro-ROS for ESP32
- ROS 2 (for communication with the device)

## Future Improvements

- Implement more advanced traffic light patterns
- Add sensor integration for adaptive traffic control
- Enhance the web interface with real-time updates
