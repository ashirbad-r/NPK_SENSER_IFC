#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // Reset pin # (or -1 if sharing Arduino reset pin)

#define RE 8
#define DE 7

const byte cond[] = { 0x01, 0x03, 0x00, 0x02, 0x00, 0x01, 0x25, 0xca };
const byte ph[] = { 0x01, 0x03, 0x00, 0x03, 0x00, 0x01, 0x74, 0x0a };
const byte nitro[] = { 0x01, 0x03, 0x00, 0x04, 0x00, 0x01, 0xc5, 0xcb };
const byte phos[] = { 0x01, 0x03, 0x00, 0x05, 0x00, 0x01, 0x94, 0x0b };
const byte pota[] = { 0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0b };
const byte sali[] = { 0x01, 0x03, 0x00, 0x07, 0x00, 0x01, 0x35, 0xcb };

uint16_t values[11];
char buffer[40];

SoftwareSerial mod(2, 3);

#define OLED_ADDRESS 0x3C  // OLED I2C address

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  mod.begin(4800);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  delay(1000);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println(F("PHYTEC. INDIA"));
  display.display();
  delay(4000);
  display.clearDisplay();
}

void loop() {
  uint16_t val1, val2, val3, val4, val5, val6;

  val1 = sensor_request(nitro[0], nitro[1], nitro[2], nitro[3], nitro[4], nitro[5], nitro[6], nitro[7]);
  delay(2000);
  displaySensorReading("Nitrogen", val1);

  val2 = sensor_request(phos[0], phos[1], phos[2], phos[3], phos[4], phos[5], phos[6], phos[7]);
  delay(2000);
  displaySensorReading("Phosphorous", val2);

  val3 = sensor_request(pota[0], pota[1], pota[2], pota[3], pota[4], pota[5], pota[6], pota[7]);
  delay(2000);
  displaySensorReading("Potassium", val3);

  val4 = sensor_request(ph[0], ph[1], ph[2], ph[3], ph[4], ph[5], ph[6], ph[7]);
  delay(2000);
  displaySensorReading("PH", val4);

  val5 = sensor_request(cond[0], cond[1], cond[2], cond[3], cond[4], cond[5], cond[6], cond[7]);
  delay(2000);
  displaySensorReading("Conductivity", val5);

  val6 = sensor_request(sali[0], sali[1], sali[2], sali[3], sali[4], sali[5], sali[6], sali[7]);
  delay(2000);
  displaySensorReading("Salinity", val6);

  delay(3000);
}

void displaySensorReading(String sensorName, uint16_t value) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println(sensorName + " = " + String(value) + " Mg/Kg");
  display.display();
}

uint16_t sensor_request(byte d1, byte d2, byte d3, byte d4, byte d5, byte d6, byte d7, byte d8) {
  byte inicio;
  uint16_t hbyte;
  while (mod.available()) mod.read();
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
  mod.write(d1);
  mod.write(d2);
  mod.write(d3);
  mod.write(d4);
  mod.write(d5);
  mod.write(d6);
  mod.write(d7);
  mod.write(d8);
  mod.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(250);

  inicio = 0;
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    if (inicio == 0 and values[i] == 0 and mod.available()) values[i] = mod.read();
    if (inicio == 0 and values[i] == 0 and mod.available()) values[i] = mod.read();
    if (inicio == 0 and values[i] == 0 and mod.available()) values[i] = mod.read();
    inicio = 1;
  }

  return (values[3] << 8 | values[4]);
}
