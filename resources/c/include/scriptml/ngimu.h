/** @file
 *
 * @brief X-IO NGIMU (NExt Generation Inertial M<anagement Unit) driver layer
 *
 * General:
 *
 * This driver controls and receives messages from the NGIMU unit, using OSC 
 * for communication. Incoming messages are handled by implementing handler 
 * functions matching the calls made from the _ngimu_handler() function.
 *
 * Commands are implemented directly in functions named ngimu_command_x(). These
 * methods block until an ack is received.
 *
 * Other sends should use the ngimu_send() method with arguments gien according to
 * the documentation for osc.py.
 *
 * C-API-specific:
 *
 * Detailed per-function documentation will be added when required.
 * 
 * Copyright (c) Open IO Labs Ltd 2017
 * All Rights Reserved
 */

#include <osc.h>

typedef struct
{
	char *ip;
	int ngimu_ack_mute;
	int ngimu_ack_unmute;
	int ngimu_ack_reset;
	int ngimu_ack_sleep;
	int ngimu_ack_identify;
	int ngimu_ack_apply;
	int ngimu_ack_default;
	int ngimu_ack_ahrs_initialise;
	int ngimu_ack_ahrs_zero;
	int ngimu_ack_echo;
} ngimu_t;


ngimu_t *_ngimu_instance;


void ngimu_handle_buttons()
{
}


void ngimu_handle_sensors( float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float b )
{
}


void ngimu_handle_magnitudes( float g, float a, float m )
{
}


void ngimu_handle_quaternion( float w, float x, float y, float z )
{
}


void ngimu_handle_matrix( float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz )
{
}


void ngimu_handle_euler( float roll, float pitch, float yaw )
{
}


void ngimu_handle_linear( float x, float y, float z )
{
}


void ngimu_handle_earth( float x, float y, float z )
{
}


void ngimu_handle_euler( float roll, float pitch, float yaw )
{
}


void ngimu_handle_altitude( float a )
{
}


void ngimu_handle_temperature( float tp, float tg, float tb )
{
}


void ngimu_handle_humidity( float h )
{
}


void ngimu_handle_battery( float l, float t, float v, float i, char *st )
{
}


void ngimu_handle_analogue( float c1, float c2, float c3, float c4, float c5, float c6, float c7, float c8 )
{
}


void ngimu_handle_rssi( float dbm, float percent )
{
}


void ngimu_handle_auxserial( char *str )
{
}


void ngimu_handle_auxserial_cts( int cts )
{
}


void ngimu_handle_serial_cts( int cts )
{
}


void _ngimu_handler( ___StringType_T(size:___NULL()) path, 
                     ___ListType_T(element_type:___IntegerType(), size:___NULL()) ints, 
                     ___ListType_T(element_type:___FloatType(), size:___NULL()) floats, 
                     ___ListType_T(element_type:___StringType(size:___NULL()), size:___NULL()) strings )
{
	ngimu_t *h = _ngimu_instance;
	if( strcmp(path, "/buttons")==0 )
	{
		ngimu_handle_buttons(); 
	}
	else if( strcmp(path, "/sensors")==0 )
	{
		ngimu_handle_sensors( floats[0], floats[1], floats[2], floats[3], floats[4], floats[5], floats[6], floats[7], floats[8], floats[9] );
	}
	else if( strcmp(path, "/magnitudes")==0 )
	{
		ngimu_handle_magnitudes( floats[0], floats[1], floats[2] );
	}
	else if( strcmp(path, "/quaternion")==0 )
	{
		ngimu_handle_quaternion( floats[0], floats[1], floats[2], floats[3] );
	}
	else if( strcmp(path, "/matrix")==0 )
	{
		ngimu_handle_matrix( floats[0], floats[1], floats[2], floats[3], floats[4], floats[5], floats[6], floats[7], floats[8] );
	}
	else if( strcmp(path, "/euler")==0 )
	{
		ngimu_handle_euler( floats[0], floats[1], floats[2] );
	}
	else if( strcmp(path, "/linear")==0 )
	{
		ngimu_handle_linear( floats[0], floats[1], floats[2] );
	}
	else if( strcmp(path, "/earth")==0 )
	{
		ngimu_handle_earth( floats[0], floats[1], floats[2] );
	}
	else if( strcmp(path, "/altitude")==0 )
	{
		ngimu_handle_altitude( floats[0] );
	}
	else if( strcmp(path, "/temperature")==0 )
	{
		ngimu_handle_temperature( floats[0], floats[1], floats[2] );
	}
	else if( strcmp(path, "/humidity")==0 )
	{
		ngimu_handle_humidity( floats[0] );
	}
	else if( strcmp(path, "/battery")==0 )
	{
		ngimu_handle_battery( floats[0], floats[1], floats[2], floats[3], strings[0] ); 
	}
	else if( strcmp(path, "/analogue")==0 )
	{
		ngimu_handle_analogue( floats[0], floats[1], floats[2], floats[3], floats[4], floats[5], floats[6], floats[7] ); 
	}
	else if( strcmp(path, "/rssi")==0 )
	{
		ngimu_handle_rssi( floats[0], floats[1] ); 
	}
	else if( strcmp(path, "/auxserial")==0 )
	{
		ngimu_handle_auxserial( strings[0] ); 
	}
	else if( strcmp(path, "/auxserial/cts")==0 )
	{
		ngimu_handle_auxserial_cts( ints[0] ); 
	}
	else if( strcmp(path, "/serial/cts")==0 )
	{
		ngimu_handle_serial_cts( ints[0] ); 
	}
	else if( strcmp(path, "/mute")==0 )
	{
		h->ngimu_ack_mute = 1;
	}
	else if( strcmp(path, "/unmute")==0 ) 
	{
		h->ngimu_ack_unmute = 1;
	}
	else if( strcmp(path, "/reset")==0 ) 
	{
		h->ngimu_ack_reset = 1;
	}
	else if( strcmp(path, "/sleep")==0 ) 
	{
		h->ngimu_ack_sleep = 1;
	}
	else if( strcmp(path, "/identify")==0 ) 
	{
		h->ngimu_ack_identify = 1;
	}
	else if( strcmp(path, "/apply")==0 ) 
	{
		h->ngimu_ack_apply = 1;
	}
	else if( strcmp(path, "/default")==0 ) 
	{
		h->ngimu_ack_default = 1;
	}
	else if( strcmp(path, "/ahrs/initialise")==0 ) 
	{
		h->ngimu_ack_ahrs_initialise = 1;
	}
	else if( strcmp(path, "/ahrs/zero")==0 ) 
	{
		h->ngimu_ack_ahrs_zero = 1;
	}
	else if( strcmp(path, "/echo")==0 ) 
	{
		h->ngimu_ack_echo = 1;
	}
}


