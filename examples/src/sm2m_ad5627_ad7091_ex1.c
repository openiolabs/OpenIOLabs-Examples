/* 
 * This example script uses the ADC and the DAC on the development board.
 * The DAC is driven from a user selectable voltage setting on the browser.
 * This sets the DAC output voltage. Then the DAC output is passed to the ADC
 * input. The ADC input is read and then passed back to the browser as an
 * LWM2M analogue input object. This can be displayed as a graph on the 
 * browser window. 
 */


#include <lwm2m.h> // lwm2m.h is auto-generated
#include <test_print.h>
#include "i2c_regmap.h"

#include <unistd.h>
#include "stdio.h"
#include "ad7091.h"
#include "ad5627.h"
#include <scriptml/i2c.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define I2C_DEV_PATH "/dev/i2c-1"

LWM2M_IPSO_Analog_Input_T LWM2M_IPSO_Analog_Input[2];
LWM2M_IPSO_Analog_Output_T LWM2M_IPSO_Analog_Output;

int main(){
    float value;
    int int_value;     
     

    /* Create various variables used for the configuration and the results */
    int ch0, ch1, ch2, ch3;
    int rch0, rch1, rch2, rch3;
    
    int w_p_down, w_gpo1, w_alert_pol_or_gpo0, w_alert_en_or_gpo0, w_busy, w_cycle_timer, w_auto_mode, w_srst, w_cmd, w_fltr, w_gpo2, w_alert_drive_type;
    int r_p_down, r_gpo1, r_alert_pol_or_gpo0, r_alert_en_or_gpo0, r_busy, r_cycle_timer, r_auto_mode, r_srst, r_cmd, r_fltr, r_gpo2, r_alert_drive_type;
    
    int result;
    int alert_flag;
    int chan;
    
    float adc_value_float_volts;
    
    /* Define limits for the DAC */
    LWM2M_IPSO_Analog_Output.Min_Range_Value = 0.0;
    LWM2M_IPSO_Analog_Output.Max_Range_Value = 10.0;       
   
    /* Register the LWM2M objects with the Server */
    sml_lwm2m_register_object(LWM2M_IPSO_Analog_Output);

    /* Create a device manager object to store local device parameters */
    sml_i2c_regmap_t dev  =  sml_i2c_regmap_create( sml_i2c_open( "/dev/i2c-1" ), AD5627_BASE_ADDR, AD5627_REG_SIZE,0 );
    
    /* Initialise the DAC */
    sml_ad5627_sw_init(dev);        
    

    /* Register the LWM2M objects with the Server */
    sml_lwm2m_register_object(LWM2M_IPSO_Analog_Input);
    
    /* Create the device handle for the AD7091 ADC */
    sml_ad7091_t dev2 = sml_ad7091_create( sml_i2c_open( I2C_DEV_PATH ));     
    
    /* Power down mode - 4 modes that set the sleep mode and the internal 
     * reference. He we de-activate the sleep mode, but activate the internal
     * reference. This is MODE1 */
    w_p_down = SML_AD7091_CONF_REG_P_DOWN_MODE_1;
    
    /* The GPO1 pin is either used as the CONVST pin (conversion start) which is 
     * coming from RPI GPIO12 or if used as a GPO output pin and it can drive 
     * GPIO12 pin on the OpenIO Labs GP2.  */
//    w_gpo1 = SML_AD7091_CONF_REG_GPO1_DRIVE_0;
    w_gpo1 = 1;
    
    
    /* Sets the polarity of the ALERT/BUSY/GPO0 pin. Use switched by ALERT_EN register
     * GPO0 is an output pin. This is used on the OpenIOLabs DB4 development
     * board to switch the ADC and DAC internal references between 2.5V (ADC internal)
     * and 3.3V external (from VDD power supply).
     * 3.3V VREF from VDD to ADC and DAC VREF: SML_AD7091_CONF_REG_ALERT_POL_OR_GPO0_PIN_ACTIVE_LOW     
     * 2.5V VREF from ADC to ADC and DAC VREF: SML_AD7091_CONF_REG_ALERT_POL_OR_GPO0_PIN_ACTIVE_HIGH
     * Note the VREF will set the fullscale input / output for the DAC and ADC 
     * Here we set the VREF = 3.3V == VDD */
    w_alert_pol_or_gpo0 = SML_AD7091_CONF_REG_ALERT_POL_OR_GPO0_PIN_ACTIVE_LOW;
    
    /* Used to control the use of the ALERT/BUSY/GPO0 pin. For the OpenIO Labs 
     * DB4 development board, the GPO0 is used to switch VREF source, so we set
     * it to the value that selects the pin as a GPO0 output */
    w_alert_en_or_gpo0 = SML_AD7091_CONF_REG_ALERT_EN_OR_GPO0_USED_FOR_GPO0;
    
    /* Used to activate the BUST status pin. Not used here so set to not used */
    w_busy = SML_AD7091_CONF_REG_BUSY_NOT_USED_FOR_BUSY;
    
    /* The cycle timer for Autocycle mode. Here we select 800 microseconds */
    w_cycle_timer = SML_AD7091_CONF_REG_CYCLE_TIMER_800_US;
    
    /* Used to select between the autocycle mode and the sample mode. Used with the
     * command register.
     * Autocycle Mode = 0 & Command Mode = 0 : Sample Mode
     * Autocycle Mode = 0 & Command Mode = 1 : Command Mode
     * Autocycle Mode = 1 & Command Mode = 0 : Autocycle Mode
     * Autocycle Mode = 1 & Command Mode = 1 : Sample Mode
     * Here we configure this and the command mode to give Autocycle Mode */
    w_auto_mode = SML_AD7091_CONF_REG_AUTO_MODE_AUTO_OR_SAMP_MODE;
    
    /* Used to activate a software reset or de-activate the software reset.
     * The software reset is a transitory state and this register is set
     * to deactivated when complete. Here we request a SW reset */
    w_srst = SML_AD7091_CONF_REG_SRST_ACTIVATE;
    
    /* Used to select Autocycle mode. See the Autocycle Mode register above
     * for further details */
    w_cmd = SML_AD7091_CONF_REG_CMD_SAMP_OR_AUTO_MODE;
    
    /* Filter to eliminate small glitches on teh I2C lines. Here it is bypassed */
    w_fltr = SML_AD7091_CONF_REG_FLTR_BYPASS;
    
    /* GPO2 is used on the OpenIO Labs DB4 development board to control whether we
     * loop the 4 DAC outputs to the 4 ADC inputs for testing purposes.
     * GPO2 = 0 - Disable DAC-ADC loopback - here ADC input is from the SMA connectors
     * GPO2 = 1 - Enable DAC-ADC loopback.
     * Here we enable the loopback */
    w_gpo2 = SML_AD7091_CONF_REG_GPO2_DRIVE_1;
    
    /* Set the drive type for the GPO0 pin. Open Drain or CMOS.
     * Here we select CMOS */
    w_alert_drive_type = SML_AD7091_CONF_REG_ALERT_DRIVE_TYPE_CMOS;
 
    /* Configure the ADC with the values that we have slected */
    sml_ad7091_set_conf_reg(dev2, w_p_down, w_gpo1, w_alert_pol_or_gpo0, 
                                  w_alert_en_or_gpo0, w_busy, w_cycle_timer, 
                                  w_auto_mode, w_srst, w_cmd, w_fltr, w_gpo2, w_alert_drive_type);
    usleep(1000000);

    /* Read back the configuration register and print to validate that we have the correct configuration */
    sml_ad7091_get_conf_reg(dev2, &r_p_down, &r_gpo1, &r_alert_pol_or_gpo0, 
                                  &r_alert_en_or_gpo0, &r_busy, &r_cycle_timer, 
                                  &r_auto_mode, &r_srst, &r_cmd, &r_fltr, &r_gpo2, &r_alert_drive_type );
    usleep(1000000);
    
    /* Print the configuration. The Software reset Register is omitted as its value is transitory and changes */
    if( w_p_down == r_p_down && w_gpo1 == r_gpo1 && w_alert_pol_or_gpo0 == r_alert_pol_or_gpo0 &&
            w_alert_en_or_gpo0 == r_alert_en_or_gpo0 && w_busy == r_busy && w_cycle_timer == r_cycle_timer &&
            w_auto_mode == r_auto_mode && w_cmd == r_cmd && w_fltr == r_fltr &&
            w_gpo2 == r_gpo2 && w_alert_drive_type == r_alert_drive_type){
            
        printf("PASS: Correct device configuration \n");
        
    } else {      
        printf("FAIL: Incorrect device configuration \n");
        printf("w_p_down set = %d, Get value = %d\n", w_p_down, r_p_down);
        printf("w_gpo1 set = %d, Get value = %d\n", w_gpo1, r_gpo1);
        printf("w_alert_pol_or_gpo0 set = %d, Get value = %d\n", w_alert_pol_or_gpo0, r_alert_pol_or_gpo0);
        printf("w_alert_en_or_gpo0 set = %d, Get value = %d\n", w_alert_en_or_gpo0, r_alert_en_or_gpo0);
        printf("w_busy set = %d, Get value = %d\n", w_busy, r_busy);
        printf("w_cycle_timer set = %d, Get value = %d\n", w_cycle_timer, r_cycle_timer);
        printf("w_auto_mode set = %d, Get value = %d\n", w_auto_mode, r_auto_mode);
        printf("w_cmd set = %d, Get value = %d\n", w_cmd, r_cmd);
        printf("w_fltr set = %d, Get value = %d\n", w_fltr, r_fltr);
        printf("w_gpo2 set = %d, Get value = %d\n", w_gpo2, r_gpo2);
        printf("w_alert_drive_type set = %d, Get value = %d\n", w_alert_drive_type, r_alert_drive_type);
        
        
        
        
    }
    
    /* Next we configure the Channels that we want enabled. 0 is disabled, 1 enabled.
       In this example, we will be working with just channel 0 and channel 1. */
    ch0 = SML_AD7091_CHANNEL_REGISTER_CH0_ENABLED; 
    ch1 = SML_AD7091_CHANNEL_REGISTER_CH1_ENABLED; 
    ch2 = SML_AD7091_CHANNEL_REGISTER_CH1_ENABLED; 
    ch3 = SML_AD7091_CHANNEL_REGISTER_CH1_ENABLED;
    
    /* Set the active configuration of the ADC */
    sml_ad7091_set_channel_register(dev2, ch0, ch1, ch2, ch3);
    
    usleep(1000000);
    
    /* Retrieve the active configuration for checking */
    sml_ad7091_get_channel_register(dev2, &rch0, &rch1, &rch2, &rch3 );

    /* Check we have the correct channel configuration */
    if (ch0 == rch0 && ch1 == rch1 && ch2 == rch2 && ch3 == rch3){
        printf("PASS: Correct channel configurations\n");
    } else {
        printf("FAIL: Incorrect channel configurations\n");
        printf("ch0 = %d, ch1 = %d, ch2 = %d, ch3 = %d\n", ch0, ch1, ch2, ch3);        
        printf("rch0 = %d, rch1 = %d, rch2 = %d, rch3 = %d\n", rch0, rch1, rch2, rch3);
        
    }
    usleep(1000000);
      
    while(1) {
        
        
        /* Get the current Analog Output Voltage requested */
        value = LWM2M_IPSO_Analog_Output.Analog_Output_Current_Value;
        
        /* Convert the analog voltage to an equivalent integer DAC value for the AD5627*/
        int_value = (int) (value * AD5627_MAX_INT_VALUE / AD5627_MAX_FLOAT_VALUE_3V3_REF);
        
        /* Set the DAC level using the integer DAC value. This value is being sent to both DACs on the AD5627 */
        sml_ad5627_set_level( dev, AD5627_DACA_AND_DACB, int_value );
        
        /* Print the float and int version of the level */
        printf("Current DAC Integer value = %d\n", int_value);
        printf("Current DAC Float value = %d.%03d\n", (int)value , (int)(value*1000)%1000);
   
        /* Get the conversion result, the channel and the ALERT value */
        sml_ad7091_get_conv_res(dev2, &result, &alert_flag, &chan );
        
        /* Convert to voltage based on VREF */
        if( w_alert_pol_or_gpo0 == SML_AD7091_CONF_REG_ALERT_POL_OR_GPO0_PIN_ACTIVE_LOW) {
            
            adc_value_float_volts = (float) (result) * 3.3 / 4096;
        } else {
            adc_value_float_volts = (float) (result) * 2.5 / 4096;
        }
            
        if(0 == chan && ch0 == SML_AD7091_CHANNEL_REGISTER_CH0_ENABLED) {
            printf("Channel ID = %d, Conv result = %d, DAC Float value = %d.%03d Volts\n", chan, result, (int)adc_value_float_volts , (int)(adc_value_float_volts*1000)%1000);    
            LWM2M_IPSO_Analog_Input[0].Analog_Input_Current_Value = adc_value_float_volts;
            sleep(5);  
        }
        
        if(1 == chan && ch1 == SML_AD7091_CHANNEL_REGISTER_CH1_ENABLED) {
            printf("Channel ID = %d, Conv result = %d, DAC Float value = %d.%03d Volts\n", chan, result, (int)adc_value_float_volts , (int)(adc_value_float_volts*1000)%1000);    
            LWM2M_IPSO_Analog_Input[1].Analog_Input_Current_Value = adc_value_float_volts;
            sleep(5);  
        }   
    }
    return 0;
}