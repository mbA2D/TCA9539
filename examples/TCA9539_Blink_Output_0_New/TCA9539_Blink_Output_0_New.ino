#include "Wire.h"
#include <TCA9539.h>

TwoWire Wire2(PB9, PB8);

#define ADDRESS 0x77
//uint8_t reset_pin = 4;
//uint8_t int_pin = 3;
uint8_t pin = 0;

//reset pin, int pin, address
TCA9539 tca1(ADDRESS, &Wire2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting TCA9539 Example");
  //Wire2.begin();
  //Wire2.setClock(100000);
  
  tca1.TCA9539_init();
  tca1.TCA9539_set_pin_val(pin, TCA9539_PIN_OUT_LOW);
  tca1.TCA9539_set_dir(pin, TCA9539_PIN_DIR_OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  tca1.TCA9539_set_pin_val(pin, TCA9539_PIN_OUT_LOW);
  Serial.println(tca1.TCA9539_read_pin_val(pin));
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  tca1.TCA9539_set_pin_val(pin, TCA9539_PIN_OUT_HIGH);
  Serial.println(tca1.TCA9539_read_pin_val(pin));
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

}
