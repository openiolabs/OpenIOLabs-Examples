import gpio
import time
import coroutines

led = gpio.device("17")
led.set_direction( gpio.OUT )

button = gpio.device("20")
button.set_direction( gpio.IN )

coroutines.wait( lambda: button.get_level() )
# Could alternatively use coroutines.wait( button.get_level )
# but lambda is more flexible
	
print "button pressed"

led.set_level( 1 )
time.sleep(1)
led.set_level( 0 )

# for these "device" objects, deleting by hand is recommended when finished with them
del led
del button
