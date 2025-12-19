# Robotnik - Robot Design and Competition

## ℹ️ Project Overview
A multi-tasking robot with self-navigation was designed. The power supply, control system, sensor navigation and mechanical subsystems was planned thoroughly prior to execution. 

## 🤖 Robot Design

![Cover photo](media/cover_photo.jpeg)

Tasks to cover: 
1. Line following - continous and dashed lines.
2. Wall following (circular wall).
3. Ramp completion and climbing.
4. Obstacle avoiding.
5. Box picking.
6. Ball shooting.

[Task Sheet - 📎Robot Design Task](media/Robot_Design_Task_2025.pdf)

## Hardware Specs 🦾
• Dimensions - 220mm x 180mm
• Power Supply - 3 cell LiPo 11.1 V
• Components 
1. Arduino Mega 2560[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)](docs/arduino.md)


2. Aptinex Reykha S8 IR sensor array.
3. 12V JGA-25370 motors.
4. BTS 7960 motor drivers.
5. MG90 and MG995 servo motors.
6. VL53LOX TOF sensors.
7. TCS3200 colour sensors.
8. DC-DC step down buck convertors.
9. OLED SPI display.

## Software specs 💻
• Programming language - C++

• IDE - VS Code [![VS Code](https://img.shields.io/badge/VS%20Code-Setup-007ACC?style=for-the-badge&logo=visualstudiocode)](docs/vscode.md)

• Platform IO [![PlatformIO](https://img.shields.io/badge/PlatformIO-Documentation-blue?style=for-the-badge&logo=platformio)](docs/platformio.md)

• 3D Modelling 
[![SolidWorks](https://img.shields.io/badge/SolidWorks-red?style=for-the-badge&logo=dassaultsystemes&logoColor=white)](docs/solidworks.md)

 ## Mechanisms

 1. Gripper mechanism for ball picking.
![Mechanical parts](Mechanical_parts.jpg)

![Ball picking arena](Ball_arena.jpg)

The balls were mounted on a 10cm cylindrical mount and 6 such mounts were kept together in a circular fashion. Therefore a cylindrical arm was selected to pick the balls.

3. Clamping and dragging mechanism for box picking.
<p align = "center">
 <img src = "media/Box_picking.jpg",width = "45%">
 <img src = "media/Box_arena.png",width = "45%">
</p>


Sinces boxes were of dimensions 5cm x 10cm x 10cm, it was decided to grab the box and drag along the way until being placed in the reserved ares of respective colour.

4. Ball shooting mechanism.
![Ball shooting](Ball_shooting.jpg)

The task was to shoot the picked ball through a ring placed in a pre-determined location. Hence a design with two design BLDC motors was used.

## Arena
![Arena](Arena.png)




