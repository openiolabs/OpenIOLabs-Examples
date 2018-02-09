## @file
#  @package isl29023
# 
#  @brief ISL29023 device driver
# 
#  Detects the level of visible light or infra-red.
#  =========================
#  
#  Program the two `command` registers and then read back from the `data` register.
#  
#  
#  Auto-generated 09 February 2018; do not edit
#  
#  Copyright (c) Open IO Labs Ltd 2017
#  All Rights Reserved
# 

from i2c_regmap import *
from gpio import *

BASE_ADDR = 0x44

COMMAND_1_MODE_IR_ONCE = 0x2
COMMAND_1_MODE_IR_CONTINUOUS = 0x6
COMMAND_1_MODE_ALS_CONTINUOUS = 0x5
COMMAND_1_MODE_POWER_DOWN = 0x0
COMMAND_1_MODE_ALS_INTEGRATION_CYCLE = 0x1
COMMAND_1_PERSIST_1_CYCLE = 0x0
COMMAND_1_PERSIST_8_CYCLES = 0x2
COMMAND_1_PERSIST_16_CYCLES = 0x3
COMMAND_1_PERSIST_4_CYCLES = 0x1

COMMAND_2_RESOLUTION_4_BIT = 0x3
COMMAND_2_RESOLUTION_12_BIT = 0x1
COMMAND_2_RESOLUTION_8_BIT = 0x2
COMMAND_2_RESOLUTION_16_BIT = 0x0
COMMAND_2_RANGE_16000_LUX = 0x2
COMMAND_2_RANGE_64000_LUX = 0x3
COMMAND_2_RANGE_1000_LUX = 0x0
COMMAND_2_RANGE_4000_LUX = 0x1

class device:
    ##
    #  @brief Create device driver instance
    # 
    #  @param i2c An instance of the I2C driver for the bus on which the device is placed
    #  @param intr_pin An instance of the GPIO driver for the pin connected to the interrupt line
    #  @return Device handle
    # 
    def __init__( self, i2c, intr_pin ):
        self.intr_gpio = intr_pin
        self.iic = i2c_regmap( i2c, BASE_ADDR, 0x100, True )

    ##
    #  @brief Set the device's operation mode
    # 
    #  @param mode operation mode
    #  @param persist interrupt persistance mode
    # 
    def set_command_1( self, mode, persist ):
        _value = uint8(((mode & 0x7) << 5) | (persist & 0x3))
        self.iic.write( [_value], 0x0, 1 )

    ##
    #  @brief Set the device's resolution and range
    # 
    #  @param resolution ADC resolution
    #  @param range full scale range
    # 
    def set_command_2( self, resolution, range ):
        _value = uint8(((resolution & 0x3) << 2) | (range & 0x3))
        self.iic.write( [_value], 0x1, 1 )

    ##
    #  @brief Get data registers
    # 
    #  @return data registers
    # 
    def get_data( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x2, 2 )
        return uint16(_bytes[0] | (_bytes[1] << 8))

    ##
    #  @brief Set lower interrupt threshold
    # 
    #  @param int_lt lower interrupt threshold
    # 
    def set_int_lt( self, int_lt ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8(int_lt & 0xff)
        _bytes[1] = uint8((int_lt >> 8) & 0xff)
        self.iic.write( _bytes, 0x4, 2 )

    ##
    #  @brief Set upper interrupt threshold
    # 
    #  @param int_ht upper interrupt threshold
    # 
    def set_int_ht( self, int_ht ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8(int_ht & 0xff)
        _bytes[1] = uint8((int_ht >> 8) & 0xff)
        self.iic.write( _bytes, 0x6, 2 )

