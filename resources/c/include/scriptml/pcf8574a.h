/** @file
 *
 * @brief pcf8574a IO extender device driver.
 *
 * Read and write support
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#include <scriptml/i2c.h>
#include <stdint.h>

#define BASE_ADDR 0x38

// Driver flags for this device:     { "PCF8574A",      GPIO Extender },

typedef struct
{
	sml_i2c_t *piic;
	int addr;
} sml_pcf8574a_t;


/** @brief Create device driver instance
 *
 * @param i2c An instance of the I2C driver for the bus on which the device is placed
 * @param addr_offset - not used for the IO expander. This was taken from the EEPROM code
 * @return Device handle
 */
sml_pcf8574a_t sml_pcf8574a_create( sml_i2c_t i2c, int addr_offset )
{
	sml_pcf8574a_t dev;
	dev.piic = &i2c;
	dev.addr = BASE_ADDR | addr_offset;
	return dev;
}
	

/** @brief Write to PCF8574A IO Expander
 *
 * @param dev Device handle
 * @param buf Buffer of data to write
 * @param offset - Not used set to 0
 * @param count - set to 1 for IO expander
 */
void sml_pcf8574a_write( sml_pcf8574a_t dev, const uint8_t *buf,
                       unsigned int offset, size_t count )	
{
	struct i2c_msg msg[1];	

    msg[0].addr = dev.addr;
    msg[0].flags = 0;
    msg[0].buf = buf;
    msg[0].len = count;
 
    sml_i2c_transfer(*(dev.piic), msg, 1);
}


/** @brief Read from PCF8574A IO Expander
 *
 * @param dev Device handle
 * @param buf Buffer of data for read
 * @param offset - Not used set to 0
 * @param count  - set to 1 for IO expander
 */
void sml_pcf8574a_read( sml_pcf8574a_t dev, uint8_t *buf,
                      unsigned int offset, size_t count )	
{
	struct i2c_msg msg[1];	
	
    msg[0].addr = dev.addr;
    msg[0].flags = I2C_M_RD;
    msg[0].buf = buf;
    msg[0].len = count;
  
    sml_i2c_transfer(*(dev.piic), msg, 1);
}
