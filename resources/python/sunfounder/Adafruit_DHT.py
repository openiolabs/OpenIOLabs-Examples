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

def read_retry(sensor, humiture):
	print "Reading", sensor, humiture
	return 30.0, 80.0
