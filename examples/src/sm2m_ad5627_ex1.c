#include <lwm2m.h> // lwm2m.h is auto-generated

#include <scriptml/i2c.h>
#include "i2c_regmap.h"
#include "ad5627.h"

#include <stdint.h>
#include <unistd.h>
#include "stdio.h"

LWM2M_IPSO_Analog_Output_T LWM2M_IPSO_Analog_Output;


int main()
{    
    float value;
    int int_value;     
     
    LWM2M_IPSO_Analog_Output.Min_Range_Value = 0.0;
    LWM2M_IPSO_Analog_Output.Max_Range_Value = 10.0;       
   
    /* Register the LWM2M objects with the Server */
    sml_lwm2m_register_object(LWM2M_IPSO_Analog_Output);

    /* Create a device manager object to store local device parameters */
    sml_i2c_regmap_t dev  =  sml_i2c_regmap_create( sml_i2c_open( "/dev/i2c-1" ), AD5627_BASE_ADDR, AD5627_REG_SIZE,0 );
    
    /* Initialise the DAC */
    sml_ad5627_sw_init(dev);

    /* Continually read the LWM2M Analog Output object and set the DAC to the digital equivalent Voltage*/
    while(1)
    {
        /* Get the current Analog Output Voltage requested */
        value = LWM2M_IPSO_Analog_Output.Analog_Output_Current_Value;
        
        /* Convert the analog voltage to an equivalent integer DAC value for the AD5627*/
        int_value = (int) (value * AD5627_MAX_INT_VALUE / AD5627_MAX_FLOAT_VALUE_3V3_REF);
        
        /* Set the DAC level using the integer DAC value. This value is being sent to both DACs on the AD5627 */
        sml_ad5627_set_level( dev, AD5627_DACA_AND_DACB, int_value );
        
        /* Print the float and int version of the level */
        printf("Current DAC Integer value = %d\n", int_value);
        printf("Current DAC Float value = %d.%03d\n", (int)value , (int)(value*1000)%1000);
        
        /* Pause a while for the next value to be set */
        sleep(1);
    }

    return 0;
}
