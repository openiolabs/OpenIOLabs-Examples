## @file
#  @package mpl115a2
# 
#  @brief Miniature I2C Digital Barometer
# 
#  MPL115A2 Digital Barometer 
#  ==========================
#  
#  Read out the constants `a0`, `b1`, `b2` and `c12`, then `convert` and finally read back `Padc` and `Tadc`
#  
#  Auto-generated 01 May 2018; do not edit
#  
#  Copyright (c) Open IO Labs Ltd 2017
#  All Rights Reserved
# 

from i2c_regmap import *

BASE_ADDR = 0x60

class device:
    ##
    #  @brief Create device driver instance
    # 
    #  @param i2c An instance of the I2C driver for the bus on which the device is placed
    #  @return Device handle
    # 
    def __init__( self, i2c ):
        self.iic = i2c_regmap( i2c, BASE_ADDR, 0x100, True )

    ##
    #  @brief Get Pressure ADC output value
    # 
    #  @param padc list containing Pressure ADC output value
    # 
    def get_padc( self, padc ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x0, 2 )
        _value = uint16((_bytes[0] << 8) | _bytes[1])
        padc[0] = (_value >> 6) & 0x3ff

    ##
    #  @brief Get Temperature ADC output value
    # 
    #  @param tadc list containing Temperature ADC output value
    # 
    def get_tadc( self, tadc ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x2, 2 )
        _value = uint16((_bytes[0] << 8) | _bytes[1])
        tadc[0] = (_value >> 6) & 0x3ff

    ##
    #  @brief Get a0 coefficient
    # 
    #  @return a0 coefficient
    # 
    def get_a0( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x4, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Get b1 coefficient
    # 
    #  @return b1 coefficient
    # 
    def get_b1( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x6, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Get b2 coefficient
    # 
    #  @return b2 coefficient
    # 
    def get_b2( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x8, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Get c12 coefficient
    # 
    #  @return c12 coefficient
    # 
    def get_c12( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0xa, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Start Pressure and Temperature Conversion
    # 
    # 
    def convert( self ):
        _value = uint8(0)
        self.iic.write( [_value], 0x12, 1 )

