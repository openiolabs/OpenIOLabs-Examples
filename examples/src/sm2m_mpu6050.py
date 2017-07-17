import lwm2m # lwm2m.h is auto-generated
import i2c
import gpio
import mpu6050
import time
from numpy import *

# Hookup details 
I2C_DEV_PATH = "/dev/i2c-1"
GPIO_NUM = "21"
ADDR_OFFSET = 0

# Chosen configuration 
afs_sel = mpu6050.ACCEL_CONFIG_AFS_SEL_2
gfs_sel = mpu6050.GYRO_CONFIG_FS_SEL_2000

# Define instances of the LWM2M objects 
Accelerometer = lwm2m.create_IPSO_Accelerometer()
Gyrometer = lwm2m.create_IPSO_Gyrometer()

raw_fs = 32768.0
afs = 0
if afs_sel==mpu6050.ACCEL_CONFIG_AFS_SEL_2:
    afs = 2.0
elif afs_sel==mpu6050.ACCEL_CONFIG_AFS_SEL_4:
    afs = 4.0
elif afs_sel==mpu6050.ACCEL_CONFIG_AFS_SEL_8:
    afs = 8.0
elif afs_sel==mpu6050.ACCEL_CONFIG_AFS_SEL_16:
    afs = 16.0
                    
gfs = 0                    
if gfs_sel==mpu6050.GYRO_CONFIG_FS_SEL_250:
    gfs = 250.0
elif gfs_sel==mpu6050.GYRO_CONFIG_FS_SEL_500:
    gfs = 500.0
elif gfs_sel==mpu6050.GYRO_CONFIG_FS_SEL_1000:
    gfs = 1000.0
elif gfs_sel==mpu6050.GYRO_CONFIG_FS_SEL_2000:
    gfs = 2000.0;  

# Initialise constant-valued resources 
Accelerometer[lwm2m.IPSO_Accelerometer_Sensor_Units] = "*g" # Note: multiple of earth's magnetic field, not grammes
Accelerometer[lwm2m.IPSO_Accelerometer_Min_Range_Value] = -afs
Accelerometer[lwm2m.IPSO_Accelerometer_Max_Range_Value] = afs        
Gyrometer[lwm2m.IPSO_Gyrometer_Sensor_Units] = "degrees/s" # degrees per second
Gyrometer[lwm2m.IPSO_Gyrometer_Min_Range_Value] = -gfs
Gyrometer[lwm2m.IPSO_Gyrometer_Max_Range_Value] = gfs

# Register the LWM2M objects with the Server 
lwm2m.register_object_id(lambda: Accelerometer, lwm2m.id_IPSO_Accelerometer)
lwm2m.register_object_id(lambda: Gyrometer, lwm2m.id_IPSO_Gyrometer)

# Create the device objects 
i2c_bus = i2c.device( I2C_DEV_PATH ) # This is the I2C bus
intr_pin = gpio.device( GPIO_NUM ) # GPIO that the interrupt pin is wired to    
device = mpu6050.device( i2c_bus, ADDR_OFFSET, intr_pin ) 
    
# Confirm device present 
who = [int8()]
device.get_who_am_i( who )
assert who[0] == 0x34
    
# Initialise the device 
device.set_pwr_mgmt_1( 0, 0, 0, 0, mpu6050.PWR_MGMT_1_CLKSEL_INTERNAL )
device.set_gyro_config( gfs_sel )
device.set_accel_config( afs_sel )

# Continually read the device and update the LWM2M object 
while True:
    Accelerometer[lwm2m.IPSO_Gyrometer_X_Value] = device.get_accel_xout() * afs / raw_fs
    Accelerometer[lwm2m.IPSO_Gyrometer_Y_Value] = device.get_accel_yout() * afs / raw_fs
    Accelerometer[lwm2m.IPSO_Gyrometer_Z_Value] = device.get_accel_zout() * afs / raw_fs
    Gyrometer[lwm2m.IPSO_Gyrometer_X_Value] = device.get_gyro_xout() * gfs / raw_fs
    Gyrometer[lwm2m.IPSO_Gyrometer_Y_Value] = device.get_gyro_yout() * gfs / raw_fs
    Gyrometer[lwm2m.IPSO_Gyrometer_Z_Value] = device.get_gyro_zout() * gfs / raw_fs
    time.sleep(0.1) # 100ms

