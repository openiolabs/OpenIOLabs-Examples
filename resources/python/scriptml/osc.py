## @file
#
# @brief OSC (Open Sound Control) basic API
#
# General:
#
# A single handler may be registered for all incoming messages. This
# handler will also receive the acknowledgement messages resulting from
# sending commands. A sending function is also provided.
#
# Copyright (c) Open IO Labs Ltd 2017
# All Rights Reserved
#

_osc_user_data_map={} 


def _handler( my_port, path, ints, floats, strings ):
	global _osc_user_data_map
	_user_handler( _osc_user_data_map[my_port], path, ints, floats, strings )
	
	
##
# @brief Specify handler for OSC messages
#
# @param handler OSC message handler function
# @param my_port Handler is called for messages incoming on this port
# @param device_ip IP address of the device
# @param device_port Port on device to send messages to
# @param data A user data object that is passed to the handler
#
def init(handler, my_port, device_ip, device_port, data):
	global _user_handler
	global _osc_user_data_map
	_user_handler = handler
	_osc_user_data_map[my_port] = data
	___OMISend(request="OSC_AddMethod", client_handle=-1, snippet_payload=___ISeq(_handler), str_payload=device_ip, int_payload=___ISeq(my_port, device_port), float_payload=___ISeq())
	l = ___Receive()
	assert l[0]=="OK"


##
# @brief Send an OSC message
#
# @param device_ip IP address of the OSC device
# @param path OSC-defined path to the resource to write (a string separated by /)
# @param types OSC-defined types of the parameters of the message
# @param sargv String arguments referenced by types argument, in their own order
# @param iargv Integer arguments referenced by types argument, in their own order
# @param fargv Floating-point arguments referenced by types argument, in their own order
#
def send_message( device_ip, path, types, sargv, iargv, fargv ):
	sarg = device_ip + ":" + path + ":" + types
	for s in sargv:
		sarg += ":" + s

	___VarSend(request="OSC_Send", client_handle=-1, str_payload=sarg, int_payload=iargv, float_payload=fargv)
	l = ___Receive()
	assert l[0]=="OK";

