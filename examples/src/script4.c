/* Standard LWM2M object and RPi required */

#include <lwm2m.h> // lwm2m.h is auto-generated from registry.json so any of those resources and objects may be used
#include <gpio.h>

#define NUM_GPIOS 2

char * gpio_map[NUM_GPIOS] = {"21", "26"};
sml_gpio_handle_t gpio_pin[NUM_GPIOS];


LWM2M_OpenIO_Motor_Control_T LWM2M_OpenIO_Motor_Control[NUM_GPIOS]; // Declare an LWM2M object as a ScriptML variable

int main()
{
	int i;
	
	for( i=0; i<NUM_GPIOS; i++ )
	{
		gpio_pin[i] = sml_gpio_open(gpio_map[i]); 
		sml_gpio_set_direction( gpio_pin[i], SML_GPIO_OUT );
	}
	
	sml_lwm2m_register_object(LWM2M_OpenIO_Motor_Control); // Register our object with server 
	// ... LWM2M_OpenIO_Motor_Control is now externally readable and modifiable	    		 

	// Just keep on setting the GPIOs to the "state" resource of the objects (id=1)
	while(1)
	{
		for( i=0; i<NUM_GPIOS; i++ )
			sml_gpio_set_level( gpio_pin[i], LWM2M_OpenIO_Motor_Control[i].State );	
	}
	    
    return 0;
}
