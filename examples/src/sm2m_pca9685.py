import lwm2m # lwm2m.h is auto-generated
import i2c
import gpio
import pca9685
import time
from numpy import *

# Hookup details 
I2C_DEV_PATH = "/dev/i2c-1"
ADDR_OFFSET = 0x38
NUM_LEDS = 16

# Define instances of the LWM2M objects 
Light_Controls = []
for i in range(NUM_LEDS):
    Light_Controls += [lwm2m.create_IPSO_Light_Control()]

# Register the LWM2M objects with the Server 
lwm2m.register_object_id(lambda: Light_Controls, lwm2m.id_IPSO_Light_Control)

# Create the device objects 
i2c_bus = i2c.device( I2C_DEV_PATH ) # This is the I2C bus
device = pca9685.device( i2c_bus, ADDR_OFFSET ) # Addr pin set low

# Configure device: restart disabled, internal clk, auto-inc, power-up, subaddresses disabled, all-call enabled
device.set_mode1( 0, 0, 1, 0, 0, 0, 0, 1 )
time.sleep(0.0005)

# Configure device: restart enabled, internal clk, auto-inc, power-up, subaddresses disabled, all-call enabled
device.set_mode1( 1, 0, 1, 0, 0, 0, 0, 1 )
device.set_mode2( 0, pca9685.MODE2_OCH_ACK, pca9685.MODE2_OUTDRV_TOTEM_POLE, pca9685.MODE2_OUTNE_0 )
device.set_all_led_on_off( 0, 0, 0, 0 )

# Continually read the device and update the LWM2M object 
while True:
    for i in range(NUM_LEDS):      
        on_count = i*4096/16 # Distribute phasing to minimise power supply burst loading
        off_count = (on_count + (Light_Controls[i][lwm2m.IPSO_Light_Control_Dimmer]*4096+50)/100) % 4096
        full_on = Light_Controls[i][lwm2m.IPSO_Light_Control_OnOff] and Light_Controls[i][lwm2m.IPSO_Light_Control_Dimmer]==100
        full_off = (not Light_Controls[i][lwm2m.IPSO_Light_Control_OnOff]) or Light_Controls[i][lwm2m.IPSO_Light_Control_Dimmer]==0
        device.set_led_on_off( i, on_count, full_on, off_count, full_off )
    time.sleep(0.1)
