/** @file
 *
 * @brief Access to /dev and /sys nodes
 *
 * General:
 *
 * This is the correct API to use for device drivers when accessing these 
 * nodes under /dev or /sys. Other "file" APIs may not be able to access 
 * these nodes in the correct manner.
 *
 * There is a class-based interface which holds the device file open while
 * the driver class instance exists, and alternative free functions 
 * that open the device, act, and close it again. the latter are termed 
 * "monolithic" and begin with mono_.
 *
 * Read and write operations work with lists of byte data only (numpy.uint8 or
 * numpy.int8). The variants containing _block are for intended for block 
 * devices and use pread() and pwrite(). The others use read() and write()
 * are meant for character devices. This correspondance is not strict
 * and some devices don't really correspond to block or character idioms.
 *
 * The ioctl can accept data structures made up of pointers, arrays and 
 * structs, and converts them to and from a memory-based form for use
 * with the underlying ioctl operation. Alignment padding is generated
 * consistent with the C++11 cross-compiler used to build the scriptml
 * interpreter.
 *
 * C:
 *
 * The C version of this file includes non-scriptML implementations for use
 * in reference builds for comaprative tests. They are automatically 
 * subsituted when ScriptML is not detected.
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __DEVICE_H
#define __DEVICE_H

#include <unistd.h>

// Internal helper for fixing the length of pointed-to arrays
#define FIX_LEN(P, L) P[ ___Range( start:0 , stop:(X), step:1 ) ]
#define VAR_ARRAY(T) ___ListType( element_type:T )


#ifdef __SCRIPTML
// Doing strings this way makes for slightly smaller scripts and faster
typedef ___StringType_T( size:___NULL() ) _str;
// OP-844 is to let this be a typedef
#define _data ___NULL_T()
#else
typedef char *_str;
typedef void *_data;
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

// Don't want to include <sys/ioctl.h> since scripts will likely define their own request codes. 
int ioctl(int d, int request, ...);

#define PAGE_SIZE 4096
#endif

#ifdef __SCRIPTML
typedef ___DevSysfsDeviceType_T() sml_devsysfs_t;
#else
typedef int sml_devsysfs_t;
#endif


/**
 *  @brief Open a device. Returns a handle.
 *
 *  @param path Path to device
 *  @return Device handle
 */
sml_devsysfs_t sml_devsysfs_open( _str path )
{ 
#ifdef __SCRIPTML
	return ___Construct( object_type:___DevSysfsDeviceType(), args_list:___ArgsList(args:___ISeq(path)), args_map:___ArgsMap(args:___IMap()), variadic_arg:___NULL() );
#else
    int fd = open(path, O_RDWR);
    if( fd < 0 )
    {
		printf("Failed to open %s: %s\n", path, strerror(errno));
		abort();
	}
	return fd;
#endif
}


/**
 *  @brief Close a device. 
 *
 *  @param dev Device handle
 */
void sml_devsysfs_close( sml_devsysfs_t dev )
{
#ifdef __SCRIPTML
#else
	int res = close(dev);
    if( res < 0 )
    {
		printf("Failed to close fd %d: %s\n", dev, strerror(errno));
		abort();
	}
#endif
}


/**
 *  @brief Write to device
 *
 *  @param dev Device handle
 *  @param data Data to write to the device
 */
void sml_devsysfs_write( sml_devsysfs_t dev, _data data )
{
#ifdef __SCRIPTML
	___Write( device:dev, pos:___NULL(), data:data );	
#else
    int res = write( dev, data, strlen(data) );
    if( res < 0 )
    {
		printf("Failed to write to fd %d: %s\n", dev, strerror(errno));
		abort();
	}
#endif
}

	 
/**
 *  @brief Write a block of data to device
 *
 *  @param dev Device handle
 *  @param pos Position of start of block
 *  @param data Data to write to the device
 */
void sml_devsysfs_write_block( sml_devsysfs_t dev, int pos, _data data )
{
#ifdef __SCRIPTML
	___Write( device:dev, pos:pos, data:data );	
#else
    int res = pwrite( dev, data, strlen(data), pos );
    if( res < 0 )
    {
		printf("Failed to write to fd %d: %s\n", dev, strerror(errno));
		abort();
	}
#endif
}	 


/**
 *  @brief Read a number of bytes from device
 *
 *  @param dev Device handle
 *  @param len Number of bytes
 *  @return Data read from device
 */
_data sml_devsysfs_read( sml_devsysfs_t dev, int len )
{
#ifdef __SCRIPTML
	return ___Read( device:dev, pos:___NULL(), len:len );	 
#else
	char *buf = (char *)malloc(len); // compromise for tests: scriptml has no problem here
    int res = read( dev, buf, len );
    if( res < 0 )
    {
		printf("Failed to read from fd %d: %s\n", dev, strerror(errno));
		abort();
	}
	return buf;
#endif
}
	
	 	 
/**
 *  @brief Read from device until EOF
 *
 *  @param dev Device handle
 *  @return Data read from device
 */
