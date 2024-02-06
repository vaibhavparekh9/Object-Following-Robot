# Object-Following-Robot

## Explanation of the code:

During the initiation of the software coding phase, two parameters were left variable:

• Distance between both WiFi modules

• The delay in each microcontroller to maintain synchronization

It is known that the difference in RSSI values of both WiFi modules is sensitive to the distance between them, following a directly proportional relationship. Therefore, this value was finalized to be 70 cm.

![image](https://github.com/vaibhavparekh9/Object-Following-Robot/assets/153970846/1f4699d5-f903-479c-b53b-aa36b974a171)
<img src='![image](https://github.com/vaibhavparekh9/Object-Following-Robot/assets/153970846/1f4699d5-f903-479c-b53b-aa36b974a171)' width=100> 

### 1. Code for the Right WiFi Module:

Initially, all the necessary libraries and dependencies are imported for Software Serial Communication and for enabling the WiFi capabilities of the NodeMCU. Subsequently, the credentials of the target WiFi Hotspot, such as its Name or SSID, and its password are stored in two separate variables. In the setup section, serial communication is established between the right and left WiFi modules, where the right module sends the latest recorded RSSI value to the left module. Additionally, the WiFi connection with the target hotspot source is established in the setup section.

In the void loop section, an infinite loop is executed only after the connection with the target WiFi source is established. Here, a predefined function called WiFi.RSSI() is used to extract the latest values of RSSI. As the RSSI value is typically negative, it needs to be flipped into the positive range for ease of interpretation and further calculations. Subsequently, this positive RSSI value is sent to the left module via serial communication, and a delay of 1 second is implemented to synchronize it with other microcontrollers in the system, namely, the Left WiFi module and Arduino.

### 2. Code for the Left WiFi Module:

Initially, all the necessary libraries and dependencies are imported for Software Serial Communication and for enabling the WiFi capabilities of the NodeMCU. Subsequently, the credentials of the target WiFi Hotspot, such as its Name or SSID, and its password are stored in two separate variables.

In the setup section, serial communication is established between the right and left WiFi modules, as well as between the Left WiFi module and Arduino. The right module sends the latest RSSI value to the left module, and the Left WiFi module sends the latest RSSI values of both WiFi modules, recorded and received from the Right module. Additionally, in the setup section, the WiFi connection is established with the target hotspot source.

In the void loop section, an infinite loop is executed only after the connection with the target WiFi source is established. Here, a predefined function called WiFi.RSSI is used to extract the latest values of RSSI. Since the RSSI value is usually negative, it is flipped into the positive range for ease of interpretation and further calculations. Subsequently, this recorded RSSI value of the left module is transmitted to Arduino via Serial Communication.

Following this, it reads data from the right WiFi module, stores the value in another variable, and then sends the data received from the right module to Arduino. A delay of 1 second is implemented to keep it in synchronization with other components.

### 3. Code for the Arduino:

At the start, various variables necessary for storing values and performing calculations are defined. Additionally, the pins for the motor driver and serial communication are initialized. In the setup part, Serial Communication with the Left WiFi module is established, and the pins for the motor driver are set to output mode.

In the void loop section, a counter is initialized with an initial value of 2. This is done to keep track of which data is being processed at a given time. If the counter is 2, it means that the Arduino will be reading the RSSI value for the Left module. If the counter is 1, then the RSSI value will be for the Right module. These received data are stored in separate variables for future calculations. Additionally, the received values are squared and stored in separate variables for amplification purposes.

When the counter reaches a value of 0, a series of conditional statements are checked for decision-making. Initially, the difference between Left and Right values and their squares is calculated to determine the direction of the object (in this case, the WiFi hotspot source).

• If the difference between Left and Right values is positive, the object is in the right direction. This indicates that the value of the right RSSI is less than the left RSSI, implying that the right RSSI is stronger than the left one.

• If the difference between Left and Right values is negative, the object is in the left direction. This suggests that the value of the right RSSI is greater than the left RSSI, indicating that the left RSSI is stronger than the right one.

Following this, various conditional statements are defined to check whether the values are within the threshold range or not. If within the threshold range, the robot stops; if beyond the threshold range, other conditions are checked to evaluate the direction and plan movement accordingly. Additionally, various functions are defined at the end for different pin output instructions based on the required movement of the robot.

