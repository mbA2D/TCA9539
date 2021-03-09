#include "Wire.h"
#include <TCA9539.h>

#define ADDRESS 0x74
uint8_t reset_pin = 4;
uint8_t int_pin = 3;
uint8_t pin = 0;

//reset pin, int pin, address
TCA9539 tca1(reset_pin, int_pin, ADDRESS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting TCA9539 Example");
  Wire.begin();
  Wire.setClock(100000);
  
  tca1.TCA9539_init();
  tca1.TCA9539_set_pin_val(pin, LOW);
  tca1.TCA9539_set_dir(pin, TCA9539_PIN_DIR_OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  tca1.TCA9539_set_pin_val(pin, LOW);
  Serial.println(tca1.TCA9539_read_pin_val(pin));
  digitalWrite(13, LOW);
  delay(1000);
  tca1.TCA9539_set_pin_val(pin, HIGH);
  Serial.println(tca1.TCA9539_read_pin_val(pin));
  digitalWrite(13, HIGH);
  delay(1000);

}