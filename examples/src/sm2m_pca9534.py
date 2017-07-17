import lwm2m # lwm2m.h is auto-generated
import i2c
import gpio
import pca9534
import time
from numpy import *

# Hookup details 
I2C_DEV_PATH = "/dev/i2c-1"
ADDR_OFFSET = 0
NUM_INS = 4
NUM_OUTS = 4
GPIO_NUM = 21 # TODO fill in correctly

# Define instances of the LWM2M objects 
Inputs = []
for i in range(NUM_INS):
    Inputs += [lwm2m.create_IPSO_Digital_Input()]
Outputs = []
for i in range(NUM_OUTS):
    Outputs += [lwm2m.create_IPSO_Digital_Output()]

# Register the LWM2M objects with the Server 
lwm2m.register_object_id(lambda: Inputs, lwm2m.id_IPSO_Digital_Input)
lwm2m.register_object_id(lambda: Outputs, lwm2m.id_IPSO_Digital_Output)

# Create the device objects 
i2c_bus = i2c.device( I2C_DEV_PATH ) # This is the I2C bus
intr_pin = gpio.device( GPIO_NUM ) # GPIO that the interrupt pin is wired to    
device = pca9534.device( i2c_bus, ADDR_OFFSET, intr_pin ) 

# Configure device: restart disabled, internal clk, auto-inc, power-up, subaddresses disabled, all-call enabled
device.set_configuration( (1<<NUM_INS)-1 ) # lower pins as ins, upper as outs

# Continually read the device and update the LWM2M object 
while True:
    # Process inputs
    data = device.get_input()
    for i in range(NUM_INS):
        Inputs[i][lwm2m.IPSO_Digital_Input_Digital_Input_State] = (data>>i) & 1
        
    # Process outputs
    data = 0
    for i in range(NUM_OUTS):
        data |= Outputs[i][lwm2m.IPSO_Digital_Output_Digital_Output_State] << (i+NUM_INS)
    device.set_output( data )
      
    time.sleep(0.1)
