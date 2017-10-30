import i2c
import ad7991
import max518
import time
import lwm2m

# Instantiate the motor, ADC and DAC device
adc = ad7991.device( i2c.device("/dev/i2c-1"), 0)
dac = max518.device( i2c.device("/dev/i2c-1"), 0 )
my_motor = lwm2m.create_OpenIO_Motor_Control()

# Register the motor with the server
lwm2m.register_object_id(lambda: my_motor, lwm2m.id_OpenIO_Motor_Control)  
# ... my_motor is now externally readable and modifiable	    


# Set the number of ADC channels
adc.set_channel(ad7991.TWO_CHAN)

i = 0;

while True:

    # Set the DAC levels in opposite directions
    dac.set_level( 0, i )
    dac.set_level( 1, 255-i )
    
    # Allow time for the loop
    time.sleep(1)
    
    # Get the value for channel 0
    channel, value = adc.get_level()
    print ('Channel = ' + channel + ' ADC value = ' + value + ' DAC value = ' + i)

    # Get the value for channel 1
    channel, value = adc.get_level()
    print ('Channel = ' + channel + ' ADC value = ' + value + ' DAC value = ' + str(255-i))
    
    # If the motor is active update its velocity with the ADC value
    if my_motor[lwm2m.OpenIO_Motor_Control_State]:

        my_motor[lwm2m.OpenIO_Motor_Control_Velocity] = value
    
    # Increment DAC value
    i = i + 1

# Destroy the devices
del adc
del dac
del my_motor
