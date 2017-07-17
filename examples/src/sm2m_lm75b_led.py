import lwm2m # lwm2m.h is auto-generated
import i2c
import gpio
import lm75b
import time

time.sleep(1)

# Hookup details */
I2C_DEV_PATH = "/dev/i2c-1"
GPIO_NUM = "4"
ADDR_OFFSET = 0

RED_LED_GPIO_NUM = "17"
GREEN_LED_GPIO_NUM = "19"

LWM2M_IPSO_Temperature = lwm2m.create_IPSO_Temperature()

conv = 0.125 / 32.0 # Allow for the 5 zero-bits

# Initialise constant-valued resources
LWM2M_IPSO_Temperature[lwm2m.IPSO_Temperature_Sensor_Units] = "degrees C"
LWM2M_IPSO_Temperature[lwm2m.IPSO_Temperature_Min_Range_Value] = -32768.0*conv
LWM2M_IPSO_Temperature[lwm2m.IPSO_Temperature_Max_Range_Value] = 32768.0*conv
      
# Register the LWM2M objects with the Server
lwm2m.register_object_id(lambda: LWM2M_IPSO_Temperature, lwm2m.id_IPSO_Temperature)

# Create the device objects 
i2c_bus = i2c.device( I2C_DEV_PATH ) # This is the I2C bus
intr_pin = gpio.device( GPIO_NUM ) # GPIO that the interrupt pin is wired to    
thermometer = lm75b.device( i2c_bus, ADDR_OFFSET, intr_pin ) 

red_led_pin = gpio.device( RED_LED_GPIO_NUM ) # GPIO that the LED is wired to    
green_led_pin = gpio.device( GREEN_LED_GPIO_NUM ) # GPIO that the LED is wired to    
red_led_pin.set_direction( gpio.OUT )
green_led_pin.set_direction( gpio.OUT )

# Initialise the device 
thermometer.set_conf( lm75b.CONF_SHUTDOWN_NORMAL, lm75b.CONF_OS_COMP_INT_COMPARATOR, lm75b.CONF_OS_POL_ACTIVE_LOW, lm75b.CONF_OS_F_QUE_1 )

# Continually read the device and update the LWM2M object 
while True:
    temp = thermometer.get_temp() * conv
    LWM2M_IPSO_Temperature[lwm2m.IPSO_Temperature_Sensor_Value] = temp
    print temp
    
    # Light LED when temperature is rising
    if temp > 20.0:
        red_led_pin.set_level( 1 )
    else:
        red_led_pin.set_level( 0 )
    if temp < 25.0:
        green_led_pin.set_level( 1 )
    else:
        green_led_pin.set_level( 0 )
    time.sleep(1)

