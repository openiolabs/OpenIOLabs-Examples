## @file
#  @package pcf8574
#
#  @brief PCF8574 IO Expander device driver.
#
# Support for input, output and interrupt-on-change, using a seperate GPIO.
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

from numpy import *
import time
import coroutines
import gpio

BASE_ADDR = 0x20

## @brief PCF8574 device driver class
#
# Instantiate one of these for each device
class device:
	## @brief Create device driver instance
	#
	# @param i2c An instance of the I2C driver for the bus on which the device is placed
	# @param addr_offset The I2C address offset, corresponding to the value on the Ax pins, 0 through 7 inclusive
	# @param nint_gpio Optional GPIO device instance to which the ~int pin is connected
	def __init__( self, i2c, addr_offset, nint_gpio=None ):
		self.iic = i2c
		self.addr = BASE_ADDR | addr_offset
		self.nint_pin = nint_gpio
		if self.nint_pin is not None:
			self.nint_pin.set_direction( gpio.IN )

	## @brief Destroy device driver instance
	def __del__( self ):
		del self.iic
		if self.nint_pin is not None:
			del self.nint_pin
			
	## @brief Set direction of the pins on the IO expander
	#
	# @param dirs A byte containing the directions for pins 0 through 7 in binary
	#
	# Use 0 for input and 1 for output. 
	# Note: Pins are quasi-bidirectional - see data sheet
	def set_direction( self, dirs ):
		self.dirmask = dirs ^ 0xFF 
		msg = self.iic.msg( self.addr, 0, [uint8(self.dirmask)] )		
		self.iic.transfer( [msg] )

	## @brief Set the level of output pins on the IO expander
	#
	# @param values A byte containing the levels for output pins 0 through 7 in binary
	def set_level( self, values ):
		msg = self.iic.msg( self.addr, 0, [uint8(values | self.dirmask)] )
		self.iic.transfer( [msg] )

	## @brief Get the level of input pins on the IO expander
	#
	# @return A byte containing the levels for input pins 0 through 7 in binary
	def get_level( self ):
		values = uint8(0)
		msg = self.iic.msg( self.addr, i2c.I2C_M_RD, [values] )
		self.iic.transfer( [msg] )
		return values & self.dirmask

	## @brief Wait for any change on input pins (requires optional GPIO device)
	def wait_any_change( self ): # placeholder: should really be attached to read()
		assert self.nint_pin is not None, "A GPIO must be provided to the I2C extender to permit waiting"
		___Wait( test=(self.nint_pin.get_level() == 0) ) # active-low TODO use coroutines.wait() once OP-797 is done
		self.get_level() # clear the interrupt TODO may need to make this a seperate op for spinless wait integration
