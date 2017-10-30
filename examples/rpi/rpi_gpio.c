#include <scriptml/gpio.h>
#include <test_print.h>
#include <unistd.h>

int main()
{
	sml_gpio_handle_t h = sml_gpio_open("17");
	sml_gpio_set_direction( h, SML_GPIO_OUT );
	sml_gpio_set_level( h, 1 );
	sleep(1);
	sml_gpio_set_level( h, 0 );
	printstr("ending");
	sml_gpio_close("17");
	return 0;	
} 
