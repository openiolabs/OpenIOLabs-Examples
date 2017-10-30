# Standard LWM2M object and RPi required 
import lwm2m
import gpio

NUM_GPIOS = 3

gpio_map = ["21", "26", "17"]
gpio_dir = [ gpio.OUT, gpio.OUT, gpio.IN]
gpio_pin = [None, None, None]
my_motors = [None, None]

for i in range(NUM_GPIOS):
	gpio_pin[i] = gpio.device(gpio_map[i])
	gpio_pin[i].set_direction( gpio_dir[i] )

for i in range(2):
	my_motors[i] = lwm2m.create_OpenIO_Motor_Control()

lwm2m.register_object_id(lambda: my_motors, lwm2m.id_OpenIO_Motor_Control) # Register our objects with server 
# ... my_motor is now externally readable and modifiable	    

# Just keep on setting the GPIOs to the "state" resource of the objects (id=1)
while(1):
	for i in range(2):
		my_motors[i][lwm2m.OpenIO_Motor_Control_Direction] = gpio_pin[2].get_level()
		gpio_pin[i].set_level( my_motors[i][lwm2m.OpenIO_Motor_Control_State] )
