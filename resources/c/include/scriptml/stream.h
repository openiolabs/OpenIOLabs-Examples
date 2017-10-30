/** @file
 *
 * @brief Streaming to external server
 *
 * General:
 *
 * Sends data to an external server using HTTP PUT and POST operations.
 * 
 * When appending, data is POSTed. When not appending, the fist block is 
 * PUT, and subsequent blocks are POSTed. 
 * 
 * The API can accept strings, integers and floating point values. These
 * are sent as binary. For best efficiency, API call overhad should be 
 * amortised by sending at least 100 data items in each API call. Internal 
 * buffering can store up a large number of such buffers while it waits 
 * for successful completion of HTTP POST or PUT operations to the server.
 * 
 * C-API-specific:
 * 
 * The C api provides seperate functions for:
 * - A single string
 * - An array of ints
 * - An array of floats
 * 
 * The python API is more expressive.
 * 
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __STREAM_H
#define __STREAM_H

#include <unistd.h>

// Doing strings this way makes for slightly smaller scripts and faster
typedef ___StringType_T( size:___NULL() ) _str;
// OP-844 is to let this be a typedef
#define _data ___NULL_T()

typedef ___ServerStreamType_T() **sml_server_stream_t;


/**
 *  @brief Open a device. Returns a handle.
 *
 *  @param dest_ip IP address of customer server
 *  @param dest_path HTTP path to POST/PUT to (typically a file path in some sandbox)
 *  @param append 1 to append to object to dest_path, 0 to overwrite
 *  @return Device handle
 */
sml_server_stream_t sml_server_stream_open( _str dest_ip, _str dest_path, int append )
{ 
	return & &___Construct( object_type:___ServerStreamType(), args_list:___ArgsList(args:___ISeq(dest_ip, dest_path, append)), args_map:___ArgsMap(args:___IMap()) );
}


/**
 *  @brief Close a device. 
 *
 *  @param dev Stream handle
 */
void sml_server_stream_close( sml_server_stream_t dev )
{
	*dev = NULL;
}


/**
 *  @brief Write a string to server
 *
 *  @param dev Stream handle
 *  @param data String to write to the server
 */
void sml_server_stream_write_string( sml_server_stream_t dev, _str s )
{
	___Write( device:**dev, pos:___NULL(), data:s );	
}


/**
 *  @brief Write integer data to server
 *
 *  @param dev Stream handle
 *  @param data Data to write to the server
 */
void sml_server_stream_write_ints( sml_server_stream_t dev, _data data )
{
	___Write( device:**dev, pos:___NULL(), data:data );	
}


/**
 *  @brief Write flaoting-point data to server
 *
 *  @param dev Stream handle
 *  @param data Data to write to the server
 */
void sml_server_stream_write_floats( sml_server_stream_t dev, _data data )
{
	___Write( device:**dev, pos:___NULL(), data:data );	
}

#endif
 
