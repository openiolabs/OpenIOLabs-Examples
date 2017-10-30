## @file
#  @package max518
#
#  @brief MAX518 DAC device driver.
#
# Support for output level setting on both channels, power down and reset
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

from numpy import *

BASE_ADDR = 0x2C

## @brief MAX518 device driver class
#
# Instantiate one of these for each device
class device:
	## @brief Create device driver instance
	#
	# @param i2c An instance of the I2C driver for the bus on which the device is placed
	# @param addr_offset The I2C address offset, corresponding to the value on the Ax pins, 0 through 3 inclusive
	def __init__( self, i2c, addr_offset ):
		self.iic = i2c
		self.addr = BASE_ADDR | addr_offset
		
	## @brief Destroy device driver instance
	def __del__( self ):
		del self.iic
		
	## @brief Set the level of output pins on the DAC
	#
	# @param channel Channel number to set; 0 or 1
	# @param level A byte containing the level; 0 through 255 inclusive
	def set_level( self, channel, level ):
		command = channel
		m = self.iic.msg( self.addr, 0, [uint8(command), uint8(level)] )
		self.iic.transfer([m])
	
	## @brief Set power status
	#
	# @param power Power status; 0 for off, 1 for on
	#
	# Note: device is intially powered on
	def power( self, power ):
		command = 0x0 if power else 0x8
		m = self.iic.msg( self.addr, 0, [uint8(command)] )
		self.iic.transfer([m])

	## @brief Reset device
	#
	# Device is reset as described in the data sheet
	def reset( self ):
		command = 0x10
		m = self.iic.msg( self.addr, 0, [uint8(command)] )
		self.iic.transfer([m])
