/** @file
 *
 * @brief AD562 DAC device driver.
 *
 * Support for output level setting on both channels, power down and software reset
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#include <scriptml/i2c.h>
#include "i2c_regmap.h"
#include "stdio.h"

#define AD5627_BASE_ADDR 0x0C
#define AD5627_REG_SIZE 3
#define AD5627_COMMAND_WRITE_TO_DAC 0x10
#define AD5627_COMMAND_SW_RESET 0x280001
#define AD5627_COMMAND_PWR_UP_DACS 0x200003
#define AD5627_COMMAND_SET_LDAC 0x300003

#define AD5627_DACA_ONLY 0x0
#define AD5627_DACB_ONLY 0x1
#define AD5627_DACA_AND_DACB 0x7

#define AD5627_MAX_INT_VALUE 65535
#define AD5627_MAX_FLOAT_VALUE_3V3_REF 3.3	
#define AD5627_MAX_FLOAT_VALUE_2V5_REF 2.5	
	
/** @brief Set the level of output pins on the DAC
 * The device takes a 24 bit word. {COMMAND, MSB, LSB}
 *
 * @param dev Device handle
 * @param channel Channel number to set: 0 - DAC A; 1 - DAC B; 7 - Both
 * @param level integer containing the 16 bit level
 */
void sml_ad5627_set_level( sml_i2c_regmap_t dev, int channel, int level )
{
    uint8_t reg[AD5627_REG_SIZE];
    
    reg[0] = (uint8_t) AD5627_COMMAND_WRITE_TO_DAC | channel;
    reg[1] = (uint8_t) ( (level & 0xFF00) >> 8 );
    reg[2] = (uint8_t) ( (level & 0xFF) );
    
    sml_i2c_reg_write( dev, reg, AD5627_REG_SIZE );
}

/** @brief Perform a power on software reset
 *
 * @param dev Device handle
 */
void sml_ad5627_reset( sml_i2c_regmap_t dev)
{
    uint8_t reg[AD5627_REG_SIZE];
    
    reg[0] = (uint8_t) ( (AD5627_COMMAND_SW_RESET & 0xFF0000) >> 16 );
    reg[1] = (uint8_t) ( (AD5627_COMMAND_SW_RESET & 0x00FF00) >> 8 );
    reg[2] = (uint8_t) ( (AD5627_COMMAND_SW_RESET & 0x0000FF) );
    
    sml_i2c_reg_write( dev, reg, AD5627_REG_SIZE );
}

/** @brief Power up both DACs and activate buffers
 *
 * @param dev Device handle
 */
void sml_ad5627_power( sml_i2c_regmap_t dev)
{
    uint8_t reg[AD5627_REG_SIZE];
    
    reg[0] = (uint8_t) ( (AD5627_COMMAND_PWR_UP_DACS & 0xFF0000) >> 16 );
    reg[1] = (uint8_t) ( (AD5627_COMMAND_PWR_UP_DACS & 0x00FF00) >> 8 );
    reg[2] = (uint8_t) ( (AD5627_COMMAND_PWR_UP_DACS & 0x0000FF) );
    
    sml_i2c_reg_write( dev, reg, AD5627_REG_SIZE );
}

/** @brief Set LDAC pin as SW driven
 *
 * @param dev Device handle
 */
void sml_ad5627_set_ldac( sml_i2c_regmap_t dev)
{
    uint8_t reg[AD5627_REG_SIZE];
    
    reg[0] = (uint8_t) ( (AD5627_COMMAND_SET_LDAC & 0xFF0000) >> 16 );
    reg[1] = (uint8_t) ( (AD5627_COMMAND_SET_LDAC & 0x00FF00) >> 8 );
    reg[2] = (uint8_t) ( (AD5627_COMMAND_SET_LDAC & 0x0000FF) );
    
    sml_i2c_reg_write( dev, reg, AD5627_REG_SIZE );
}

/** @brief Initialise the AD5627 to standard start conditions using a SW 
 * triggered conversion
 *
 * @param dev Device handle
 */
void sml_ad5627_sw_init( sml_i2c_regmap_t dev)
{
    /* Software reset */       
    sml_ad5627_reset( dev);

    /* Power up DACs */    
    sml_ad5627_power(dev);
    
    /* Set LDAC register to indicate software conversion trigger */   
    sml_ad5627_set_ldac(dev);
}
