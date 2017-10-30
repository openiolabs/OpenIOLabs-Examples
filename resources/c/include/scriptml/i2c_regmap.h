/** @file
 *
 * @brief Sub-driver for I2C devices organised as regmaps.
 *
 * Where an I2C device implements a "regular" regmap, a sml_i2c_regmap_t
 * instance may be created to permit access using straightforward read
 * and write operations, simplifying device driver implementation. 
 * 
 * The device must accept writes of the form 
 * START <device addr+W bit> <register> <bytes...> STOP
 * 
 * and reads of the form
 * START <device addr+W bit> <register> START <device addr+R bit> <bytes...> STOP
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#include <scriptml/i2c.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef TRACE_I2C_REGMAP
#include <stdio.h>
#endif

typedef struct
{
	sml_i2c_t *piic;
	int addr;
    int size;
    int smbus_api;
} sml_i2c_regmap_t;


/** @brief Create device driver instance
 *
 * Note that the I2C/SMBUS API can only be used with devices that auto-increment
 * the register number on multi-byte operations.
 * 
 * @param i2c An instance of the I2C driver for the bus on which the device is placed
 * @param addr Address of the I2C device on the bus
 * @param size Number of registers in the regmap (just for a check)
 * @param smbus_api 0 for plain I2C; 1 for I2C/SMBUS. 
 * @return Device handle
 */
sml_i2c_regmap_t sml_i2c_regmap_create( sml_i2c_t i2c, int addr, int size, int smbus_api )
{
	sml_i2c_regmap_t dev;
	dev.piic = &i2c;
	dev.addr = addr;
	dev.size = size;
    dev.smbus_api = smbus_api;
	return dev;
}
	

/** @brief Write to I2C device registers
 * 
 * @param dev Device handle
 * @param buf Buffer of data to write
 * @param reg Number of first register to write
 * @param count Number of bytes to write
 *
 * If count is greater than one, multiple bytes are written stating at reg.
 * Count must be at least one byte and the write operation must not go past the
 * end of the register map. Note that it is dependent on the device whether
 * a multiple write goes to sucessive registers.
 */
void sml_i2c_regmap_write( sml_i2c_regmap_t dev, const uint8_t *buf,
                           uint8_t reg, size_t count )	
{
    assert( count >= 1 );
    assert( reg < dev.size );

#ifdef TRACE_I2C_REGMAP
    printf("I2C at 0x%x regmap at 0x%x write", dev.addr, reg);
    int i;
    for( i=0; i<(int)count; i++ )
        printf(" 0x%x", buf[i] );
    printf("\n");
#endif

    if( dev.smbus_api )
    {
        sml_i2c_smbus_set_addr( *(dev.piic), dev.addr );
        int i;
        for( i=0; i<count; i++ )
            sml_i2c_smbus_write_byte_data( *(dev.piic), reg+i, buf[i] );
    }
    else
    {
        uint8_t *wbuf = (uint8_t *)malloc( count+1 );
        wbuf[0] = (uint8_t)reg;
        memcpy( wbuf+1, buf, count );
        
        struct i2c_msg msg[1];	

        msg[0].addr = dev.addr;
        msg[0].flags = 0; // Write
        msg[0].buf = wbuf;
        msg[0].len = count + 1; // Account for the register byte
     
        sml_i2c_transfer(*(dev.piic), msg, 1);
    }
}


/** @brief Read from I2C device registers
 *
 * @param dev Device handle
 * @param buf Buffer of data for read
 * @param reg Number of first register to read
 * @param count Number of bytes to read
 *
 * If count is greater than one, multiple bytes are read stating at reg.
 * Count must be at least one byte and the write operation must not go past the
 * end of the register map. Note that it is dependent on the device whether
 * a multiple read reads sucessive registers.
 */
void sml_i2c_regmap_read( sml_i2c_regmap_t dev, uint8_t *buf,
                          uint8_t reg, size_t count )	
{
    assert( count >= 1 );
    assert( reg < dev.size );

    if( dev.smbus_api )
    {
        sml_i2c_smbus_set_addr( *(dev.piic), dev.addr );
        int i;
        for( i=0; i<count; i++ )
            buf[i] = sml_i2c_smbus_read_byte_data( *(dev.piic), reg+i );     
    }
    else
    {
        struct i2c_msg msg[2];	
        
        msg[0].addr = dev.addr;
        msg[0].flags = 0; // Write
        msg[0].buf = &reg;
        msg[0].len = 1;
        msg[1].addr = dev.addr;
        msg[1].flags = I2C_M_RD; // Read
        msg[1].buf = buf;
        msg[1].len = count;
      
        sml_i2c_transfer(*(dev.piic), msg, 2);
    }
    
#ifdef TRACE_I2C_REGMAP
    printf("I2C at 0x%x regmap at 0x%x read", dev.addr, reg);
    int i;
    for( i=0; i<(int)count; i++ )
        printf(" 0x%x", buf[i] );
    printf("\n");
#endif
}

