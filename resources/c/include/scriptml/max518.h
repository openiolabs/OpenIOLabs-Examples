/** @file
 *
 * @brief MAX518 DAC device driver.
 *
 * Support for output level setting on both channels, power down and reset
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#include <scriptml/i2c.h>

#define BASE_ADDR 0x2C

typedef struct
{
	sml_i2c_t *piic;
	int addr;
} sml_max518_t;


/** @brief Create device driver instance
 *
 * @param i2c An instance of the I2C driver for the bus on which the device is placed
 * @param addr_offset The I2C address offset, corresponding to the value on the Ax pins, 0 through 3 inclusive
 * @return Device handle
 */
sml_max518_t sml_max518_create( sml_i2c_t i2c, int addr_offset )
{
	sml_max518_t dev;
	dev.piic = &i2c;
	dev.addr = BASE_ADDR | addr_offset;
	return dev;
}
	
	
/** @brief Set the level of output pins on the IO expander
 *
 * @param dev Device handle
 * @param channel Channel number to set; 0 or 1
 * @param level A byte containing the level; 0 through 255 inclusive
 */
void sml_max518_set_level( sml_max518_t dev, int channel, int level )
{
	struct i2c_msg msg;
	msg.addr = dev.addr;
	msg.flags = 0;
	char b[2];
	msg.buf = b;
	int i=0;
    msg.buf[i++] = channel; 
    msg.buf[i++] = level;
    msg.len = i;
    sml_i2c_transfer(*(dev.piic), &msg, 1);
}


/** @brief Set power status
 *
 * @param dev Device handle
 * @param power Power status; 0 for off, 1 for on
 *
 * Note: device is intially powered on
 */
void sml_max518_power( sml_max518_t dev, int power )
{
	struct i2c_msg msg;
	msg.addr = dev.addr;
	msg.flags = 0;
	char b[2];
	msg.buf = b;
	int i=0;
    msg.buf[i++] = power ? 0x0 : 0x8; 
    msg.len = i;
    sml_i2c_transfer(*(dev.piic), &msg, 1);
}


/** @brief Reset device
 *
 * @param dev Device handle
 *
 * Device is reset as described in the data sheet
 */
void sml_max518_reset( sml_max518_t dev )
{
	struct i2c_msg msg;
	msg.addr = dev.addr;
	msg.flags = 0;
	char b[2];
	msg.buf = b;
	int i=0;
    msg.buf[i++] = 0x10; 
    msg.len = i;
    sml_i2c_transfer(*(dev.piic), &msg, 1);
}
