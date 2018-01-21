## @file
#  @package lm75b
# 
#  @brief LM75B device driver
# 
#  LM75B Digital Thermometer 
#  =========================
#  
#  Program the the `conf` register then read the `temp` register
#  
#  Auto-generated 21 January 2018; do not edit
#  
#  Copyright (c) Open IO Labs Ltd 2017
#  All Rights Reserved
# 

from i2c_regmap import *
from gpio import *

BASE_ADDR = 0x48

CONF_SHUTDOWN_SHUTDOWN = 0x1
CONF_SHUTDOWN_NORMAL = 0x0
CONF_OS_COMP_INT_INTERRUPT = 0x1
CONF_OS_COMP_INT_COMPARATOR = 0x0
CONF_OS_POL_ACTIVE_HIGH = 0x1
CONF_OS_POL_ACTIVE_LOW = 0x0
CONF_OS_F_QUE_1 = 0x0
CONF_OS_F_QUE_2 = 0x1
CONF_OS_F_QUE_4 = 0x2
CONF_OS_F_QUE_6 = 0x3

class device:
    ##
    #  @brief Create device driver instance
    # 
    #  @param i2c An instance of the I2C driver for the bus on which the device is placed
    #  @param addr_offset The I2C address offset
    #  @param intr_pin An instance of the GPIO driver for the pin connected to the interrupt line
    #  @return Device handle
    # 
    def __init__( self, i2c, addr_offset, intr_pin ):
        self.intr_gpio = intr_pin
        self.iic = i2c_regmap( i2c, BASE_ADDR + addr_offset, 0x100, False )

    ##
    #  @brief Set configuration
    # 
    #  @param shutdown device operation mode
    #  @param os_comp_int OS operation mode
    #  @param os_pol OS polarity selection
    #  @param os_f_que OS fault queue programming
    # 
    def set_conf( self, shutdown, os_comp_int, os_pol, os_f_que ):
        _value = uint8((shutdown & 0x1) | ((os_comp_int & 0x1) << 1) | ((os_pol & 0x1) << 2) | ((os_f_que & 0x3) << 3))
        self.iic.write( [_value], 0x1, 1 )

    ##
    #  @brief Get temperature
    # 
    #  @return temperature
    # 
    def get_temp( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x0, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set overtemperature shutdown threshold
    # 
    #  @param tos overtemperature shutdown threshold
    # 
    def set_tos( self, tos ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((tos >> 8) & 0xff)
        _bytes[1] = uint8(tos & 0xff)
        self.iic.write( _bytes, 0x3, 2 )

    ##
    #  @brief Set hysteresis
    # 
    #  @param thyst hysteresis
    # 
    def set_thyst( self, thyst ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((thyst >> 8) & 0xff)
        _bytes[1] = uint8(thyst & 0xff)
        self.iic.write( _bytes, 0x2, 2 )

