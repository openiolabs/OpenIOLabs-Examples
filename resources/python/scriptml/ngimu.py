## @file
#
# @brief X-IO NGIMU (NExt Generation Inertial M<anagement Unit) driver layer
#
# General:
#
# This driver controls and receives messages from the NGIMU unit, using OSC 
# for communication. Incoming messages are handled by implementing handler 
# functions matching the calls made from the handler() member function in 
# the device class.
#
# Commands are implemented directly in member functions named command_x(). These
# methods block until an ack is received.
#
# Other sends should use the send() method with arguments gien according to
# the documentation for osc.py.
#
# Copyright (c) Open IO Labs Ltd 2017
# All Rights Reserved
#

import osc	
import time
		
class device:
	##
	# @brief Open NGIMU connection
	#
	# @param my_port Handler is called for messages incoming on this port
	# @param device_ip IP address of the device
	# @param device_port Port on device to send messages to
	# @param user A user data object that is passed to the handlers
	# @param timeout command ack timeout in seconds 
	#
	def __init__( self, my_port, device_ip, device_port, user, timeout ):
		self.device_ip = device_ip
		self.user = user
		self.acks = {}
		self.acks["/mute"] = False
		self.acks["/unmute"] = False
		self.acks["/reset"] = False
		self.acks["/sleep"] = False
		self.acks["/identify"] = False
		self.acks["/apply"] = False
		self.acks["/default"] = False
		self.acks["/ahrs/initialise"] = False
		self.acks["/ahrs/zero"] = False
		self.acks["/echo"] = False
		self.inmap = {}
		self.inmap["/buttons"] = handle_buttons
		self.inmap["/sensors"] = handle_sensors
		self.inmap["/magnitudes"] = handle_magnitudes
		self.inmap["/quaternion"] = handle_quaternion
		self.inmap["/matrix"] = handle_matrix
		self.inmap["/euler"] = handle_euler
		self.inmap["/linear"] = handle_linear
		self.inmap["/earth"] = handle_earth
		self.inmap["/altitude"] = handle_altitude
		self.inmap["/temperature"] = handle_temperature
		self.inmap["/humidity"] = handle_humidity
		self.inmap["/battery"] = handle_battery
		self.inmap["/analogue"] = handle_analogue
		self.inmap["/rssi"] = handle_rssi
		self.inmap["/auxserial"] = handle_auxserial
		self.inmap["/auxserial/cts"] = handle_auxserial_cts
		self.inmap["/serial/cts"] = handle_serial_cts
		self.read_ack = False
		self.read_path = None
		self.timeout = timeout
		osc.init( _handler, my_port, device_ip, device_port, self )

	##
	# @brief Send a message to the NGIMU
	#
	# @param path OSC-defined path to the resource to write (a string separated by /)
	# @param types OSC-defined types of the parameters of the message
	# @param sargv String arguments referenced by types argument, in their own order
	# @param iargv Integer arguments referenced by types argument, in their own order
	# @param fargv Floating-point arguments referenced by types argument, in their own order
	#
	def send( self, path, types, sargv, iargv, fargv ):
		osc.send_message( self.device_ip, path, types, sargv, iargv, fargv )

	##
	# @brief Send a message to the NGIMU
	#
	# @param path OSC-defined path to the resource to write (a string separated by /)
	# @param ack_flag index into self.acks map - blocks until this flag is True
	# @param types OSC-defined types of the parameters of the message
	# @param sargv String arguments referenced by types argument, in their own order
	# @param iargv Integer arguments referenced by types argument, in their own order
	# @param fargv Floating-point arguments referenced by types argument, in their own order
	# @return True if successful or False if timed out
	#
	def command( self, path, types, sargv, iargv, fargv ):
		self.send( path, types, sargv, iargv, fargv )
		time_limit = time.time() + self.timeout
		while self.acks[path] == False and time.time() < time_limit:
			pass
		ok = self.acks[path]
		self.acks[path] = False
		return ok

	##
	# @brief Send a message to the NGIMU
	#
	# @param path OSC-defined path to the resource to read (a string separated by /)
	# @return a tuple made up of (list of strings, list of integers, list of floats) or None if timeout
	#
	def read_setting( self, path ):
		self.read_path = path
		self.send( path, "", [], [], [] )
		time_limit = time.time() + self.timeout
		while self.read_ack == False and time.time() < time_limit:
			pass
		ok = self.read_ack
		self.read_ack = False
		return (self.read_strings, self.read_ints, self.read_floats) if ok else None

	##
	# @brief Send "mute" command to NGIMU
	#
	# @return True if successful or False if timed out
	#
	def command_mute(self):
		return self.command( "/mute", "", [], [], [] )

	##
	# @brief Send "unmute" command to NGIMU
	#
	# @return True if successful or False if timed out
	#
	def command_unmute(self):
		return self.command( "/unmute", "", [], [], [] )

	##
	# @brief Send "reset" command to NGIMU
	#
	# @return True if successful or False if timed out
	#
	def command_reset(self):
		return self.command( "/reset", "", [], [], [] )

	##
	# @brief Send "sleep" command to NGIMU
	#
	# @return True if successful or False if timed out
	#
	def command_sleep(self):
		return self.command( "/sleep", "", [], [], [] )

	##
	# @brief Send "identify" command to NGIMU
	#
	# @return True if successful or False if timed out
	#
	def command_identify(self):
		return self.command( "/identify", "", [], [], [] )

	##
	# @brief Send "apply" command to NGIMU
	#
	# @return True if successful or False if timed out
	#
	def command_apply(self):
		return self.command( "/apply", "", [], [], [] )

	##
	# @brief Send "default" command to NGIMU
	#
	# @return True if successful or False if timed out
	#
	def command_default(self):
		return self.command( "/default", "", [], [], [] )

	##
	# @brief Send "ahrs_initialise" command to NGIMU
	#
	# @return True if successful or False if timed out
	#
	def command_ahrs_initialise(self):
		return self.command( "/ahrs/initialise", "", [], [], [] )

	##
	# @brief Send "ahrs_zero" command to NGIMU
	#
	# @return True if successful or False if timed out
	#
	def command_ahrs_zero(self):
		return self.command( "/ahrs/zero", "", [], [], [] )

	##
	# @brief Send "echo" command to NGIMU
	#
	# @return True if successful or False if timed out
	#
	def command_echo( self ):
		return self.command( "/echo", "", [], [], [] )

	##
	# @brief Set the update rate of a channel of data
	# @param channel The kind of data to send, eg "sensors", "magnitudes" etc
	# @param rate the new rate in Hertz
	#
	def set_rate( self, channel, rate ):
		self.send( "/rate/"+channel, "f", [], [], [rate] ) 
		
		
def _handler( data, path, ints, floats, strings ):
	if path in data.inmap:			
		(data.inmap[path])( data.user, *(ints + floats + strings) )
	elif path in data.acks:
		data.acks[path] = True
	elif data.read_path is not None and path==data.read_path: 
		data.read_ints =  ints
		data.read_floats = floats
		data.read_strings = strings
		data.read_ack = True
		data.read_path = None
		
