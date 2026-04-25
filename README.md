\# 🚦 Arduino 4-Way Traffic Light Controller



\## 📝 Project Overview

This repository contains the source code for a 4-way traffic light controller model built with an \*\*Arduino Uno R3\*\*. The system manages two intersecting roads (Phase 1 - Vertical and Phase 2 - Horizontal) using symmetric phase routing to ensure there are no conflicting green signals. A key highlight of this project is the integration of a countdown timer using a \*\*Common Anode 7-segment display\*\*, which is intelligently driven via bitwise operations.



\## ✨ Key Features

\* \*\*Symmetric Phase Routing:\*\* Automatically manages the Red - Yellow - Green sequences for two pairs of traffic light poles.

\* \*\*Common Anode Optimization:\*\* Standard HEX codes are dynamically bit-inverted in software (`!((segmentState >> i) \& 1)`), eliminating the need for a manually converted lookup table.

\* \*\*GPIO Resource Utilization:\*\* Cleverly utilizes the Analog `A0` pin as a standard Digital output to overcome pin shortages for the LEDs.

\* \*\*Failsafe Mechanism:\*\* Actively turns off all signals before switching phases, completely preventing accidental overlapping of light colors.



\## 🛠 Hardware Requirements

\* 1x Arduino Uno R3 Board.

\* 1x Common Anode 7-segment LED Display.

\* 6x Single LEDs (2 Green, 2 Yellow, 2 Red) representing two traffic light clusters.

\* Current-limiting resistors (220Ω - 330Ω recommended).

\* Jumper wires and a Breadboard.



\## 🔌 Pinout \& Wiring



\### Countdown Timer (7-Segment LED)

| 7-Segment Pin | Arduino Pin |

| :---: | :---: |

| a, b, c, d, e, f, g | `D2` to `D8` |

| COM | Connect to `5V` |



\### Traffic Light Clusters

| State | Phase 1 (Vertical) | Phase 2 (Horizontal) |

| :--- | :---: | :---: |

| \*\*Green LED\*\* | `D9` | `D12` |

| \*\*Yellow LED\*\* | `D10` | `D13` |

| \*\*Red LED\*\* | `D11` | `A0` (Used as Digital) |



\## 🚀 Usage Instructions

1\. Wire the hardware components according to the Pinout table above.

2\. Open the source code using the \*\*Arduino IDE\*\*.

3\. Connect your Arduino Uno to your computer via a USB cable.

4\. Select the correct Board (`Arduino Uno`) and corresponding `COM` port from the \*\*Tools\*\* menu.

5\. Click the \*\*Upload\*\* button to flash the program and observe the system in action.



\*(Note: You can easily adjust the duration of each light phase in the `loop()` function by modifying the `duration` parameter inside the `trafficPhase` function calls).\*

