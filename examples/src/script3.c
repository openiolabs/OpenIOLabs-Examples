/* Standard LWM2M object and RPi required */

#include <lwm2m.h> // lwm2m.h is auto-generated from registry.json so any of those resources and objects may be used
#include <gpio.h>
#include <test_print.h>

LWM2M_OpenIO_Motor_Control_T LWM2M_OpenIO_Motor_Control; // Declare an LWM2M object as a ScriptML variable

int main()
{
	sml_lwm2m_register_object(LWM2M_OpenIO_Motor_Control); // Register our object with server 
	// ... LWM2M_OpenIO_Motor_Control is now externally readable and modifiable
	    		    		    
	sml_gpio_handle_t pin =	sml_gpio_open("21"); // Set up pin 21 as output
	sml_gpio_set_direction( pin, SML_GPIO_OUT );

	// Just keep on setting the GPIO to the "state" resource of the object (id=1)
	while(1)
	{
		//printint(LWM2M_OpenIO_Ping_interface.LWM2M_OpenIO_Ping_interface_Ping);
		sml_gpio_set_level( pin, LWM2M_OpenIO_Motor_Control.State );	
	}
	    
    return 0;
}
