import i2c
import ad7991
import time
import lwm2m

# Instantiate the device
adc = ad7991.device( i2c.device("/dev/i2c-1"), 0)

#Create the device on the server
my_adc = [lwm2m.create_IPSO_Analog_Input(), lwm2m.create_IPSO_Analog_Input()]

#Register the ADC with the server
lwm2m.register_object_id(lambda: my_adc, lwm2m.id_IPSO_Analog_Input)

# Set the number of ADC channels
adc.set_channel(ad7991.TWO_CHAN)

counter =0
while True:
	channel = 0
	# Get the value for channel 0
	channel0, value0 = adc.get_level()
	print ('Channel = ' + channel0 + ' ADC value0 = ' + value0)
	
	channel = 1
	# Get the value for channel 1
	channel1, value1 = adc.get_level()
	print ('Channel = ' + channel1 + ' ADC value1 = ' + value1)
	
	# Update ADC value to the server
	my_adc[0][lwm2m.IPSO_Analog_Input_Analog_Input_Current_Value] = value0
	my_adc[1][lwm2m.IPSO_Analog_Input_Analog_Input_Current_Value] = value1
	
	print ( 'Counter = ' + counter )
	counter = counter + 1
	# Allow time for the loop
	time.sleep(1)

# Destroy the device
#del adc
