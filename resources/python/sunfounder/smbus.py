#
# ScriptML example hardware API
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

##
#  @file
#  @brief example hardware API
#
# Supports example code in third_party/rasberrypi/Sensor_Kit_V2.0_for_B_RPi2_andRPi3/SunFounder_SensorKit_for_RPi2/Python/

class SMBus:
	def __init__(self, rpi_version):
		pass
	
	def write_byte(self, address, val):
		print "Writing", address, val
		
	def read_byte(self, address):		
		print "Reading", address
		return 100
				
	def write_byte_data(self, address, v0, v1): # TODO suspect this is varargs
		self.write_byte(address,v0)
		self.write_byte(address,v1)

	def read_byte_data(self, address, adr):		 # no idea about semantics
		return 0

				
