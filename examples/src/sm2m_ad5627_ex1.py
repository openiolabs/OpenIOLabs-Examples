import lwm2m # lwm2m.h is auto-generated
import i2c
import ad5627
import time

time.sleep(1)

# Hookup details */
I2C_DEV_PATH = "/dev/i2c-1"

# Create the device objects 
i2c_bus = i2c.device( I2C_DEV_PATH ) # This is the I2C bus

# Create the DAC desvice and link to the I2C address
dac = ad5627.device( i2c_bus)

# Put DAC into power up state
dac.power_up()

# Perform software reset for the DAC
dac.sw_reset()

# Set to software controlled conversion
dac.set_ldac()

# Loop to set DAC to multiple levels with a pause between
while(True):
    dac.set_level(ad5627.DACA_AND_DACB, 0)
    time.sleep(1)
    dac.set_level(ad5627.DACA_AND_DACB, 32767)
    time.sleep(1)
    dac.set_level(ad5627.DACA_AND_DACB, 65535)
    time.sleep(1)