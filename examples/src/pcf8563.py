import i2c
import gpio
import pcf8563
import time
from numpy import *

# Hookup details 
I2C_DEV_PATH = "/dev/i2c-1"
GPIO_NUM = "6" # TODO fill in correctly

# Create the device objects 
i2c_bus = i2c.device( I2C_DEV_PATH ) # This is the I2C bus
intr_pin = gpio.device( GPIO_NUM ) # GPIO that the interrupt pin is wired to    
device = pcf8563.device( i2c_bus, intr_pin ) 
    
vl = [uint8()]
seconds_units = [uint8()]
seconds_tens = [uint8()]
minutes_units = [uint8()]
minutes_tens = [uint8()]
hours_units = [uint8()]
hours_tens = [uint8()]
days_units = [uint8()]
days_tens = [uint8()]
weekdays = [uint8()]
century = [uint8()]
months_units = [uint8()]
months_tens = [uint8()]
years_units = [uint8()]
years_tens = [uint8()]     

# Continually read the device and print to console 
while True:
    device.get_vl_and_time_combined(
        vl, 
        seconds_units, seconds_tens, minutes_units, minutes_tens, hours_units, hours_tens, 
        days_units, days_tens, weekdays, century, months_units, months_tens, years_units, years_tens )
    time.sleep(1.0)
    print str(days_tens[0])+str(days_units[0])+"/"+str(months_tens[0])+str(months_units[0])+"/"+str(19+century[0])+str(years_tens[0])+str(years_units[0]), str(hours_tens[0])+str(hours_units[0])+":"+str(minutes_tens[0])+str(minutes_units[0])+":"+str(seconds_tens[0])+str(seconds_units[0])