_data sml_devsysfs_read_to_eof( sml_devsysfs_t dev )
{
#ifdef __SCRIPTML
	return ___Read( device:dev, pos:___NULL(), len:___NULL() );		 
#else
	static char buf[PAGE_SIZE]; // compromise for tests: scriptml has no problem here
    int res = read( dev, buf, PAGE_SIZE );
    if( res < 0 )
    {
		printf("Failed to read from fd %d: %s\n", dev, strerror(errno));
		abort();
	}
	return buf;
#endif
}

	 	 
/**
 *  @brief Read a block of data from device
 *
 *  @param dev Device handle
 *  @param pos Position of start of block
 *  @param len Number of bytes
 *  @return Data read from device
 */
_data sml_devsysfs_read_block( sml_devsysfs_t dev, int pos, int len )
{
#ifdef __SCRIPTML
	return ___Read( device:dev, pos:pos, len:len );		 
#else
	char *buf = (char *)malloc(len); // compromise for tests: scriptml has no problem here
    int res = pread( dev, buf, len, pos );
    if( res < 0 )
    {
		printf("Failed to read from fd %d: %s\n", dev, strerror(errno));
		abort();
	}
	return buf;
#endif
}
	 	 
	 	 
/**
 *  @brief Read a block of data from device until end of file
 *
 *  @param dev Device handle
 *  @param pos Position of start of block
 *  @return Data read from device
 */
_data sml_devsysfs_read_block_to_eof( sml_devsysfs_t dev, int pos )
{
#ifdef __SCRIPTML
	return ___Read( device:dev, pos:pos, len:___NULL() );		 
#else
	static char buf[PAGE_SIZE]; // compromise for tests: scriptml has no problem here
    int res = pread( dev, buf, PAGE_SIZE, pos );
    if( res < 0 )
    {
		printf("Failed to read from fd %d: %s\n", dev, strerror(errno));
		abort();
	}
	return buf;
#endif
}
	 	 
/**
 *  @brief Perform ioctl on device
 *
 *  @param dev Device handle
 *  @param request Ioctl request code
 *  @param data Pointer to data block, used as input and output
 */
void sml_devsysfs_ioctl( sml_devsysfs_t dev, unsigned request, _data data )
{
#ifdef __SCRIPTML
	___Ioctl( device:dev, request:request, data:data );	
#else
    int res = ioctl( dev, request, data );
    if( res < 0 )
    {
		printf("Failed to ioctl 0x%x: %s\n", request, strerror(errno));
		abort();
	}
#endif	 
}	 


/**
 *  @brief Monolithic write to device
 *
 *  @param path Path to device
 *  @param data Data to write to the device
 */
void sml_devsysfs_mono_write( _str path, _data data )
{
	sml_devsysfs_t d = sml_devsysfs_open( path );
	sml_devsysfs_write( d, data );	
	sml_devsysfs_close( d );
}	 
	 
	 	 
/**
 *  @brief Monolithic write a block of data to device
 *
 *  @param path Path to device
 *  @param pos Position of start of block
 *  @param data Data to write to the device
 */
void sml_devsysfs_mono_write_block( _str path, int pos, _data data )
{
	sml_devsysfs_t d = sml_devsysfs_open( path );
	sml_devsysfs_write_block( d, pos, data );	
	sml_devsysfs_close( d );
}	 
	 	 

/**
 *  @brief Monolithic read from device until EOF
 *
 *  @param path Path to device
 *  @return Data read from device
 */
_str sml_devsysfs_mono_read_to_eof( _str path )
{
	sml_devsysfs_t d = sml_devsysfs_open( path );
	_str data = sml_devsysfs_read_to_eof( d );	
	sml_devsysfs_close( d );
	return data;
}	 
	 	 	 	 
/**
 *  @brief Monolithic read a number of bytes from device
 *
 *  @param path Path to device
 *  @param len Number of bytes
 *  @return Data read from device
 */
_str sml_devsysfs_mono_read( _str path, int len )
{
	sml_devsysfs_t d = sml_devsysfs_open( path );
	_str data = sml_devsysfs_read( d, len );	
	sml_devsysfs_close( d );
	return data;
}	 
	
	 	 
/**
 *  @brief Monolithic read a block of data from device
 *
 *  @param path Path to device
 *  @param pos Position of start of block
 *  @param len Number of bytes
 *  @return Data read from device
 */
_str sml_devsysfs_mono_read_block( _str path, int pos, int len )
{
	sml_devsysfs_t d = sml_devsysfs_open( path );
	_str data = sml_devsysfs_read_block( d, pos, len );	
	sml_devsysfs_close( d );
	return data;
}	 

	 
/**
 *  @brief Perform monolithic ioctl on device
 *
 *  @param path Path to device
 *  @param request Ioctl request code
 *  @param data Pointer to data block, used as input and output
 */
void sml_devsysfs_mono_ioctl( _str path, unsigned long request, _data data )
{
	sml_devsysfs_t d = sml_devsysfs_open( path );
	sml_devsysfs_ioctl( d, request, data );
	sml_devsysfs_close( d );
}	 

#endif
 
