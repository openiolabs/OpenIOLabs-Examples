import i2c
import gpio
import pcf8574
from numpy import *

# It is better to let the main program explicitly create the 
# i2c and gpio objects, because that way alternatives can be 
# use without needing to change the pcf8574 driver
io_extender = pcf8574.device( i2c.device("/dev/i2c-1"), # i2c bus
                              0, # address offset (setting on Ax pins)
                              gpio.device("21") ) # GPIO pin for nint

io_extender.set_direction( 0x03 ) # iiiiiioo

print io_extender.get_level()
io_extender.set_level( 3 ) # flash P0 and P1
io_extender.wait_any_change() # await first change
print io_extender.get_level()
io_extender.set_level( 1 ) # flash P0 and P1
io_extender.wait_any_change() # await second change
print io_extender.get_level()
io_extender.set_level( 0 ) # flash P0 and P1
io_extender.wait_any_change() # await third change
print io_extender.get_level()
io_extender.set_level( 2 ) # flash P0 and P1

del io_extender

# Note: it is interesting to run this with --trace on, which slows
# it down enough to be able to see the flashes on the interrupt
# line (if you have an LED on it)


