//Arduino Library for TCA9539
//16 bit port expander

#include "Arduino.h"
#include <TCA9539.h>

TCA9539::TCA9539(uint8_t reset_pin, uint8_t int_pin, uint8_t address)
{
	//setup pins and addresses
	_reset_pin = reset_pin;
	_int_pin = int_pin;
	_addr = address;
	
}

void TCA9539::_set_reg_defaults()
{
	_input.word = 0;
	_output.word = 0xffff;
	_pol_inv.word = 0;
	_config.word = 0xffff;
}

void TCA9539::TCA9539_init()
{
	//reset the device to initial register defaults
	//requires minimum 6ns pulse on reset which the digitalWrite
	//timing would satisfy but an extra delay to be safe
	pinMode(_reset_pin, OUTPUT);
	digitalWrite(_reset_pin, LOW);
	delayMicroseconds(1);
	digitalWrite(_reset_pin, HIGH);
	
	//TODO - attach interrupt for inputs
	pinMode(_int_pin, INPUT);
	
	//setup registers to default values
	_set_reg_defaults();
}

void TCA9539::_TCA9539_set_bit(TCA9539_register* reg, uint8_t bit, bool value)
{
	if(!_valid_pin(bit)) return;
	if(value) reg->word |= 1 << bit; //set bit
	else reg->word &= ~(1 << bit); //clear bit
}

bool TCA9539::_TCA9539_get_bit(TCA9539_register* reg, uint8_t bit)
{
	if(!_valid_pin(bit)) return false;
	return (reg->word >> bit) & 1;
}

void TCA9539::TCA9539_set_dir(uint8_t pin, TCA9539_pin_dir_t dir)
{
	if(!_valid_pin(pin)) return;
	
	_TCA9539_set_bit(&_config, pin, dir);
	
	Wire.beginTransmission(_addr);
	Wire.write(TCA9539_CONFIG_ADDR);
	Wire.write(_config.low);
	Wire.write(_config.high);
	Wire.endTransmission();
}

void TCA9539::TCA9539_set_pol_inv(uint8_t pin, TCA9539_pol_inv_t inv)
{
	if(!_valid_pin(pin)) return;
	
	_TCA9539_set_bit(&_pol_inv, pin, inv);
	
	Wire.beginTransmission(_addr);
	Wire.write(TCA9539_POL_INV_ADDR);
	Wire.write(_pol_inv.low);
	Wire.write(_pol_inv.high);
	Wire.endTransmission();
}

void TCA9539::TCA9539_set_pin_val(uint8_t pin, TCA9539_pin_val_t val)
{
	if(!_valid_pin(pin)) return;
	
	_TCA9539_set_bit(&_output, pin, val);
	
	Wire.beginTransmission(_addr);
	Wire.write(TCA9539_OUTPUT_ADDR);
	Wire.write(_output.low);
	Wire.write(_output.high);
	Wire.endTransmission();
}

bool TCA9539::TCA9539_read_pin_val(uint8_t pin)
{
	if(!_valid_pin(pin)) return false;
	
	_TCA9539_read_reg(TCA9539_INPUT_ADDR, &_input);
	return _TCA9539_get_bit(&_input, pin);
}

bool TCA9539::TCA9539_check_pin_dir(uint8_t pin, TCA9539_pin_dir_t dir)
{
	if(!_valid_pin(pin)) return false;
	return (dir == (_config.word >> pin & 1));
}

void TCA9539::_TCA9539_read_reg(uint8_t reg_addr, _TCA9539_register* reg_memory)
{
	if(reg_addr > TCA9539_CONFIG_ADDR) return;
	
	Wire.beginTransmission(_addr);
	Wire.write(reg_addr);
	Wire.endTransmission();
	Wire.requestFrom(_addr, 2);
	reg_memory->low = Wire.read();
	reg_memory->high = Wire.read();
}

bool TCA9539::_valid_pin(uint8_t pin)
{
	return (pin < TCA9539_REG_SIZE);
}
