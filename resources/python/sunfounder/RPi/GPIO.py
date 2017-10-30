#
# ScriptML example hardware API
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

##
#  @file
#  @brief example hardware API
#
# Supports example code in third_party/rasberrypi/Sensor_Kit_V2.0_for_B_RPi2_andRPi3/SunFounder_SensorKit_for_RPi2/Python/

import comms

BOARD = "board"
BCM = "Broadcom"

OUT = 0
IN = 1

LOW = 0
HIGH = 1

RISING = 1
FALLING = 2
BOTH = 3

PUD_NONE = 0
PUD_UP = 1
PUD_DOWN = 2

def __callback():
	pass

def setmode( mode ):
	print "Setting the mode to", mode
	
def setup( pin, d, pull_up_down=0 ): # TODO default args as expressions
	print "Setting up pin", pin, "as", d
	
def add_event_detect( pin, edge, callback, bouncetime=0 ):
	print "Setting event", pin, edge, callback, bouncetime
	global __callback
	__callback = callback

def __GPIO_event():
	print "Got event, handler is", __callback
	__callback(1)

def cleanup():
	pass

def output( pin, l ):
	print "Setting pin", pin, l
	comms.Notify(l)
	
def input( pin ):
	print "Polling pin", pin
	return comms.ReadFromDevice( str(pin) )

class PWM:	
	def __init__( self, pin, freq ):
		self.pin = pin
		self.freq = freq
		print "Setting pin PWM", pin, "freq", freq
	
	def start( self, duty ):
		print "Starting PWM pin", self.pin, "duty", duty
		
	def stop( self ):
		print "Stopping PWM pin", self.pin	

__event = __GPIO_event
