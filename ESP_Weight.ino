#include <LiquidCrystal_I2C.h>
#include <Thread.h>
#include <ESP8266WiFi.h>
#include "myserver.h"
#include "myfb.h"
#include "myweight.h"
//#include "LCDisp.h"

float emptyWeight = 3;
float space = 5;
unsigned long previousMillis = 0;
bool connectMsg = false;

//LCDisp disp;
/*Put your SSID & Password*/
const char* ssid = "Weight";            // Enter SSID here
const char* password = "12345678";  //Enter Password here


uint8_t box[8] = { 0xff,    // 0000000 Create a 5X7 bit heart character using pattern
                   0xff,    // 0001010
                   0xff,   // 0011111
                   0xff,   // 0011111
                   0xff,    // 0001110
                   0xff,    // 0000100
                   0xff
                 };  //

//My simple Thread
Thread myThread = Thread();
MyWeight w;
MyServer s;
MyFB fb;

int sda_pin = D2;  // pin to connect to SDA pin on LCD (can be any data pin)
int scl_pin = D1;  // pin to connect to SCL pin on LCD (can be any data pin)
LiquidCrystal_I2C lcd(0x27, 20, 4);  // start up LCD as 20 characters X 4 lines
void sendWeight() {
  // set Float  value
  Firebase.setFloat(fb.data, "weight", w.weight);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);

  //disp.startMsg();
  Wire.begin(sda_pin, scl_pin);
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.createChar(1, box);
  lcd.home();
  lcd.setCursor(4, 0);
  lcd.print("Gas Weight");
  lcd.setCursor(5, 1);
  lcd.print("Monitoring");
  lcd.setCursor(6, 2);  // set cursor to 0th position on line 3
  lcd.print("System ");
  for (int i = 0; i < 20; i++) {
        lcd.setCursor(i, 3);
        lcd.write(byte(1));
        delay(150);
    }
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println(WiFi.localIP());
  myThread.onRun(sendWeight);
  myThread.setInterval(1000);

  s.setUp();
}

void loop() {

  // put your main code here, to run repeatedly:
  if (myThread.shouldRun())
    myThread.run();

  int level = w.weight / space * 100;

  w.measureKg();
  Serial.print("Present Weight: ");
  Serial.println(w.weight);
  if (printInterval(1000)) {
    lcd.clear();
    lcd.print("Sensor(Kg):");
    lcd.setCursor(12, 0);
    lcd.print(w.weight);
    lcd.setCursor(0, 1);
    lcd.print("Size(Kg): ");
    lcd.setCursor(12, 1);
    lcd.print(space);
    lcd.setCursor(5, 2);
    lcd.print("Gas Level");
    lcd.setCursor(0, 3);
    lcd.print(level);
    lcd.setCursor(3, 3);
    lcd.print("%>");
    int p = ((int)(level / 100 * 15))+1;
    for (int i = 6; i < 6 + p; i++) {
      if (i >= 6) {
        lcd.setCursor(i, 3);
        lcd.write(byte(1));
      }
    }
  }

}

bool printInterval(const unsigned int interval) {
  if (millis() - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = millis();
    return true;
  } else {
    return false;
  }
}

void conMsg() {
  Serial.print(".");
  lcd.clear();
  lcd.print("Connecting to");
  lcd.setCursor(0, 1);
  lcd.print("Mobile Hotspot");
  delay(1000);
}
