import i2c
import ad7991
import max518
import time

# Instantiate the ADC and DAC device
adc = ad7991.device( i2c.device("/dev/i2c-1"), 0)
dac = max518.device( i2c.device("/dev/i2c-1"), 0 )

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
    
    # Increment DAC value
    i = i + 1

# Destroy the device
del adc
