## @file
#
# @brief Support for I2C devices organised as regmaps.
#
# Where an I2C device implements a "regular" regmap, a sml_i2c_regmap_t
# instance may be created to permit access using straightforward read
# and write operations, simplifying device driver implementation. 
# 
# The device must accept writes of the form 
# START <device addr+W bit> <register> <bytes...> STOP
# 
# and reads of the form
# START <device addr+W bit> <register> START <device addr+R bit> <bytes...> STOP
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

import i2c
from numpy import *

class i2c_regmap:
    ## @brief Create device driver instance
    #
    # @param i2c An instance of the I2C driver for the bus on which the device is placed
    # @param addr Address of the I2C device on the bus
    # @param size Number of registers in the regmap (just for a check)
    # @return Device handle
    #
    def __init__( self, i2c, addr, size=256, smbus_api=False ):
        self.iic = i2c
        self.addr = addr
        self.size = size
        self.smbus_api = smbus_api
	

    ## @brief Write to I2C device registers
    # 
    # @param self Device handle
    # @param buf Buffer of data to write
    # @param reg Number of first register to write
    # @param count Number of bytes to write
    #
    # If count is greater than one, multiple bytes are written stating at reg.
    # Count must be at least one byte and the write operation must not go past the
    # end of the register map. Note that it is dependent on the device whether
    # a multiple write goes to sucessive registers.
    #
    def write( self, buf, reg, count=1 ):
        assert count >= 1 
        assert reg < self.size 
        if self.smbus_api:        
            self.iic.smbus_set_addr( self.addr )
            for i in range(count):
                self.iic.smbus_write_byte_data( reg+i, buf[i] )
        else:            
            msg = self.iic.msg( self.addr, 0, [uint8(reg)] + buf )            
            self.iic.transfer([msg])


    ## @brief Read from I2C device registers
    #
    # @param self Device handle
    # @param buf Buffer of data for read
    # @param reg Number of first register to read
    # @param count Number of bytes to read
    #
    # If count is greater than one, multiple bytes are read stating at reg.
    # Count must be at least one byte and the read operation must not go past the
    # end of the register map. Note that it is dependent on the device whether
    # a multiple read reads sucessive registers.
    #
    def read( self, reg, count=1 ):    
        assert count >= 1 
        assert reg < self.size 
        
        buf = []
        for i in range(count):
            buf = buf + [uint8()]

        if self.smbus_api:        
            self.iic.smbus_set_addr( self.addr )
            for i in range(count):
                buf[i] = self.iic.smbus_read_byte_data( reg+i );      
        else:                        
            msgs = [self.iic.msg( self.addr, 0, [uint8(reg)] ), 
                    self.iic.msg( self.addr, i2c.I2C_M_RD, buf )];	            
            self.iic.transfer(msgs)    
        
        return buf
