# NPK_SENSER_IFC
This project is designed to interface with NPK (Nitrogen, Phosphorus, Potassium) sensors and display their readings on an OLED screen. The readings include values for various soil parameters like Nitrogen, Phosphorus, Potassium, PH, Conductivity, and Salinity. The data is read via a Modbus communication protocol.

Hardware Requirements
Arduino Board (or compatible microcontroller)
NPK Sensors: Sensors for Nitrogen, Phosphorus, Potassium, pH, Conductivity, and Salinity
OLED Display: 128x64 OLED display (I2C)
Software Serial Communication: For Modbus communication with sensors
Wiring Setup: Ensure that the sensors are correctly connected to the microcontroller via appropriate pins for communication (e.g., RX, TX for SoftwareSerial, and control pins for Modbus)
Software Requirements
Arduino IDE
Libraries:
Adafruit_GFX: For OLED display control.
Adafruit_SSD1306: For OLED display driver.
SoftwareSerial: For serial communication between Arduino and the NPK sensors.
Wire: For I2C communication with the OLED display.
Pin Definitions
RE (Pin 8): Control pin for enabling Modbus communication (Receiver Enable).
DE (Pin 7): Control pin for enabling Modbus communication (Driver Enable).
SoftwareSerial Pins:
RX (Pin 2) and TX (Pin 3) for communication with the NPK sensors.
Description
The main objective of this project is to read data from the NPK sensors and display the results on an OLED screen. The following parameters are read from the sensors:

Nitrogen (N)
Phosphorus (P)
Potassium (K)
pH Level
Conductivity
Salinity
Each of these values is displayed on the OLED screen, one after the other.

Key Functions:
sensor_request: This function sends a Modbus request to the sensor and retrieves the data. The data is parsed to extract the measurement values.
displaySensorReading: This function updates the OLED display with the sensor name and its corresponding value.
Code Overview
Initialization:

Serial communication for debugging.
Modbus communication setup via SoftwareSerial.
OLED display initialization.
Sensor Data Acquisition:

The sensors are queried one by one with a Modbus RTU request.
The corresponding values are fetched and displayed on the OLED screen.
Display Output:

Each sensor value is displayed for 3 seconds, one sensor at a time.
Modbus Communication:

SoftwareSerial is used to communicate with the NPK sensors, sending requests and receiving data.
How to Use
Upload the Code:

Open the NPK_SENSER_IFC.ino file in Arduino IDE.
Select the correct board and port in the Arduino IDE.
Upload the code to the Arduino board.
Connect the Hardware:

Connect the NPK sensors to the appropriate pins on your Arduino board.
Connect the OLED display via I2C (SCL and SDA).
Connect the RE and DE pins to the Arduino for Modbus control.
Monitor the Output:

The readings for each sensor will be displayed on the OLED screen.
The data will update periodically, showing values in mg/kg for each sensor.
Adjustments:

You can modify the sensor requests (const byte cond[], const byte ph[], etc.) if your sensor configuration differs.
Troubleshooting
OLED Not Displaying:
Ensure the I2C address is correct and check wiring for SDA and SCL.
Modbus Communication Issues:
Double-check the sensor wiring, especially the RX/TX pins.
Ensure the sensor baud rate matches the code (4800 in this case).
