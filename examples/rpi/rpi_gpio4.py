import gpio
import time
import coroutines

level = 0 # current brightness
time_resolution = 0.01 # in seconds
stop = False # shared flag saying when to stop

#
# This coroutine simply waits for a button press and then sets the shared
# stop variable, triggering all to exit
#
def button_coroutine_function(gpio_number):
	global stop
	global button # At present, lambdas can only refer to global names; task OP-797 is to remove this restriction
	print "Starting button"
	button = gpio.device(gpio_number)
	button.set_direction( gpio.IN )
	coroutines.wait( lambda: button.get_level() )
	stop = True
	print "Stopping button"
	del button	


#
# This coroutine handles the rotary encoder. It uses two nested loops
# to demonstrate imperative coding style. Inner just waits for a legitimate
# transition, and then exits to the outer loop which updates the level
#
def decode_coroutine_function(gpio_numbers):
	global level, stop
	global previous_reading, encoder # At present, lambdas can only refer to global names; task OP-797 is to remove this restriction
	print "Starting decoder"
	encoder = [gpio.device(gpio_numbers[0]), gpio.device(gpio_numbers[1])] # IC-352 will add comprehensions to make this and elsewhere cleaner
	encoder[0].set_direction( gpio.IN ) 
	encoder[1].set_direction( gpio.IN )
	previous_reading=[encoder[0].get_level(), encoder[1].get_level()]	
	while not stop:
		coroutines.wait( lambda: previous_reading[0]!=encoder[0].get_level() or previous_reading[1]!=encoder[1].get_level() or stop )
		reading = [encoder[0].get_level(), encoder[1].get_level()] # would rather "grab" 
		index = reading[0]+reading[1]*2+previous_reading[0]*4+previous_reading[1]*8
		decoded_delta = [0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0][index] # 0->1->3->2->0
		previous_reading = reading
		level += decoded_delta
		if level<0: 
			level = 0
		if level>10:
			level = 10		
		print "level now", level	
	print "Stopping decoder"
	del encoder[0], encoder[1]


#
# This coroutine handles the LED. It flashes on and off with a duty cycle set 
# by the rotary encoder. The flashing is done in a loop, so that it is
# straightforward to build arbitrarily complex control patterns. The call
# to time.sleep causes yields so we don't need to do this by hand
#
def pwm_coroutine_function(gpio_number):
	global level, stop
	print "Starting PWM"
	led = gpio.device( gpio_number )
	led.set_direction( gpio.OUT )
	while not stop:
		led.set_level( 1 )
		time.sleep(level*time_resolution)
		led.set_level( 0 )
		time.sleep((10-level)*time_resolution)
	print "Stopping PWM"
	del led


#
# Main program:
# Create the coroutines. For convenience, the actual GPIO numbers 
# are specified here, but the coroutines themselves deal with
# opening and closing the GPIO pins (for modularity)
#
print "Starting coroutines"
button_coroutine = coroutines.coroutine(button_coroutine_function, ["20"])
decode_coroutine = coroutines.coroutine(decode_coroutine_function, [["21", "22"]])
pwm_coroutine = coroutines.coroutine(pwm_coroutine_function, ["17"])

# Let the coroutines run
coroutines.wait( lambda: stop )

#
# Ensure a clean shutdown by waiting for the coroutines to finish
# You don't need this if you never plan to stop until power-off
#
print "Awaiting coroutine exit"
button_coroutine.join()
decode_coroutine.join()
pwm_coroutine.join()

print "Done"

	
