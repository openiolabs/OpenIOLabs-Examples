## @file
#  @package serial
#
#  @brief Simple serial port driver
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

import devsysfs

## @brief serial device driver class
#
# Instantiate one of these for each serial port
class device:
	##
	#  @brief Initialise access to the serial port
	#
	#  @return handle for the serial port
	#
	def __init__( self ):
		self.path = "/dev/ttyAMA0" # TODO or /dev/ttyS0 or /dev/serialx
		 		
	##
	#  @brief End access to the serial port
	#
	def close( self ):
		pass

	##
	#  @brief Write to serial port
	#
	#  @param h serial port handle
	#  @param text text to write to the port
	#
	def write( self, text ):
		devsysfs.mono_write( self.path, text )
		 
	##
	#  @brief Read from serial port
	#
	#  @param h serial port handle
	#  @return buffer for text read from port
	#
	def read( self ):
		return devsysfs.mono_read_to_eof( self.path )
