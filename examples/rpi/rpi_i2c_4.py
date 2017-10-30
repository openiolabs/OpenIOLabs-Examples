import i2c
import ad5242
import pcf8591
import time

bus = i2c.device("/dev/i2c-1")
pot = ad5242.device( bus, 0 )
adc = pcf8591.device( bus, 0, pcf8591.FOUR_SINGLE )

# Try out the ADC's digital out and the DAC feature of the ADC
adc.enable_output( True )
adc.set_level(255)
pot.set_position( 0, 0, 3 )
time.sleep(1)
adc.set_level(0)
pot.set_position( 0, 0, 0 )
time.sleep(1)

# Now ramp the pot and monitor the ADC return
adc.enable_output( False )
for i in range(256):
	pot.set_position( 0, i )
	time.sleep(0.1)
	print i, adc.get_level( 0 )
	time.sleep(0.1)

del pot, adc, bus

