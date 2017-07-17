import lwm2m # lwm2m.h is auto-generated
import i2c
import gpio
import mpl115a2
import time
from numpy import *

# Hookup details 
I2C_DEV_PATH = "/dev/i2c-1"

# Define instances of the LWM2M objects 
Pressure = lwm2m.create_IPSO_Pressure()

Pressure[lwm2m.IPSO_Pressure_Sensor_Units] = "kPa"
Pressure[lwm2m.IPSO_Pressure_Min_Range_Value] = 50.0
Pressure[lwm2m.IPSO_Pressure_Max_Range_Value] = 115.0

# Register the LWM2M objects with the Server 
lwm2m.register_object_id(lambda: Pressure, lwm2m.id_IPSO_Pressure)

# Create the device objects 
i2c_bus = i2c.device( I2C_DEV_PATH ) # This is the I2C bus
device = mpl115a2.device( i2c_bus )

a0 = float(device.get_a0()) / 8.0 # Q3
b1 = float(device.get_b1()) / 8192.0 # Q13
b2 = float(device.get_b2()) / 16384.0 # Q14
c12 = float(device.get_c12()) / 65536.0 / 256.0 # Q24

# Continually read the device and update the LWM2M object 
while True:
    Padc=[0]
    Tadc=[0]
    device.convert()
    time.sleep(0.1)

    device.get_padc( Padc )
    device.get_tadc( Tadc )
    Pcomp = a0 + (b1 + c12*Tadc[0])*Padc[0] + b2*Tadc[0]
    pressure = Pcomp * (115.0-50.0) / 1023.0 + 50.0
    Pressure[lwm2m.IPSO_Pressure_Sensor_Value] = pressure