ngimu_t *ngimu_init( char *ip )
{ 
	ngimu_t h;
	_ngimu_instance = &h;
	h.ip = ip;
	h.ngimu_ack_mute = 0;
	h.ngimu_ack_unmute = 0;
	h.ngimu_ack_reset = 0;
	h.ngimu_ack_sleep = 0;
	h.ngimu_ack_identify = 0;
	h.ngimu_ack_apply = 0;
	h.ngimu_ack_default = 0;
	h.ngimu_ack_ahrs_initialise = 0;
	h.ngimu_ack_ahrs_zero = 0;
	h.ngimu_ack_echo = 0;
	sml_osc_addmethod( _ngimu_handler );
	return _ngimu_instance;
}


void ngimu_send( ngimu_t *h, char *path, char *types, char **sargv, int sargc, int *iargv, int iargc, float *fargv, int fargc )
{
	sml_osc_send( h->ip, path, types, sargv, sargc, iargv, iargc, fargv, fargc );
}


void ngimu_command( ngimu_t *h, int *ack_flag, char *path, char *types, char **sargv, int sargc, int *iargv, int iargc, float *fargv, int fargc )
{
	ngimu_send( h, path, types, sargv, sargc, iargv, iargc, fargv, fargc );
	// Await the acknowledgement
	while( *ack_flag == 0 )
	{
	}
	*ack_flag = 0;	
}


void ngimu_command_mute( ngimu_t *h )
{
	ngimu_command( h, &(h->ngimu_ack_mute), "/mute", "", NULL, 0, NULL, 0, NULL, 0 );
}


void ngimu_command_unmute( ngimu_t *h )
{
	ngimu_command( h, &(h->ngimu_ack_unmute), "/unmute", "", NULL, 0, NULL, 0, NULL, 0 );
}


void ngimu_command_reset( ngimu_t *h )
{
	ngimu_command( h, &(h->ngimu_ack_reset), "/reset", "", NULL, 0, NULL, 0, NULL, 0 );
}


void ngimu_command_sleep( ngimu_t *h )
{
	ngimu_command( h, &(h->ngimu_ack_sleep), "/sleep", "", NULL, 0, NULL, 0, NULL, 0 );
}


void ngimu_command_identify( ngimu_t *h )
{
	ngimu_command( h, &(h->ngimu_ack_identify), "/identify", "", NULL, 0, NULL, 0, NULL, 0 );
}


void ngimu_command_apply( ngimu_t *h )
{
	ngimu_command( h, &(h->ngimu_ack_apply), "/apply", "", NULL, 0, NULL, 0, NULL, 0 );
}


void ngimu_command_default( ngimu_t *h )
{
	ngimu_command( h, &(h->ngimu_ack_default), "/default", "", NULL, 0, NULL, 0, NULL, 0 );
}


void ngimu_command_ahrs_initialise( ngimu_t *h )
{
	ngimu_command( h, &(h->ngimu_ack_ahrs_initialise), "/ahrs/initialise", "", NULL, 0, NULL, 0, NULL, 0 );
}


void ngimu_command_ahrs_zero( ngimu_t *h )
{
	ngimu_command( h, &(h->ngimu_ack_ahrs_zero), "/ahrs/zero", "", NULL, 0, NULL, 0, NULL, 0 );
}


void ngimu_command_echo( ngimu_t *h, char *sarg, int iarg, float farg )
{
	ngimu_command( h, &(h->ngimu_ack_echo), "/echo", "sif", &sarg, 1, &iarg, 1, &farg, 1 );
}


