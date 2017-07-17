import max518
import i2c

dac = max518.device( i2c.device("/dev/i2c-1"), 0 )

while True:
	for l in range(256):
		dac.set_level( 0, l )
		dac.set_level( 1, 255-l )
	for l in range(255, 0, -1):
		dac.set_level( 0, l )
		dac.set_level( 1, 255-l )

del dac
