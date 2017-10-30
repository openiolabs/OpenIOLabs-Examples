import i2c
import ad7991
import time

# Instantiate the device
adc = ad7991.device( i2c.device("/dev/i2c-1"), 0)

# Set the number of ADC channels
adc.set_channel(ad7991.TWO_CHAN)

# Get the value for channel 0
channel, value = adc.get_level()
print ('Channel = ' + channel + ' ADC value = ' + value)

# Get the value for channel 1
channel, value = adc.get_level()
print ('Channel = ' + channel + ' ADC value = ' + value)

# Destroy the device
del adc