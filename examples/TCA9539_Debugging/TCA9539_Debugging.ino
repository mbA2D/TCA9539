/*
AUTHOR: Micah Black, A2D Electronics
DATE: Jan 21, 2021
NOTE:
This is code that I used while debugging the library
It toggles output 0 of the IC and reads it back over Serial
Make all the private functions in TCA9539.h file public to run this
*/

#include "Wire.h"
#include <TCA9539.h>

#define ADDRESS 0x74
uint8_t reset_pin = 4;
uint8_t int_pin = 3;

//reset pin, int pin, address
TCA9539 tca1(reset_pin, int_pin, ADDRESS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting TCA9539 Example");
  Wire.begin();
  Wire.setClock(100000);
  
  tca1.TCA9539_init();
  
  Serial.println("Reset to Defaults - config reg all 1");
  Serial.print("Config Reg Arduino: ");
  Serial.print(tca1._config.word);
  tca1._TCA9539_read_reg(TCA9539_CONFIG_ADDR, &(tca1._config));
  Serial.print("\t Config Reg TCA: ");
  Serial.println(tca1._config.word);
  
  
  tca1.TCA9539_set_pin_val(0, LOW);
  tca1.TCA9539_set_direction(0, TCA9539_PIN_DIR_OUTPUT);
  Serial.println("Cleared bit 0 of config reg");
  
  
  Serial.print("Config Reg: ");
  Serial.print(tca1._config.word);
  tca1._TCA9539_read_reg(TCA9539_CONFIG_ADDR, &(tca1._config));
  Serial.print("\t Config Reg TCA: ");
  Serial.println(tca1._config.word);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  tca1.TCA9539_set_pin_val(0, LOW);
  delay(100);
  tca1._TCA9539_read_reg(TCA9539_OUTPUT_ADDR, &(tca1._output));
  tca1._TCA9539_read_reg(TCA9539_INPUT_ADDR, &(tca1._input));
  Serial.print("Input Reg: ");
  Serial.print(tca1._input.word);
  Serial.print("\t Output Reg: ");
  Serial.println(tca1._output.word);
  digitalWrite(13, LOW);
  delay(2000);
  
  tca1.TCA9539_set_pin_val(0, HIGH);
  delay(100);
  tca1._TCA9539_read_reg(TCA9539_OUTPUT_ADDR, &(tca1._output));
  tca1._TCA9539_read_reg(TCA9539_INPUT_ADDR, &(tca1._input));
  Serial.print("Input Reg: ");
  Serial.print(tca1._input.word);
  Serial.print("\t Output Reg: ");
  Serial.println(tca1._output.word);
  digitalWrite(13, HIGH);
  delay(2000);

}