/** @brief Convert an integer into a defined bumber of bytes.
 *
 * @param input_int Input integer to convert
 * @param num_bytes Number of bytes to extract from the integer
 * @return A byte array with num_bytes elements
 * @param count Number of bytes to read
 *
 * The endian-ness of this operations is as follows;
 * The MSB is returned in the lowest index [0] and 
 * the LSB in the highest index [num_bytes - 1]
 */
uint8_t * int_to_byte(int * input_int, int num_bytes){
    int i;
    uint8_t * ret_bytes = malloc(num_bytes * 8);
    
    for (i = 0; i < num_bytes; i++){
        ret_bytes[i] = (* input_int) >> (((num_bytes-1)-i) * 8);
	} 
    
    return ret_bytes;
}
	
/** @brief Write long to I2C device registers for register addresses greater than one byte
 * 
 * @param dev Device handle
 * @param buf Buffer of data to write
 * @param reg Number of first register to write
 * @param reg_addr_size Register address size in bytes, maximum is 4 bytes
 * @param count Number of bytes to write
 *
 * If count is greater than one, contiguous registers are written stating at reg.
 * Count must be at least one byte and the write operation must not go past the
 * end of the register map.
 */
void sml_i2c_regmap_writeL( sml_i2c_regmap_t dev, const uint8_t *buf,
                           int *reg, int reg_addr_size, size_t count )	
{
    assert( count >= 1 );
    assert( *reg + count <= dev.size );

#ifdef TRACE_I2C_REGMAP
    int i;
    for( i=0; i<(int)count; i++ )
        printf(" 0x%x", buf[i] );
    printf("\n");
#endif
    int i;
    uint8_t *wbuf = (uint8_t *)malloc( count + reg_addr_size );
    uint8_t *raddr = (uint8_t *)malloc( reg_addr_size );
    raddr = int_to_byte(reg, reg_addr_size);
    
    for (i = 0; i < reg_addr_size; i++){
        wbuf[i]  = raddr[i];
    }
   
    memcpy( wbuf+reg_addr_size, buf, count );
    
	struct i2c_msg msg[1];	

    msg[0].addr = (dev.addr);
    msg[0].flags = 0; // Write
    msg[0].buf = wbuf;
    msg[0].len = count;

    sml_i2c_transfer(*(dev.piic), msg, 1);
}

/** @brief Simple write of a number of bytes to a single address (0x00)
 * 
 * @param dev Device handle
 * @param buf Buffer of data to write
 * @param count Number of bytes to write
 *
 * If count is greater than one, contiguous registers are written stating at reg.
 * Count must be at least one byte and the write operation must not go past the
 * end of the register map.
 */
 void sml_i2c_reg_write( sml_i2c_regmap_t dev, const uint8_t *buf, size_t count )	
{   
	struct i2c_msg msg[1];	
    
    msg[0].addr = (dev.addr);   
    msg[0].flags = 0; // Write
    msg[0].buf = buf;
    msg[0].len = count;

    sml_i2c_transfer(*(dev.piic), msg, 1);
}


/** @brief Read long from I2C device registers for register addresses greater than one byte
 *
 * @param dev Device handle
 * @param buf Buffer of data for read
 * @param reg Number of first register to read
 * @param count Number of bytes to read
 *
 * If count is greater than one, contiguous registers are written stating at reg.
 * Count must be at least one byte and the write operation must not go past the
 * end of the register map.
 */
void sml_i2c_regmap_readL( sml_i2c_regmap_t dev, uint8_t *buf,
                          int *reg, int reg_addr_size, size_t count )	
{
    assert( count >= 1 );
    assert( *reg + count <= dev.size );

    struct i2c_msg msg[2];	
    uint8_t *raddr = (uint8_t *)malloc( reg_addr_size );
   
    raddr = int_to_byte(reg, reg_addr_size);
	
    msg[0].addr = (dev.addr);
    msg[0].flags = 0; // Write
    msg[0].buf = raddr;
    msg[0].len = reg_addr_size;
    
    
    msg[1].addr = (dev.addr);
    msg[1].flags = I2C_M_RD; // Read
    msg[1].buf = buf;
    msg[1].len = count;
  
    sml_i2c_transfer(*(dev.piic), msg, 2);

#ifdef TRACE_I2C_REGMAP
    int i;
    for( i=0; i<(int)count; i++ )
        printf(" 0x%x", buf[i] );
    printf("\n");
#endif
}



