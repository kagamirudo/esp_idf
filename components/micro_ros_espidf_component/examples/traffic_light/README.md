---
title: Traffic Light Control with micro-ROS
author: Gary Pham - gp492
date: December 18th 2024
geometry: margin=2cm
output: pdf_document
header-includes:
 - \usepackage{fvextra}
 - \DefineVerbatimEnvironment{Highlighting}{Verbatim}{breaklines,commandchars=\\\{\}}
---

## Overview

This project has been updated to support multiple ESP32 boards using a master-slave protocol. One node acts as a subscriber, while the rest function as publishers. The source code is structured to allow configuration via `#define` directives, enabling you to set each board as either ROOT or CHILD, depending on its role in the network. The previous functionality has been retained, with additional features added to enhance the project.

## Project Repository

For the complete source code and additional resources, please visit the project repository:

[Traffic Light Control with micro-ROS on ESP32](https://github.com/kagamirudo/esp_idf/tree/main/components/micro_ros_espidf_component/examples/traffic_light)

For a website version of this project, please visit:

[Traffic Light Control with micro-ROS on ESP32 (Website Version)](https://github.com/kagamirudo/esp_idf/tree/main/projects/traffic_light)

This repository contains all the necessary files and instructions to set up and run the traffic light control system using micro-ROS on multiple ESP32 boards.

## Features

- Simulates a traffic light sequence with configurable timings
- Remote control via ROS2 messages
- Supports stopping and starting the traffic light sequence
- Uses micro-ROS for communication between the ESP32 nodes and a ROS2 environment
- Configurable master-slave architecture for multiple ESP32 boards as in `service.h`
  ```c
  #define ROOT
  #define CHILD
  ```
  Just comment either one to flash the board

## Hardware Requirements

- Multiple ESP32 development boards
- 3 LEDs (red, yellow, and green) per board
- 3 resistors (220 $\Omega$ - 330 $\Omega$) per board
- Breadboard and jumper wires

## Software Requirements

- ESP-IDF (v4.3 or later)
- micro-ROS component for ESP-IDF
- ROS2 environment (tested with Humble Hawksbill)

## Circuit Connection

1. Connect the LEDs to the following GPIO pins on each ESP32:
   - Red LED: GPIO 21
   - Yellow LED: GPIO 19
   - Green LED: GPIO 18
2. Connect the cathode (shorter leg) of each LED to ground through a resistor.

## Building and Flashing

1. Set up your ESP-IDF environment.
2. Navigate to the example directory.
3. Before building, ensure you have permission to access the ESP32 device:
   ``` bash
   sudo chmod 666 /dev/ttyUSB0
   ```
   Replace `/dev/ttyUSB0` with the appropriate device path if different.

4. Open a new terminal and run the micro-ROS agent using Docker:
   ``` bash
   docker run -it --rm --net=host microros/micro-ros-agent:humble udp4 --port 8888 -v6
   ```
   This command will pull the micro-ROS agent Docker image (if not already present) and run it with the necessary permissions to access network and device resources.

5. Run the Docker container for building and flashing:
   ``` bash
   cd ./../../.
   docker run -it --rm --user espidf --volume="/etc/timezone:/etc/timezone:ro" -v  $(pwd):/micro_ros_espidf_component -v  /dev:/dev --privileged --workdir /micro_ros_espidf_component/examples/traffic_light microros/esp-idf-microros:latest /bin/bash
   ```
   This command will start a Docker container with the ESP-IDF and micro-ROS environment set up. You'll be dropped into a bash shell inside the container.

6. Inside the Docker container, configure the project:
   ``` bash
   idf.py menuconfig
   ```
   - Set the WiFi SSID and password inside "Micro-ROS Settings".
   - Set the IP address of your machine in "Micro-ROS Agent IP".
   - Set the serial port in "Micro-ROS Agent Port" (<u>optional</u>, but if you want to use the serial port, you need to set it again in step 4 "port" parameter). Go to [Troubleshooting](#troubleshooting) for more detail.
   - Save and exit.

7. Build the project:
   ``` bash
   idf.py build
   ```

8. Flash the firmware to your ESP32:
   ``` bash
   idf.py -p PORT flash monitor
   ```
   Replace PORT with your ESP32's serial port (e.g., /dev/ttyUSB0).\
   Or:
   ``` bash
   idf.py flash monitor
   ```

## Usage

1. Ensure all ESP32 nodes are connected to the same LAN network and have established communication with the micro-ROS agent.
2. Control the traffic light using ROS2 messages:
    - To start the traffic light sequence with custom timings:
    ``` bash
    ros2 topic pub --once /led std_msgs/msg/String "data: '5.0 2.0 5.0'"
    ```
    This sets green to 5 seconds, yellow to 2 seconds, and red to 5 seconds.
    - To stop the traffic light sequence:
    ``` bash
    ros2 topic pub --once /led std_msgs/msg/String "data: 'stop'"
    ```
    - Since we only send messages once, it may not received due to UDP packet loss. Retry until it is received or remove 
flag "--once" to continue sending messages.
3. Observe publish message of each node:
    ```bash
    ros2 topic echo /led_pub
    ```
    This might depends on the node name, just make sure using `node list` to check.
4. To visualize the nodes and debug, use the `rqt` tool to see the node graph.

## Customization

- Modify the `light_control.h` and `light_control.c` files to change the GPIO pins or add more LEDs.
- Adjust the default timings in the `main.c` file.

## Troubleshooting

- Check proxy for host computer to avoid deny connection from board. Using port with allowance from `ufw` in Linux machine
  ``` bash
  ufw allow PORT
  ```
- Ensure your ESP32 is connected to the same network as your development machine.
- Check the serial monitor output for any error messages or connection issues.
- Verify that the micro-ROS agent is running and accessible from the ESP32.
- You may need to flash the firmware again if error messages are shown in the monitor "Aborting".

## Future Plans and Upcoming Features

1. Extend to Control a Whole Traffic System:
   - Implement multiple traffic light nodes to simulate a city-wide traffic system.
   - Create a central traffic management node to coordinate multiple intersections.
   - Develop algorithms for traffic flow optimization and adaptive signal timing.

2. Establish Inter-Node Communication:
   - Implement pub/sub communication between traffic light nodes for synchronization.
   - Use custom ROS2 messages to share traffic data and timing information.
   - Example of a potential custom message:
     ```
     # TrafficLightStatus.msg
     uint8 intersection_id
     uint8 current_state  # 0: Green, 1: Yellow, 2: Red
     float32 time_in_state
     float32[] queue_lengths  # Array of queue lengths for each lane
     ```

3. Sensor Integration:
   - Add support for simulated or real sensors (e.g., inductive loops, cameras) to detect vehicle presence and traffic density.
   - Use sensor data to inform adaptive traffic light timing.

4. User Interface:
   - Develop a web-based dashboard for monitoring and controlling the entire traffic system.
   - Implement visualization of traffic flow and light states across multiple intersections.

5. Machine Learning Integration:
   - Explore the use of reinforcement learning algorithms for optimizing traffic flow.
   - Implement prediction models for traffic patterns based on historical data.

6. Fault Tolerance and Redundancy:
   - Implement failover mechanisms for traffic light nodes.
   - Develop a system for graceful degradation in case of node failures.

7. Performance Optimization:
   - Optimize communication protocols for reduced latency and bandwidth usage.
   - Implement edge computing techniques to distribute processing load.

8. Simulation Environment:
   - Create a simulation environment to test traffic management strategies without physical hardware.
   - Integrate with existing traffic simulation software for more realistic scenarios.

To start working on these features, it is recommended to refactor the current codebase to support multiple nodes and more complex communication patterns. This may involve creating additional ROS2 packages, implementing new message types, and restructuring the main application logic to support a distributed system architecture.

## Conclusion

This traffic light example demonstrates the power and flexibility of micro-ROS on ESP32 platforms. By implementing a simple yet functional traffic light system, I've showcased how embedded systems can be integrated into the broader ROS2 ecosystem. This project serves as a starting point for more complex IoT and robotics applications, particularly in the domain of smart city infrastructure and traffic management.

Key takeaways from this project include:

1. The ability to run ROS2 nodes on resource-constrained devices like the ESP32.
2. Real-time communication between embedded systems and a ROS2 network.
3. The potential for scaling from a single traffic light to a comprehensive traffic management system.

It is encouraged to experiment with this example, contribute to its development, and explore the vast possibilities that micro-ROS and ESP32 offer in creating intelligent, connected systems.
