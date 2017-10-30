/** @file
 *
 * @brief Simple serial port driver
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __RPI_SERIAL_H
#define __RPI_SERIAL_H

#include <scriptml/devsysfs.h>
#include <unistd.h>

#ifndef __SCRIPTML
#error "This header file can only be used with ScriptML" 
#endif

typedef _str sml_serial_handle_t;

/**
 *  @brief Initialise access to the serial port
 *
 *  @return Device handle
 */
sml_serial_handle_t sml_serial_open()
{
	return "/dev/ttyAMA0"; // TODO or /dev/ttyS0 or /dev/serialx
}
	 
	 
/**
 *  @brief End access to the serial port
 */
void sml_serial_close()
{
}
	 

/**
 *  @brief Write to serial port
 *
 *  @param dev Device handle
 *  @param text Text to write to the port
 */
void sml_serial_write( sml_serial_handle_t dev, char * text )
{
	_str stext = text;
	sml_devsysfs_mono_write( dev, stext );	
}	 
	 
	 
/**
 *  @brief Read from serial port
 *
 *  @param dev Device handle
 *  @return Buffer for text read from port
 */
char *sml_serial_read( sml_serial_handle_t dev )
{
	_str stext = sml_devsysfs_mono_read_to_eof( dev );	
	return stext;
}	 
	 	 
#endif
 
