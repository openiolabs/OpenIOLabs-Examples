/** @file
 *
 * @brief 24LC64 EEPROM device driver.
 *
 * Read and write support
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#include <scriptml/i2c.h>
#include <stdint.h>

#define BASE_ADDR 0x50

// Driver flags for this device:     { "24c64",      AT24_DEVICE_MAGIC(65536 / 8,    AT24_FLAG_ADDR16) },

typedef struct
{
	sml_i2c_t *piic;
	int addr;
} sml_24lc64_t;


/** @brief Create device driver instance
 *
 * @param i2c An instance of the I2C driver for the bus on which the device is placed
 * @param addr_offset The address offset, corresponding to the value on the Ax pins, 0 through 7 inclusive
 * @return Device handle
 */
sml_24lc64_t sml_24lc64_create( sml_i2c_t i2c, int addr_offset )
{
	sml_24lc64_t dev;
	dev.piic = &i2c;
	dev.addr = BASE_ADDR | addr_offset;
	return dev;
}
	

/** @brief Write to EEPROM
 *
 * @param dev Device handle
 * @param buf Buffer of data to write
 * @param offset Start address in EEPROM; 0 through 8191
 * @param count Number of bytes to write up to 32
 */
void sml_24lc64_write( sml_24lc64_t dev, const uint8_t *buf,
                       unsigned int offset, size_t count )	
{
	struct i2c_msg msg[2];	
	uint8_t msgbuf[2];

    msgbuf[0] = offset >> 8; 
    msgbuf[1] = offset;
    msg[0].addr = dev.addr;
    msg[0].flags = 0;
    msg[0].buf = msgbuf;
    msg[0].len = 2;

    msg[1].addr = dev.addr;
    msg[1].flags = 0;
    msg[1].buf = buf;
    msg[1].len = count;
 
    sml_i2c_transfer(*(dev.piic), msg, 2);
}


/** @brief Read from EEPROM
 *
 * @param dev Device handle
 * @param buf Buffer of data for read
 * @param offset Start address in EEPROM; 0 through 8191
 * @param count Number of bytes to read up to 32
 */
void sml_24lc64_read( sml_24lc64_t dev, uint8_t *buf,
                      unsigned int offset, size_t count )	
{
	struct i2c_msg msg[2];	
	uint8_t msgbuf[2];
	
    msgbuf[0] = offset >> 8;
    msgbuf[1] = offset;
    msg[0].addr = dev.addr;
    msg[0].flags = 0;
    msg[0].buf = msgbuf;
    msg[0].len = 2;
 
    msg[1].addr = dev.addr;
    msg[1].flags = I2C_M_RD;
    msg[1].buf = buf;
    msg[1].len = count;
  
    sml_i2c_transfer(*(dev.piic), msg, 2);
}
