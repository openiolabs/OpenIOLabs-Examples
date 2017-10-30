/** @file
 * 
 *  @brief ScriptML client communications example
 *
 * Example code only. Demonstrates the use of intrinsics to create
 * Send and Receive nodes and how to wrap them in straightforward 
 * API functions.
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __COMMS_H
#define __COMMS_H

#ifndef __SCRIPTML
#error "This header file can only be used with ScriptML" 
#endif

/**
 *  @brief Example read from an inaginary device
 *
 *  @param device A string that specifies the device to read 
 *  @return An integer value read from the device
 */
int ReadFromDevice(___StringType_T(size:___NULL()) device)
{
	// Use an intrinsic to create a Send node, which is a kind of Statement and can
	// therefore be interpreted to perform the actual transaction. request, 
	// strpayload and numpayload are the outgoing message.
	___Send(request:"ReadFromDevice", client_handle:___NULL(), str_payload:device, int_payload:___ISeq(), float_payload:___ISeq());
	
	// Receive is a kind of expression and can be evaluated to get the message.
	// The incoming message is placed in the three elements of a List
	// (again, an intrinsic is used to allow a non-C list node)
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive();
	
	// Check that the response message was as expected - we require a Value
	assert( l[0]=="Value" );
	
	// Extract the actual value from the response message and return it
	return l[1];
}


/**
 *  @brief Example notification to a server
 *
 *  @param value The value to be sent to the server
 */
void Notify( int value )
{
	// As with device_read except we only expect an OK 
	___Send(request:"Notify", client_handle:___NULL(), str_payload:___NULL(), int_payload:___ISeq(value), float_payload:___ISeq(value+1));
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive();
	assert( l[0]=="OK" );
}

#endif
 
