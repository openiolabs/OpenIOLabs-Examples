## @file
#  @package devsysfs
#
#  @brief Access to /dev and /sys nodes
#
# General:
#
# This is the correct API to use for device drivers when accessing these 
# nodes under /dev or /sys. Other "file" APIs may not be able to access 
# these nodes in the correct manner.
#
# There is a class-based interface which holds the device file open while
# the driver class instance exists, and alternative free functions 
# that open the device, act, and close it again. the latter are termed 
# "monolithic" and begin with mono_.
#
# Read and write operations work with lists of byte data only (numpy.uint8 or
# numpy.int8). The variants containing _block are for intended for block 
# devices and use pread() and pwrite(). The others use read() and write()
# are meant for character devices. This correspondance is not strict
# and some devices don't really correspond to block or character idioms.
#
# The ioctl can accept data structures made up of pointers, arrays and 
# structs, and converts them to and from a memory-based form for use
# with the underlying ioctl operation. Alignment padding is generated
# consistent with the C++11 cross-compiler used to build the scriptml
# interpreter.
#
# Python:
#
# The python version of ioctl uses lists populated with numpy types
# such as numpy.uint8 and so on in lieu of structs. Free function
# block() is provided to create a C pointer to a list. This should be 
# used to seperate contiguous blocks of data (where the ioctl's data 
# structure requirement is to use a pointer). Otherwise, nested lists 
# are concatenated into a single block, as with C structures. 
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#
 
## @brief Dev node or sysfs node class
#
# Instantiate one of these for each node you wish to hold open for access
class device:
	##
	#  @brief Open a device. 
	#
	#  @param path path to device
	#
	def __init__( self, path ):
		self.dev = ___Construct( object_type=___DevSysfsDeviceType(), args_list=___ArgsList(args=___ISeq(path)), args_map=___ArgsMap(args=___IMap()), variadic_arg=___NULL() )

	##
	#  @brief Write to device
	#
	#  @param device device object
	#  @param data data to write to the device
	#
	def write( self, data ):
		___Write( device=self.dev, pos=___NULL(), data=data )
	 
	 	 
	##
	#  @brief Write a block of data to device
	#
	#  @param device device object
	#  @param pos position of start of block
	#  @param data data to write to the device
	#
	def write_block( self, pos, data ):
		___Write( device=self.dev, pos=pos, data=data )
	 	 	
	 	 
	##
	#  @brief Read from device until EOF
	#
	#  @return Data read from device
	#
	def read_to_eof( self ):
		return ___Read( device=self.dev, pos=___NULL(), len=___NULL() )
	 
	 
	##
	#  @brief Read a number of bytes from device
	#
	#  @param len Number of bytes
	#  @return Data read from device
	#
	def read( self, len ):
		return ___Read( device=self.dev, pos=___NULL(), len=len )
	 
	 
	##
	#  @brief Read a block of data from device
	#
	#  @param pos Position of start of block
	#  @param len Number of bytes
	#  @return Data read from device
	#
	def read_block( self, pos, len ):
		return ___Read( device=self.dev, pos=pos, len=len )
	 

	##
	#  @brief Read a block of data from device up to end of file
	#
	#  @param pos Position of start of block
	#  @return Data read from device
	#
	def read_block_to_eof( self, pos ):
		return ___Read( device=self.dev, pos=pos, len=___NULL() )
	 

	##
	#  @brief Perform ioctl on device
	#
	#  @param request Ioctl request code
	#  @param data Input data block
	#  @return Output data block
	#
	# data is usually a data block returned by the block() function, except
	# in a few cases where a fundamental type such as "int" is used directly.
	#
	def ioctl( self, request, data ):
		___Ioctl( device=self.dev, request=request, data=data )
		return data 
	 	 
	 	 
##
#  @brief Monolithic write to device
#
#  @param path Path to device
#  @param data Data to write to the device
#
def mono_write( path, data ):
	device( path ).write( data )
	 
	 	 
##
#  @brief Monolithic write a block of data to device
#
#  @param path Path to device
#  @param pos Position of start of block
#  @param data Data to write to the device
#
def mono_write_block( path, pos, data ):
	device( path ).write_block( pos, data )
	 	 	
	 	 
##
#  @brief Monolithic read from device until EOF
#
#  @param path Path to device
#  @return Data read from device
#
def mono_read_to_eof( path ):
	return device( path ).read_to_eof()
	 
	 
##
#  @brief Monolithic read a number of bytes from device
#
#  @param path Path to device
#  @param len Number of bytes
#  @return Data read from device
#
def mono_read( path, len ):
	return device( path ).read( len )
	 
	 
##
#  @brief Monolithic read a block of data from device
#
#  @param path Path to device
#  @param pos Position of start of block
#  @param len Number of bytes
#  @return Data read from device
#
def mono_read_block( path, pos, len ):
	return device( path ).read_block( pos, len )
	 

##
#  @brief Perform monolithic ioctl on device
#
#  @param path Path to device
#  @param request Ioctl request code
#  @param data Input data block
#  @return Output data block
#
# data is usually a data block returned by the block() function, except
# in a few cases where a fundamental type such as "int" is used directly.
#
def mono_ioctl( path, request, data ):
	return device( path ).ioctl( request, data )
	 	 
	 	 
##
#  @brief Create an ioctl data block for CLib access
#
#  @param x The data structure to place in a block
#  @return An object that may be embedded in other blocks or passed to CLib intrinsics
#
# The return value is in fact a C-style pointer, with automatic garbage collection.
# Pass in None to produce a NULL pointer (the None object cannot be converted for
# CLib access).
#
def block(x):
    if x is None:
        return ___PointerExpr( target=___NULL() )
    else:
        return ___PointerExpr( target=x )
	 	
