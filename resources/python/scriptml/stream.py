## @file
#
# @brief Streaming to external server
#
# General:
#
# Sends data to an external server using HTTP PUT and POST operations.
# 
# When appending, data is POSTed. When not appending, the first block is 
# PUT, and subsequent blocks are POSTed. 
# 
# The API can accept strings, integers and floating point values. These
# are sent as binary. For best efficiency, API call overhad should be 
# amortised by sending at least 100 data items in each API call. Internal 
# buffering can store up a large number of such buffers while it waits 
# for successful completion of HTTP POST or PUT operations to the server.
# 
# Python-API-specific:
# 
# The write_data API is capable of working on a list whose elements may 
# be any mixture of integers and floating-point numbers.
#
# Copyright (c) Open IO Labs Ltd 2017
# All Rights Reserved
#

class server_stream:
	##
	# @brief Open a device. Returns a handle.
	#
	# @param dest_ip IP address of customer server
	# @param dest_path HTTP path to POST/PUT to (typically a file path in some sandbox)
	# @param append 1 to append to object to dest_path, 0 to overwrite
    #
	def __init__(self, dest_ip, dest_path, append):
		self.obj = ___Construct( object_type=___ServerStreamType(), args_list=___ArgsList(args=___ISeq(dest_ip, dest_path, append)), args_map=___ArgsMap(args=___IMap()) )

	##
	# @brief Write a string to device
	#
	# @param data Data to write to the device
	#
	def write_string( self, s ):	
		___Write( device=self.obj, pos=___NULL(), data=s )

	##
	# @brief Write data to device
	#
	# @param data Data to write to the device
	#
	def write_data( self, data ):
		___Write( device=self.obj, pos=___NULL(), data=data )
	
