## @file
#  @package ad7991
#
#  @brief AD7991 ADC device driver.
#
# Support for ADC operations
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

from numpy import *
import i2c

BASE_ADDR = 0x28

ONE_CHAN    = 0x10
TWO_CHAN    = 0x30
THREE_CHAN  = 0x70
FOUR_CHAN   = 0xF0

## @brief AD7991 device driver class
#
# Instantiate one of these for each device
class device:
    ## @brief Create device driver instance
    #
    # @param i2c An instance of the I2C driver for the bus on which the device is placed
    # @param addr_offset The I2C address offset, corresponding to the value on the Ax pins
    # @param numChannel One of ONE_CHAN, TWO_CHAN, THREE_CHAN, FOUR_CHAN
    def __init__( self, i2c, addr_offset ):
        self.iic = i2c
        self.addr = BASE_ADDR | addr_offset


    ## @brief Destroy device driver instance
    def __del__( self ):
        del self.iic		


    def set_channel( self, channel):
        self.control = channel
        c = self.iic.msg( self.addr, 0, [uint8(self.control)] )
        self.iic.transfer([c])        

    ## @brief Get the level of the analogue inputs, the device will cycle through all active inputs
    #
    # @param channel Channel number to read; 0 thru 3 depending on mode
    # @return A byte containing the read back value
    #
    # Note: the channel numbers given here map to the AINx pins in mode
    # FOUR_SINGLE. For other modes, see the data sheet.
    #
    def get_level( self ):
        MSB = uint8(0)
        LSB = uint8(0)
        r = self.iic.msg( self.addr, i2c.I2C_M_RD, [MSB, LSB] )
        self.iic.transfer([r])
        # The returned value will include the channel identity and the 12 bit value
        channel = (MSB & 0x30)>> 4
        value = LSB + ((MSB & 0x0F) << 8)
        return channel, value
