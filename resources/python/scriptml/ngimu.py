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
	
def _handler( data, path, ints, floats, strings ):
	# data is the instance of "device" class
	data.handler( path, ints, floats, strings )
	
class device:
	##
	# @brief Open NGIMU connection
	#
	# @param handler OSC message handler function
	# @param my_port Handler is called for messages incoming on this port
	# @param device_ip IP address of the device
	# @param device_port Port on device to send messages to
	# @param data A user data object that is passed to the handler
	#
	def __init__( self, my_port, device_ip, device_port, user ):
		self.device_ip = device_ip
		self.user = user
		self.acks = {}
		self.acks["mute"] = False
		self.acks["unmute"] = False
		self.acks["reset"] = False
		self.acks["sleep"] = False
		self.acks["identify"] = False
		self.acks["apply"] = False
		self.acks["default"] = False
		self.acks["ahrs_initialise"] = False
		self.acks["ahrs_zero"] = False
		self.acks["echo"] = False
		self.read_ack = False
		self.read_path = None
		osc.init( _handler, my_port, device_ip, device_port, self )

	def handler( self, path, ints, floats, strings ):
		if path == "/buttons":
			handle_buttons( self.user )
		elif path == "/sensors":
			handle_sensors( self.user, floats[0], floats[1], floats[2], floats[3], floats[4], floats[5], floats[6], floats[7], floats[8], floats[9] )
		elif path=="/magnitudes":
			handle_magnitudes( self.user, floats[0], floats[1], floats[2] )
		elif path=="/quaternion":
			handle_quaternion( self.user, floats[0], floats[1], floats[2], floats[3] )
		elif path=="/matrix":
			handle_matrix( self.user, floats[0], floats[1], floats[2], floats[3], floats[4], floats[5], floats[6], floats[7], floats[8] )
		elif path=="/euler":
			handle_euler( self.user, floats[0], floats[1], floats[2] )
		elif path=="/linear":
			handle_linear( self.user, floats[0], floats[1], floats[2] )
		elif path=="/earth":
			handle_earth( self.user, floats[0], floats[1], floats[2] )
		elif path=="/altitude":
			handle_altitude( self.user, floats[0] )
		elif path=="/temperature":
			handle_temperature( self.user, floats[0], floats[1], floats[2] )
		elif path=="/humidity":
			handle_humidity( self.user, floats[0] )
		elif path=="/battery":
			handle_battery( self.user, floats[0], floats[1], floats[2], floats[3], strings[0] ) 
		elif path=="/analogue":
			handle_analogue( self.user, floats[0], floats[1], floats[2], floats[3], floats[4], floats[5], floats[6], floats[7] ) 
		elif path=="/rssi":
			handle_rssi( self.user, floats[0], floats[1] ) 
		elif path=="/auxserial":
			handle_auxserial( self.user, strings[0] ) 
		elif path=="/auxserial/cts":
			handle_auxserial_cts( self.user, ints[0] ) 
		elif path=="/serial/cts":
			handle_serial_cts( self.user, ints[0] ) 
		elif path=="/mute":
			self.acks["mute"] = True
		elif path=="/unmute": 
			self.acks["unmute"] = True
		elif path=="/reset": 
			self.acks["reset"] = True
		elif path=="/sleep": 
			self.acks["sleep"] = True
		elif path=="/identify": 
			self.acks["identify"] = True
		elif path=="/apply": 
			self.acks["apply"] = True
		elif path=="/default": 
			self.acks["default"] = True
		elif path=="/ahrs/initialise": 
			self.acks["ahrs_initialise"] = True
		elif path=="/ahrs/zero": 
			self.acks["ahrs_zero"] = True
		elif path=="/echo": 
			self.acks["echo"] = True
		elif self.read_path is not None and path==self.read_path: 
			self.read_ints =  ints
			self.read_floats = floats
			self.read_strings = strings
			self.read_ack = True
			self.read_path = None

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
	#
	def command( self, ack_flag, path, types, sargv, iargv, fargv ):
		self.send( path, types, sargv, iargv, fargv )
		while self.acks[ack_flag] == False:
			pass
		self.acks[ack_flag] = False

	##
	# @brief Send a message to the NGIMU
	#
	# @param path OSC-defined path to the resource to read (a string separated by /)
	# @return a tuple made up of (list of strings, list of integers, list of floats)
	#
	def read_setting( self, path ):
		self.read_path = path
		self.send( path, "", [], [], [] )
		while self.read_ack == False:
			pass
		self.read_ack = False
		return (self.read_strings, self.read_ints, self.read_floats)

	##
	# @brief Send "mute" command to NGIMU
	#
	def command_mute(self):
		self.command( "mute", "/mute", "", [], [], [] )

	##
	# @brief Send "unmute" command to NGIMU
	#
	def command_unmute(self):
		self.command( "unmute", "/unmute", "", [], [], [] )

	##
	# @brief Send "reset" command to NGIMU
	#
	def command_reset(self):
		self.command( "reset", "/reset", "", [], [], [] )

	##
	# @brief Send "sleep" command to NGIMU
	#
	def command_sleep(self):
		self.command( "sleep", "/sleep", "", [], [], [] )

	##
	# @brief Send "identify" command to NGIMU
	#
	def command_identify(self):
		self.command( "identify", "/identify", "", [], [], [] )

	##
	# @brief Send "apply" command to NGIMU
	#
	def command_apply(self):
		self.command( "apply", "/apply", "", [], [], [] )

	##
	# @brief Send "default" command to NGIMU
	#
	def command_default(self):
		self.command( "default", "/default", "", [], [], [] )

	##
	# @brief Send "ahrs_initialise" command to NGIMU
	#
	def command_ahrs_initialise(self):
		self.command( "ahrs_initialise", "/ahrs/initialise", "", [], [], [] )

	##
	# @brief Send "ahrs_zero" command to NGIMU
	#
	def command_ahrs_zero(self):
		self.command( "ahrs_zero", "/ahrs/zero", "", [], [], [] )

	##
	# @brief Send "echo" command to NGIMU
	# @param sarg String argument
	# @param iarg Integer argument 
	# @param farg Floating-point argument
	#
	def command_echo( self, sarg, iarg, farg ):
		self.command( "echo", "/echo", "sif", [sarg], [iarg], [farg] )

	##
	# @brief Set the update rate of a channel of data
	# @param channel The kind of data to send, eg "sensors", "magnitudes" etc
	# @param rate the new rate in Hertz
	#
	def set_rate( self, channel, rate ):
		self.send( "/rate/"+channel, "f", [], [], [rate] ) 
