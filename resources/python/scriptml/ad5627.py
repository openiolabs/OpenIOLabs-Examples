## @file
#  @package ad5627
# 
#  @brief Dual channel 16 bit DAC
# 
#  The ADI AD5627 dual channel DAC with 16 bits resolution, accessed via the I2C interface.
#  
#  
#  Copyright (c) Open IO Labs Ltd 2017
#  All Rights Reserved
# 

from i2c_regmap import *


BASE_ADDR = 0x0C

# Register values for certain operations
COMMAND_WRITE_TO_DAC_REG = 0x10
COMMAND_SW_RESET = 0x280001
COMMAND_SW_RESET_REG = 0x28
COMMAND_SW_RESET_VAL = 0x0001
COMMAND_PWR_UP_DACS_REG = 0x20
COMMAND_PWR_UP_DACS_VAL = 0x0003
COMMAND_SET_LDAC_REG = 0x30
COMMAND_SET_LDAC_VAL = 0x0003


DACA_ONLY = 0x0
DACB_ONLY = 0x1
DACA_AND_DACB = 0x7

# These values are included for the OpenIO Labs DB4 development board
# where we have an option to run the DAC and ADC from either a 2.5V or 3.3V reference
MAX_INT_VALUE = 65535
MAX_FLOAT_VALUE_3V3_REF = 3.3	
MAX_FLOAT_VALUE_2V5_REF = 2.5	

class device:
    ##
    #  @brief Create device driver instance
    # 
    #  @param i2c An instance of the I2C driver for the bus on which the device is placed
    #  @return Device handle
    # 
    def __init__( self, i2c ):
        self.iic = i2c_regmap( i2c, BASE_ADDR, 0x100, False )
        
    ## 
    #  @brief Set the level of output pins on the DAC
    #  The device takes a 24 bit word. {COMMAND, MSB, LSB}
    #  
    #  @param channel Channel number to set: 0 - DAC A; 1 - DAC B; 7 - Both
    #  @param level integer containing the 16 bit level
    #
    def set_level( self, channel, level ):
        reg = COMMAND_WRITE_TO_DAC_REG | channel      
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((level >> 8) & 0xFF)
        _bytes[1] = uint8(level & 0xFF)
        self.iic.write( _bytes, reg, 2 )
        

    ## 
    #  @brief Set LDAC pin as SW driven
    #  
    def set_ldac( self):
        reg = COMMAND_SET_LDAC_REG      
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((COMMAND_SET_LDAC_VAL >> 8) & 0xFF)
        _bytes[1] = uint8(COMMAND_SET_LDAC_VAL & 0xFF)
        self.iic.write( _bytes, reg, 2 )
    
    ## 
    #  @brief Power up DACs
    #  
    def power_up( self):
        reg = COMMAND_PWR_UP_DACS_REG      
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((COMMAND_PWR_UP_DACS_VAL >> 8) & 0xFF)
        _bytes[1] = uint8(COMMAND_PWR_UP_DACS_VAL & 0xFF)
        self.iic.write( _bytes, reg, 2 )
        
    
    ## 
    #  @brief Software reset of DAC
    #  
    def sw_reset( self):
        reg = COMMAND_SW_RESET_REG      
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((COMMAND_SW_RESET_VAL >> 8) & 0xFF)
        _bytes[1] = uint8(COMMAND_SW_RESET_VAL & 0xFF)
        self.iic.write( _bytes, reg, 2 )
    
    
