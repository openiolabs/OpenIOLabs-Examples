import lwm2m # lwm2m.h is auto-generated
import i2c
import gpio
import isl29023
import time

# Hookup details 
I2C_DEV_PATH = "/dev/i2c-1"
GPIO_NUM = "6"

resolution = isl29023.COMMAND_2_RESOLUTION_16_BIT
rnge = isl29023.COMMAND_2_RANGE_1000_LUX
r_ext = 499000.0 # Rext is nominally 499Kohm

# [0] is visible light, [1] is IR 
Illuminances = [lwm2m.create_IPSO_Illuminance(), lwm2m.create_IPSO_Illuminance()]

res=0.0
if resolution==isl29023.COMMAND_2_RESOLUTION_4_BIT:
    res = 16.0
elif resolution==isl29023.COMMAND_2_RESOLUTION_8_BIT:
    res = 256.0
elif resolution==isl29023.COMMAND_2_RESOLUTION_12_BIT:
    res = 4096.0
elif resolution==isl29023.COMMAND_2_RESOLUTION_16_BIT:
    res = 65536.0

fs=0.0;
if rnge==isl29023.COMMAND_2_RANGE_1000_LUX:
    fs = 1000.0
elif rnge==isl29023.COMMAND_2_RANGE_4000_LUX:
    fs = 4000.0
elif rnge==isl29023.COMMAND_2_RANGE_16000_LUX:
    fs = 16000.0
elif rnge==isl29023.COMMAND_2_RANGE_64000_LUX:
    fs = 64000.0
      
scale = fs / res * 499000.0 / r_ext;    

# Initialise constant-valued resources 
Illuminances[0][lwm2m.IPSO_Illuminance_Sensor_Units] = "lux"
Illuminances[0][lwm2m.IPSO_Illuminance_Min_Range_Value] = 0
Illuminances[0][lwm2m.IPSO_Illuminance_Max_Range_Value] = fs     
Illuminances[1][lwm2m.IPSO_Illuminance_Sensor_Units] = "lux"
Illuminances[1][lwm2m.IPSO_Illuminance_Min_Range_Value] = 0
Illuminances[1][lwm2m.IPSO_Illuminance_Max_Range_Value] = fs

# Register the LWM2M objects with the Server 
lwm2m.register_object_id(lambda: Illuminances, lwm2m.id_IPSO_Illuminance)

# Create the device objects 
i2c_bus = i2c.device( I2C_DEV_PATH ) # This is the I2C bus
intr_pin = gpio.device( GPIO_NUM ) # GPIO that the interrupt pin is wired to    
device = isl29023.device( i2c_bus, intr_pin )

# Initialise the device 
# NOTE: cannot place device in continuous IR and ALS TODO
device.set_command_1( isl29023.COMMAND_1_MODE_ALS_CONTINUOUS, isl29023.COMMAND_1_PERSIST_1_CYCLE )
device.set_command_2( resolution, rnge )

# Continually read the device and update the LWM2M object 
while True:
    Illuminances[0][lwm2m.IPSO_Illuminance_Sensor_Value] = device.get_data() * scale
    time.sleep(0.1)
