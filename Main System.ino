#include <WiFi.h>
#include "ThingSpeak.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#include "DHT.h"
#define DHTPIN 5     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

float h, t;
const char * write_api = "";//Replace with Thingspeak write API
const char* ssid     = "";//Replace with Network SSID
const char* password = "";//Replace with Network Password
unsigned long ch_no = ;//Replace with Thingspeak Channel number
WiFiClient  client;

int sensorPin = 23;
int m;
int wifi_led = 2;
void setup()
{
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(wifi_led, OUTPUT);
  digitalWrite (wifi_led, LOW);
  Wire.begin();
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  digitalWrite (wifi_led, HIGH);
  ThingSpeak.begin(client);
  delay(1000);
}

void loop()
{
  read_sensors();
  update_DISPLAY();
  update_iot();
}


void read_sensors()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  m = digitalRead(sensorPin);
}
void update_DISPLAY()
{
  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    Serial.println("Display Not Ini");
  else
    Serial.println("Display Ini");

  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  display.clearDisplay();              // Clear screen
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("  IoT based SMART  ");
  display.setCursor(0, 11);             // Set cursor position, start of line 1
  display.print("AGRICULTURE SYSTEM.");
  display.setCursor(0, 19);             // Set cursor position, start of line 1
  display.print("---------------------");
  display.setCursor(0, 26);             // Set cursor position, start of line 1
  display.print("Moisture ");
  if (m == LOW)
    display.print("Detected");
  else
    display.print("Not Detected");

  display.setCursor(0, 33);             // Set cursor position, start of line 1
  display.print("---------------------");
  display.setCursor(0, 40);             // Set cursor position, start of line 2
  display.print("Temperature= ");
  display.print(t);
  display.print(" C");
  display.setCursor(0, 51);            // Set cursor position, line 2 10th character
  display.print("Humidity= ");
  display.print(h);
  display.print(" %Rh");
  display.setCursor(0, 60);             // Set cursor position, start of line 2
  display.print("---------------------");

  display.display();
  delay(1000);
}

void update_iot()
{
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  ThingSpeak.setField(3, m);
  ThingSpeak.writeFields(ch_no, write_api);
}
