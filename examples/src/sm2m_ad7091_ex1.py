import lwm2m # lwm2m.h is auto-generated
import i2c
#import gpio
import ad7091
import time

time.sleep(1)
print("Here1")

# Hookup details */
I2C_DEV_PATH = "/dev/i2c-1"

# Create LWM2M analogue input object
LWM2M_IPSO_Analog_Input = lwm2m.create_IPSO_Analog_Input()

conv = 3.3/4095.0 # Assume 3.3Volts operation with 12 bit ADC

      
# Register the LWM2M objects with the Server
lwm2m.register_object_id(lambda: LWM2M_IPSO_Analog_Input, lwm2m.id_IPSO_Analog_Input)

# Create the device objects 
i2c_bus = i2c.device( I2C_DEV_PATH ) # This is the I2C bus
adc = ad7091.device( i2c_bus) 

# Set the configuration variables for the ADC

# Power down mode - 4 modes that set the sleep mode and the internal 
# reference. He we de-activate the sleep mode, but activate the internal
# reference. This is MODE1
w_p_down = ad7091.CONF_REG_P_DOWN_MODE_1

# The GPO1 pin is either used as the CONVST pin (conversion start) which is 
# coming from RPI GPIO12 or if used as a GPO output pin and it can drive 
# GPIO12 pin on the OpenIO Labs GP2.
w_gpo1 = ad7091.CONF_REG_GPO1_DRIVE_1

# Sets the polarity of the ALERT/BUSY/GPO0 pin. Use switched by ALERT_EN register
# GPO0 is an output pin. This is used on the OpenIOLabs DB4 development
# board to switch the ADC and DAC internal references between 2.5V (ADC internal)
# and 3.3V external (from VDD power supply).
# 2.5V VREF from ADC to ADC and DAC VREF: CONF_REG_ALERT_POL_OR_GPO0_PIN_ACTIVE_HIGH
# 3.3V VREF from VDD to ADC and DAC VREF: CONF_REG_ALERT_POL_OR_GPO0_PIN_ACTIVE_LOW
# Note the VREF will set the fullscale input / output for the DAC and ADC 
# Here we set the VREF = 3.3V == VDD */
w_alert_pol_or_gpo0 = ad7091.CONF_REG_ALERT_POL_OR_GPO0_PIN_ACTIVE_LOW

# Used to control the use of the ALERT/BUSY/GPO0 pin. For the OpenIO Labs 
# DB4 development board, the GPO0 is used to switch VREF source, so we set
# it to the value that selects the pin as a GPO0 output 
w_alert_en_or_gpo0 = ad7091.CONF_REG_ALERT_EN_OR_GPO0_USED_FOR_GPO0

# Used to activate the BUST status pin. Not used here so set to not used
w_busy = ad7091.CONF_REG_BUSY_NOT_USED_FOR_BUSY

# The cycle timer for Autocycle mode. Here we select 800 microseconds
w_cycle_timer = ad7091.CONF_REG_CYCLE_TIMER_800_US

# Used to select between the autocycle mode and the sample mode. Used with the
# command register.
# Autocycle Mode = 0 & Command Mode = 0 : Sample Mode
# Autocycle Mode = 0 & Command Mode = 1 : Command Mode
# Autocycle Mode = 1 & Command Mode = 0 : Autocycle Mode
# Autocycle Mode = 1 & Command Mode = 1 : Sample Mode
# Here we configure this and the command mode to give Autocycle Mode
w_auto_mode = ad7091.CONF_REG_AUTO_MODE_AUTO_OR_SAMP_MODE

# Used to activate a software reset or de-activate the software reset.
# The software reset is a transitory state and this register is set
# to deactivated when complete. Here we request a SW reset
w_srst = ad7091.CONF_REG_SRST_ACTIVATE

# Used to select Autocycle mode. See the Autocycle Mode register above
# for further details
w_cmd = ad7091.CONF_REG_CMD_SAMP_OR_AUTO_MODE

# Filter to eliminate small glitches on teh I2C lines. Here it is bypassed
w_fltr = ad7091.CONF_REG_FLTR_BYPASS

# GPO2 is used on the OpenIO Labs DB4 development board to control whether we
# loop the 4 DAC outputs to the 4 ADC inputs for testing purposes.
# GPO2 = 0 - Disable DAC-ADC loopback - here ADC input is from the SMA connectors
# GPO2 = 1 - Enable DAC-ADC loopback.
# Here we enable the loopback
w_gpo2 = ad7091.CONF_REG_GPO2_DRIVE_1

# Set the drive type for the GPO0 pin. Open Drain or CMOS.
# Here we select CMOS
w_alert_drive_type = ad7091.CONF_REG_ALERT_DRIVE_TYPE_CMOS

# Configure the ADC with the values that we have slected
adc.set_conf_reg(w_p_down, w_gpo1, w_alert_pol_or_gpo0, w_alert_en_or_gpo0, w_busy, w_cycle_timer, w_auto_mode, w_srst, w_cmd, w_fltr, w_gpo2, w_alert_drive_type)

# Define which channels are active
adc_chan0 = ad7091.CHANNEL_REGISTER_CH0_ENABLED
adc_chan1 = ad7091.CHANNEL_REGISTER_CH1_ENABLED
adc_chan2 = ad7091.CHANNEL_REGISTER_CH2_ENABLED
adc_chan3 = ad7091.CHANNEL_REGISTER_CH3_ENABLED

# Set the channels that are active
adc.set_channel_register(adc_chan0, adc_chan1, adc_chan2, adc_chan3)

res=[0]
alert=[0]
chan=[0]

adc_value = 0.0

# Loop to get the conversion result from the ADC. Only select one channel to push to the server
while True:
    adc.get_conv_res(res,alert,chan)
    adc_value = conv * res[0]
    if chan[0] == 0:
    
        LWM2M_IPSO_Analog_Input[lwm2m.IPSO_Analog_Input_Analog_Input_Current_Value] = adc_value
        print res, chan
        time.sleep(1)
