## @file
#
# @brief Special functions for managing persistent flags.
# 
# Persistent flags may be used to store small amounts of data on the IOI
# that remains present after a restart, power-cycle or firmware upgrade
# (but not a re-imaging of the SD card).
# 
# Each flag has a name (which should contain alpha-numeric and _ only) and
# a value which can be a string, integer or floating-point number.
# 
# Writing or attempting to read a non-existant flag creates it.
# 
# Flags may also be accessed from the server.
#
# Copyright (c) Open IO Labs Ltd 2017
# All Rights Reserved
#

##
#  @brief Persistent flag objects permitting read and write operations
#
#  @param n name of the flag
#
class flag:
	def __init__( self, n ):
		self.name = n
		
	##
	#  @brief Write a string to a persistent flag
	#
	#  @param value String to write
	#
	def write_str( self, value ):		
		___Send(request="PersistentFlag_WriteStr", client_handle=___NULL(), str_payload=self.name+":"+value, int_payload=___ISeq(), float_payload=___ISeq())
		l = ___Receive()
		
		# Check that the response message was as expected - we require OK
		assert l[0]=="OK"

	##
	#  @brief Write an integer to a persistent flag
	#
	#  @param value Number to write
	#
	def write_int( self, value ):
		___Send(request="PersistentFlag_WriteInt", client_handle=___NULL(), str_payload=self.name, int_payload=___ISeq(value), float_payload=___ISeq())
		l = ___Receive()
		
		# Check that the response message was as expected - we require OK
		assert l[0]=="OK"

	##
	#  @brief Write a floating-point value to a persistent flag
	#
	#  @param value Number to write
	#
	def write_float( self, value ):
		___Send(request="PersistentFlag_WriteFloat", client_handle=___NULL(), str_payload=self.name, int_payload=___ISeq(), float_payload=___ISeq(value))
		l = ___Receive()
		
		# Check that the response message was as expected - we require OK
		assert l[0]=="OK"

	##
	#  @brief Read a string from a persistent flag
	#
	#  @return String value
	#
	def read_str( self ):
		___Send(request="PersistentFlag_ReadStr", client_handle=___NULL(), str_payload=self.name, int_payload=___ISeq(), float_payload=___ISeq())
		l = ___Receive()
		
		# Check that the response message was as expected - we require Value
		assert l[0]=="Value"
		return l[1]
		
	##
	#  @brief Read an integer from a persistent flag
	#
	#  @return Integer value
	#
	def read_int( self ):
		___Send(request="PersistentFlag_ReadInt", client_handle=___NULL(), str_payload=self.name, int_payload=___ISeq(), float_payload=___ISeq())
		l = ___Receive()
		
		# Check that the response message was as expected - we require Value
		assert l[0]=="Value"
		return l[1]
		
	##
	#  @brief Read a floating-point value from a persistent flag
	#
	#  @return Floating-point value
	#
	def read_float( self ):
		___Send(request="PersistentFlag_ReadFloat", client_handle=___NULL(), str_payload=self.name, int_payload=___ISeq(), float_payload=___ISeq())
		l = ___Receive()
		
		# Check that the response message was as expected - we require Value
		assert l[0]=="Value"
		return l[1]
