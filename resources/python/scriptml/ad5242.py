## @file
#  @package ad5242
#
#  @brief AD5242 digital pot device driver.
#
# Support for wiper position setting on both channels, digital out, power down and reset
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

from numpy import *

BASE_ADDR = 0x2C

## @brief AD5242 device driver class
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
		
	## @brief Set the wiper position of a digital pot
	#
	# @param channel Channel number to update; 0 or 1
	# @param level A byte containing the wiper position; 0 through 255 inclusive
	# @param logic Optional 2-bit value to output on pins O1 and O2
	def set_position( self, channel, level, logic=0 ):
		command = (channel << 7) | (logic << 3) 
		m = self.iic.msg( self.addr, 0, [uint8(command), uint8(level)] )
		self.iic.transfer([m])
	
	## @brief Set power status
	#
	# @param power Power status; 0 for off, 1 for on
	#
	# Note: device is intially powered on
	def power( self, power ):
		command = 0x0 if power else 0x20
		m = self.iic.msg( self.addr, 0, [uint8(command), uint8(0)] )
		self.iic.transfer([m])

	## @brief Reset device
	#
	# Device is reset as described in the data sheet
	def reset( self ):
		command = 0x40
		m = self.iic.msg( self.addr, 0, [uint8(command), uint8(0)] )
		self.iic.transfer([m])
