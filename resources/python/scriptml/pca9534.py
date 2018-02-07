## @file
#  @package pca9534
# 
#  @brief GPIO Extender
# 
#  8-bit I2C-bus and SMBus low power I/O port with interrupt
#  
#  
#  Configuration register is really a direction register. Bits set to 1 correspond to inputs and 0 to outputs.
#  
#  
#  
#  Auto-generated 07 February 2018; do not edit
#  
#  Copyright (c) Open IO Labs Ltd 2017
#  All Rights Reserved
# 

from i2c_regmap import *
from gpio import *

BASE_ADDR = 0x20

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
        self.iic = i2c_regmap( i2c, BASE_ADDR + addr_offset, 0x100, True )

    ##
    #  @brief Get Input Port register
    # 
    #  @return Input Port register
    # 
    def get_input( self ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x0, 1 )
        return _bytes[0]

    ##
    #  @brief Set Output Port register
    # 
    #  @param output Output Port register
    # 
    def set_output( self, output ):
        self.iic.write( [output], 0x1, 1 )

    ##
    #  @brief Get Output Port register
    # 
    #  @return Output Port register
    # 
    def get_output( self ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x1, 1 )
        return _bytes[0]

    ##
    #  @brief Set Polarity Inversion register
    # 
    #  @param polarity Polarity Inversion register
    # 
    def set_polarity( self, polarity ):
        self.iic.write( [polarity], 0x2, 1 )

    ##
    #  @brief Get Polarity Inversion register
    # 
    #  @return Polarity Inversion register
    # 
    def get_polarity( self ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x2, 1 )
        return _bytes[0]

    ##
    #  @brief Set Configuration register
    # 
    #  @param configuration Configuration register
    # 
    def set_configuration( self, configuration ):
        self.iic.write( [configuration], 0x3, 1 )

    ##
    #  @brief Get Configuration register
    # 
    #  @return Configuration register
    # 
    def get_configuration( self ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x3, 1 )
        return _bytes[0]

