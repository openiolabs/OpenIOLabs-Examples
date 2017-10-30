## @file
#  @package comms
#
#  @brief ScriptML client communications example
#
# Example code only. Demonstrates the use of intrinsics to create
# Send and Receive nodes and how to wrap them in straightforward 
# API functions.
# 
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

##
#  @brief Example read from an inaginary device
#
# @param device A string that specifies the device to read 
# @return An integer value read from the device
def ReadFromDevice(device):
	___Send(request="ReadFromDevice", client_handle=-1, str_payload=device, int_payload=___ISeq(), float_payload=___ISeq())
	l = ___Receive()
	assert l[0]=="Value" 
	return l[1]


##
# @brief Example notification to a server
#
# @param value The value to be sent to the server
def Notify( value ):
	___Send(request="Notify", client_handle=-1, str_payload=___NULL(), int_payload=___ISeq(value, value+1), float_payload=___ISeq())
	l = ___Receive()
	assert l[0]=="OK";
