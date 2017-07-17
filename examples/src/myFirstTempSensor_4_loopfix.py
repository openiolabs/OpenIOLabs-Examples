import i2c
import ad7991
import time
import lwm2m
"""This script is based on myFirstADC.py and motoMonitor.  It reads a channel on a AD7991 to read a signal from a
TMP35 Analog Temperature Sensor.  The AD7991 has two channels which are both regestered with the Labbook Server.
In this Example the 1st channel remains registered on the labBook as an ADC while the second channel is registered
as a temperaure sensor.  """

# Instantiate the device
adc = ad7991.device( i2c.device("/dev/i2c-1"), 0)

# Set the number of ADC channels
#adc.set_channel(ad7991.TWO_CHAN)
adc.set_channel(ad7991.FOUR_CHAN)


#Create the device on the labBook server
my_temp = [lwm2m.create_IPSO_Temperature(),
		  lwm2m.create_IPSO_Temperature(),
		  lwm2m.create_IPSO_Temperature(),
		  lwm2m.create_IPSO_Temperature()]

#  Produces error in ScrptML ?
number_of_sensors  = len(my_temp)
#number_of_sensors  = 3

#Register the device with the LabBook server
#They are registered on the LabBook server separately
lwm2m.register_object_id(lambda: my_temp, lwm2m.id_IPSO_Temperature)

#####################
## Temperature Object
#set some fixed parameters from the given sensor used and send to the LabBook
#these values were found in the sensor's data sheet:
# http://docs-europe.electrocomponents.com/webdocs/0ae1/0900766b80ae1656.pdf
# for the TMP35
my_temp_range_min = 0
my_temp_range_max  = 100

# for the TMP36
# my_temp_range_min = -40
# my_temp_range_max  = 125
#
#  Produces error in ScrptML ?
for t in my_temp:
    t[lwm2m.IPSO_Temperature_Min_Range_Value] = my_temp_range_min ##< Min Range Value; R; float
    t[lwm2m.IPSO_Temperature_Max_Range_Value] = my_temp_range_max ##< Max Range Value; R; float

#     # the sensor outputs a voltage that can be expressed in several units given calibration data
#     my_temp[i][lwm2m.IPSO_Temperature_Sensor_Units] = "C"  ##< Sensor Units; R; string

def mvolt_to_C(mv):
    T_in_C = (((mv) - 500) / 10)-15  # the 15 is a 'fudge' calibration factor #TODO fix this
    return T_in_C

# #TODO add min and max value capture
# def minmax_capture(value):
#     if value1 <= value1_min:
#         value1_min = value1
#         my_temp[lwm2m.IPSO_Temperature_Min_Measured_Value] = mvolt_to_C(value1_min)
#
#     else value1 => value1_max:
#         value1_max = value1
#         my_temp[lwm2m.IPSO_Temperature_Max_Measured_Value] = mvolt_to_C(value1_Max)

#  End Temperature ######################################


value1_min = 0
value1_max = 0
counter = 0

#in this section the data is read from the sensor.  Note at this point there is
# no relationship between the channels being read on the sensor and the channels on the LabBook
while True:
    channel = 0
    # Get the value for channel 0
    channel0, value0 = adc.get_level()
    print ('Channel0 = ' + channel0 + ' Temperature value0 = ' + mvolt_to_C(value0))

    channel = 1
    # Get the value for channel 1
    channel1, value1 = adc.get_level()
    print ('Channel1 = ' + channel1 + ' Temperature value1 = ' + mvolt_to_C(value1))

    channel = 2
    # Get the value for channel 1
    channel2, value2 = adc.get_level()
    print ('Channel2 = ' + channel2 + ' Temperature value2 = ' + mvolt_to_C(value2))

    channel = 3
    # Get the value for channel 1
    channel3, value3 = adc.get_level()
    print ('Channel3 = ' + channel3 + ' Temperature value3 =' + mvolt_to_C(value3))

#associate the data read from the sensor and the LabBook server channels
# Update device value to the server


#TODO loop this to beable to accommodate a large number of sensors :
    my_temp[0][lwm2m.IPSO_Temperature_Sensor_Value] = mvolt_to_C(value0)
    my_temp[1][lwm2m.IPSO_Temperature_Sensor_Value] = mvolt_to_C(value1)
    my_temp[2][lwm2m.IPSO_Temperature_Sensor_Value] = mvolt_to_C(value2)
    my_temp[3][lwm2m.IPSO_Temperature_Sensor_Value] = mvolt_to_C(value3)


    print ( 'Counter = ' + counter )
    counter = counter + 1
    # Allow time for the loop
    time.sleep(1)

# Destroy the device
#del adc
