## @file
#  @package pcf8591
#
#  @brief PCF8591 ADC device driver.
#
# Support for DAC and ADC operations
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

from numpy import *
import i2c

BASE_ADDR = 0x48

FOUR_SINGLE = 0
THREE_DIFF  = 1
MIXED 		= 2
TWO_DIFF	= 3

## @brief PCF8591 device driver class
#
# Instantiate one of these for each device
class device:
	## @brief Create device driver instance
	#
	# @param i2c An instance of the I2C driver for the bus on which the device is placed
	# @param addr_offset The I2C address offset, corresponding to the value on the Ax pins, 0 through 73 inclusive
	# @param mode One of FOUR_SINGLE, THREE_DIFF, MIXED or TWO_DIFF
	def __init__( self, i2c, addr_offset, mode ):
		self.iic = i2c
		self.addr = BASE_ADDR | addr_offset
		self.control = 0x40 | (mode << 4)
		c = self.iic.msg( self.addr, 0, [uint8(self.control)] )
		self.iic.transfer([c])
		
	## @brief Destroy device driver instance
	def __del__( self ):
		del self.iic				
		
	## @brief Enable analogue output pin
	#
	# @param enable Enable bit; 1 to enable	
	def enable_output( self, enable ):
		self.control = (self.control | 0x40) if enable else (self.control & ~0x40)
		c = self.iic.msg( self.addr, 0, [uint8(self.control)] )
		self.iic.transfer([c])
		
	## @brief Set the level of DAC output pin
	#
	# @param channel Channel number to set; 0 or 1
	# @param level A byte containing the level; 0 through 255 inclusive
	def set_level( self, level ):
		c = self.iic.msg( self.addr, 0, [uint8(self.control), uint8(level)] )
		self.iic.transfer([c])
		
	## @brief Get the level of one of the analogue inputs
	#
	# @param channel Channel number to read; 0 thru 3 depending on mode
	# @return A byte containing the read back value
	#
	# Note: the channel numbers given here map to the AINx pins in mode
	# FOUR_SINGLE. For other modes, see the data sheet.
	#
	def get_level( self, channel ):
		command = self.control | channel 
		c = self.iic.msg( self.addr, 0, [uint8(command)] )
		flush = uint8(0) # need to throw away the first-read value (is old data)
		value = uint8(0)
		r = self.iic.msg( self.addr, i2c.I2C_M_RD, [flush, value] )
		self.iic.transfer([c, r])
		return value
