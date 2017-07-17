#!/usr/bin/python
#import smbus
import time

#to enable transfer of data to and from the Labbook to the device
import i2c
import lwm2m

####################################################################

# Define some constants from the datasheet
DEVICE = 0x23  # Default device I2C address

MAX_I2C_REGISTERS = 128 # Maximum number of registers (16kbit)
REG_START_ADDR = 0 # Start address for the read and write operations
BYTES_TO_WRITE = 16 # Number of bytes to write
BYTES_TO_READ = 16 # Number of bytes to read


POWER_DOWN = 0x00  # No active state
POWER_ON = 0x01  # Power on
RESET = 0x07  # Reset data register value

# Start measurement at 4lx resolution. Time typically 16ms.
CONTINUOUS_LOW_RES_MODE = 0x13
# Start measurement at 1lx resolution. Time typically 120ms
CONTINUOUS_HIGH_RES_MODE_1 = 0x10
# Start measurement at 0.5lx resolution. Time typically 120ms
CONTINUOUS_HIGH_RES_MODE_2 = 0x11
# Start measurement at 1lx resolution. Time typically 120ms
# Device is automatically set to Power Down after measurement.
ONE_TIME_HIGH_RES_MODE_1 = 0x20
# Start measurement at 0.5lx resolution. Time typically 120ms
# Device is automatically set to Power Down after measurement.
ONE_TIME_HIGH_RES_MODE_2 = 0x21
# Start measurement at 1lx resolution. Time typically 120ms
# Device is automatically set to Power Down after measurement.
ONE_TIME_LOW_RES_MODE = 0x23

# bus = smbus.SMBus(0) # Rev 1 Pi uses 0
#bus = smbus.SMBus(1)  # Rev 2 Pi uses 1


# Instantiate the device
# There is no exisinting library for this device
# the device will be created from the i2c and i2c_regmap
# Create the EEPROM device handler with the I2C device location, EEPROM I2C address and maximum number of registers
lum = i2c.device("/dev/i2c-1")
lum.write( DEVICE, [0x01] ) # power on
lum.write( DEVICE, [0x10] ) # continuous, h-resolution

#Create the device on the server
my_lum = lwm2m.create_IPSO_Illuminance()

#Register the ADC with the server
lwm2m.register_object_id(lambda: my_lum, lwm2m.id_IPSO_Illuminance)


def convertToNumber(data):
    # Simple function to convert 2 bytes of data
    # into a decimal number
    return ((data[1] + (256 * data[0])) / 1.2)


def readLight():
    data = lum.read(DEVICE, 2)
    return convertToNumber(data)

def main():
    while True:
        print "Light Level : " + str(readLight()) + " lx"

        # Update ADC value to the server
        my_lum[lwm2m.IPSO_Illuminance_Sensor_Value] = readLight()


        time.sleep(0.5)


if __name__ == "__main__":
    main()
