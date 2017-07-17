#include <lwm2m.h> // lwm2m.h is auto-generated

#include <scriptml/i2c.h>
#include <scriptml/gpio.h>
#include <scriptml/lm75b.h>

#include <stdint.h>
#include <unistd.h>
//#include <stdio.h>

/* Hookup details */
#define I2C_DEV_PATH "/dev/i2c-1"
#define GPIO_NUM "4"
#define ADDR_OFFSET 0

#define RED_LED_GPIO_NUM "17"
#define GREEN_LED_GPIO_NUM "19"

LWM2M_IPSO_Temperature_T LWM2M_IPSO_Temperature;

int main()
{    
    float conv = 0.125 / 32.0; // Allow for the 5 zero-bits
    
    /* Initialise constant-valued resources */
    LWM2M_IPSO_Temperature.Sensor_Units = "degrees C"; 
    LWM2M_IPSO_Temperature.Min_Range_Value = -32768.0*conv;
    LWM2M_IPSO_Temperature.Max_Range_Value = 32768.0*conv;       
    
    /* Register the LWM2M objects with the Server */
    sml_lwm2m_register_object(LWM2M_IPSO_Temperature);

    /* Create the device objects */
    sml_i2c_t i2c_bus = sml_i2c_open( I2C_DEV_PATH ); // This is the I2C bus
    sml_gpio_handle_t intr_pin = sml_gpio_open( GPIO_NUM ); // GPIO that the interrupt pin is wired to    
    sml_lm75b_t device = sml_lm75b_create( i2c_bus, ADDR_OFFSET, intr_pin ); 
    
    sml_gpio_handle_t red_led_pin = sml_gpio_open( RED_LED_GPIO_NUM ); // GPIO that the LED is wired to    
    sml_gpio_handle_t green_led_pin = sml_gpio_open( GREEN_LED_GPIO_NUM ); // GPIO that the LED is wired to    
    sml_gpio_set_direction( red_led_pin, SML_GPIO_OUT );
    sml_gpio_set_direction( green_led_pin, SML_GPIO_OUT );
    
    /* Initialise the device */    
    sml_lm75b_set_conf( device, 
                        SML_LM75B_CONF_SHUTDOWN_NORMAL,
                        SML_LM75B_CONF_OS_COMP_INT_COMPARATOR,
                        SML_LM75B_CONF_OS_POL_ACTIVE_LOW,
                        SML_LM75B_CONF_OS_F_QUE_1 ); 

    /* Continually read the device and update the LWM2M object */
    while(1)
    {
        float temp = sml_lm75b_get_temp(device) * conv;
        //printf("%d\n", (int)(temp*1000) );
        LWM2M_IPSO_Temperature.Sensor_Value = temp;
        
        // Light LED when temperature is rising
        if( temp > 23.0 )
            sml_gpio_set_level( red_led_pin, 1 );
        else
            sml_gpio_set_level( red_led_pin, 0 );
        if( temp < 27.0 )
            sml_gpio_set_level( green_led_pin, 1 );
        else
            sml_gpio_set_level( green_led_pin, 0 );
        usleep(100000);
    }

    return 0;
}
