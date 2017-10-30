/** @file
 *
 * @brief AD7991 8 bit Analogue to Digital Converter (ADC)
 *
 * Read Write support.
 * The write is used to configure the ADC operational modes only
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#include <scriptml/i2c.h>
#include <stdint.h>

#define BASE_ADDR 0x28 // Note, this is the address for the AD7991-0 there are other devices in the family with different addresses

// Driver flags for this device:     { "AD7991",      ADC },

typedef struct
{
	sml_i2c_t *piic;
	int addr;
} sml_ad7991_t;


/** @brief Create device driver instance
 *
 * @param i2c An instance of the I2C driver for the bus on which the device is placed
 * @param addr_offset - not used for the ADC. This was taken from the EEPROM code
 * @return Device handle
 */
sml_ad7991_t sml_ad7991_create( sml_i2c_t i2c, int addr_offset )
{
	sml_ad7991_t dev;
	dev.piic = &i2c;
	dev.addr = BASE_ADDR | addr_offset;
	return dev;
}
	

/** @brief Write to AD7991 ADC
 *
 * @param dev Device handle
 * @param buf Buffer of data to write
 * @param offset - Not used set to 0
 * @param count  - Number of bytes to write
 */
void sml_ad7991_write( sml_ad7991_t dev, const uint8_t *buf,
                       unsigned int offset, size_t count )	
{
	struct i2c_msg msg[1];	

    msg[0].addr = dev.addr;
    msg[0].flags = 0;
    msg[0].buf = buf;
    msg[0].len = count;
 
    sml_i2c_transfer(*(dev.piic), msg, 1);
}


/** @brief Read from AD7991 ADC
 *
 * @param dev Device handle
 * @param buf Buffer of data for read
 * @param offset - Not used set to 0
 * @param count   - Number of bytes to read
 */
void sml_ad7991_read( sml_ad7991_t dev, uint8_t *buf,
                      unsigned int offset, size_t count )	
{
	struct i2c_msg msg[1];	
	
    msg[0].addr = dev.addr;
    msg[0].flags = I2C_M_RD;
    msg[0].buf = buf;
    msg[0].len = count;
  
    sml_i2c_transfer(*(dev.piic), msg, 1);
}
