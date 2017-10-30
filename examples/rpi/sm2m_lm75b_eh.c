#include <lwm2m.h> // lwm2m.h is auto-generated

#include <scriptml/i2c.h>
#include <scriptml/gpio.h>
#include <scriptml/lm75b.h>

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

// Undefine when fault resource is ready
#define NO_FAULT_RESOURCE

/* Hookup details */
#define I2C_DEV_PATH "/dev/i2c-1"
#define GPIO_NUM "4"
#define ADDR_OFFSET 0

LWM2M_IPSO_Temperature_T LWM2M_IPSO_Temperature;

void handle_error()
{
	sleep(1); // avoid a hard spin
#ifndef NO_FAULT_RESOURCE
	LWM2M_IPSO_Temperature.FaultStatus = LWM2M_FAULT_IO;
#endif
	exit(1); // ... or maybe restart here
}

int main()
{    
	// The handler function h should be called on error
	set_exception_handler( external_error, &handle_error );
	
    float conv = 0.125 / 32.0; // Allow for the 5 zero-bits
    
    /* Initialise constant-valued resources */
    LWM2M_IPSO_Temperature.Sensor_Units = "degrees C"; 
    LWM2M_IPSO_Temperature.Min_Range_Value = -32768.0*conv;
    LWM2M_IPSO_Temperature.Max_Range_Value = 32768.0*conv;     
#ifndef NO_FAULT_RESOURCE
    LWM2M_IPSO_Temperature.FaultStatus = LWM2M_FAULT_OK;
#endif    
    /* Register the LWM2M objects with the Server */
    sml_lwm2m_register_object(LWM2M_IPSO_Temperature);

    /* Create the device objects */
    sml_i2c_t i2c_bus = sml_i2c_open( I2C_DEV_PATH ); // This is the I2C bus
    sml_gpio_handle_t intr_pin = sml_gpio_open( GPIO_NUM ); // GPIO that the interrupt pin is wired to    
    sml_lm75b_t device = sml_lm75b_create( i2c_bus, ADDR_OFFSET, intr_pin ); 
    
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
        LWM2M_IPSO_Temperature.Sensor_Value = temp;
#ifndef NO_FAULT_RESOURCE
        if( temp > 40 )
            LWM2M_IPSO_Temperature.FaultStatus = LWM2M_FAULT_OVERTEMP;
#endif
        usleep(100000);
    }

    return 0;
}
