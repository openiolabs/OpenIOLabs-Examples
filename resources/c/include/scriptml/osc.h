/** @file
 *
 * @brief OSC (Open Sound Control) basic API
 *
 * General:
 *
 * A single handler may be registered for all incoming messages. This
 * handler will also receive the acknowledgement messages resulting from
 * sending commands. A sending function is also provided.
 *
 * Copyright (c) Open IO Labs Ltd 2017
 * All Rights Reserved
 */

#include <unistd.h>
#include <assert.h>
#include <string.h>

/**
 *  @brief Specify handler for OSC messages
 *
 *  @param HANDLER OSC message handler function
 */
#define sml_osc_addmethod( HANDLER, DEVICE_IP, MY_PORT ) \
{ \
	___OMISend(request:"OSC_AddMethod", client_handle:-1, snippet_payload:___ISeq(HANDLER), str_payload:DEVICE_IP, int_payload:___ISeq(MY_PORT), float_payload:___ISeq()); \
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); \
	assert( l[0]=="OK" ); \
}


/**
 *  @brief Send an OSC message
 *
 *  @param ip IP address of the OSC device
 *  @param path OSC-defined path to the resource to write (a string separated by /)
 *  @param types OSC-defined types of the parameters of the message
 *  @param sargv String arguments referenced by types argument, in their own order
 *  @param sargc Number of string arguments
 *  @param iargv Integer arguments referenced by types argument, in their own order
 *  @param iargc Number of integer arguments
 *  @param fargv Floating-point arguments referenced by types argument, in their own order
 *  @param fargc Number of floating-point arguments
 */
void sml_osc_send( char *device_ip, char *path, char *types, char **sargv, int sargc, int *iargv, int iargc, float *fargv, int fargc )
{
	int i;
	char sarg[256];
	char *psarg = sarg;
	strcpy(sarg, device_ip);
	strcat(sarg, ":");
	strcat(sarg, path);
	strcat(sarg, ":");
	strcat(sarg, types);
	for( i=0; i<sargc; i++ )
	{
		strcat(sarg, ":");
		strcat(sarg, sargv[i]);
	}

	___ListType_T(element_type:___IntegerType(), size:___NULL()) iarg;
	for( i=0; i<iargc; i++ )
	{
		___ListType_T(element_type:___IntegerType(), size:1) app;
		app[0] = iargv[i];
		iarg += app;
	}
	
	___ListType_T(element_type:___FloatType(), size:___NULL()) farg;
	for( i=0; i<fargc; i++ )
	{
		___ListType_T(element_type:___FloatType(), size:1) app;
		app[0] = fargv[i];
		farg += app;
	}
	
	___VarSend(request:"OSC_Send", client_handle:-1, str_payload:psarg, int_payload:iarg, float_payload:farg); 
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); 
	assert( l[0]=="OK" ); 	
}
