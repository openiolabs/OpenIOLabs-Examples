/** @file
 *
 * @brief Special functions for managing persistent flags.
 * 
 * Persistent flags may be used to store small amounts of data on the IOI
 * that remains present after a restart, power-cycle or firmware upgrade
 * (but not a re-imaging of the SD card).
 * 
 * Each flag has a name (which should contain alpha-numeric and _ only) and
 * a value which can be a string, integer or floating-point number.
 * 
 * Writing or attempting to read a non-existant flag creates it.
 * 
 * Flags may also be accessed from the server.
 *
 * Copyright (c) Open IO Labs Ltd 2017
 * All Rights Reserved
 */

#ifndef __PERSISTENT_H
#define __PERSISTENT_H

#include <unistd.h>
#include <assert.h>
#include <string.h>

/**
 *  @brief Write a string to a persistent flag
 *
 *  @param name Name of flag to write
 *  @param value String to write
 */
void sml_persistent_flag_write_str( ___StringType_T( size:___NULL() ) name, ___StringType_T( size:___NULL() ) value )
{
    ___Send(request:"PersistentFlag_WriteStr", client_handle:___NULL(), str_payload:name+":"+value, int_payload:___ISeq(), float_payload:___ISeq());
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive();
	
	// Check that the response message was as expected - we require OK
	assert( l[0]=="OK" );
}


/**
 *  @brief Write an integer to a persistent flag
 *
 *  @param name Name of flag to write
 *  @param value Number to write
 */
void sml_persistent_flag_write_int( ___StringType_T( size:___NULL() ) name, int value )
{
    ___Send(request:"PersistentFlag_WriteInt", client_handle:___NULL(), str_payload:name, int_payload:___ISeq(value), float_payload:___ISeq());
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive();
	
	// Check that the response message was as expected - we require OK
	assert( l[0]=="OK" );
}


/**
 *  @brief Write a floating point value to a persistent flag
 *
 *  @param name Name of flag to write
 *  @param value Number to write
 */
void sml_persistent_flag_write_float( ___StringType_T( size:___NULL() ) name, float value )
{
    ___Send(request:"PersistentFlag_WriteFloat", client_handle:___NULL(), str_payload:name, int_payload:___ISeq(), float_payload:___ISeq(value));
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive();
	
	// Check that the response message was as expected - we require OK
	assert( l[0]=="OK" );
}


/**
 *  @brief Read a string from a persistent flag. 
 * 
 * Default string is ""
 *
 *  @param name Name of flag to write
 *  @param buf Buffer to receive the string
 */
void sml_persistent_flag_read_str( ___StringType_T( size:___NULL() ) name, char *buf )
{
    ___Send(request:"PersistentFlag_ReadStr", client_handle:___NULL(), str_payload:name, int_payload:___ISeq(), float_payload:___ISeq());
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive();
	
	// Check that the response message was as expected - we require Value
	assert( l[0]=="Value" );
	
	strcpy( buf, l[1] );
}


/**
 *  @brief Read an integer from a persistent flag
 *
 * Default integer is 0
 * 
 *  @param name Name of flag to write
 *  @return value in flag
 */
int sml_persistent_flag_read_int( ___StringType_T( size:___NULL() ) name )
{
    ___Send(request:"PersistentFlag_ReadInt", client_handle:___NULL(), str_payload:name, int_payload:___ISeq(), float_payload:___ISeq());
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive();
	
	// Check that the response message was as expected - we require Value
	assert( l[0]=="Value" );
	
	return l[1];
}


/**
 *  @brief Read a floating-point number from a persistent flag
 *
 * Default integer is 0.0
 * 
 *  @param name Name of flag to write
 *  @return value in flag
 */
float sml_persistent_flag_read_float( ___StringType_T( size:___NULL() ) name )
{
    ___Send(request:"PersistentFlag_ReadFloat", client_handle:___NULL(), str_payload:name, int_payload:___ISeq(), float_payload:___ISeq());
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive();
	
	// Check that the response message was as expected - we require Value
	assert( l[0]=="Value" );
	
	return l[1];
}

#endif
 
