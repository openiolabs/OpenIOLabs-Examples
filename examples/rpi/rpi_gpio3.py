import gpio
import time
import coroutines

def f(hled, stop):
	while not stop[0]:
		hled.set_level( 1 )
		time.sleep(1)
		hled.set_level( 0 )
		time.sleep(1)

hled = gpio.device("17");
hled.set_direction( gpio.OUT )

hbutton = gpio.device("20");
hbutton.set_direction( gpio.IN )

stop = [0]
led_coroutine = coroutines.coroutine(f, [hled, stop])

coroutines.wait( lambda: hbutton.get_level() )
	
print "button pressed"

stop[0] = 1
led_coroutine.join()

print "done"

del hled
del hbutton	
	
