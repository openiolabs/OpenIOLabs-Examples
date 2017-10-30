#include <scriptml/gpio.h>
#include <test_print.h>
#include <unistd.h>
#include <coroutines.h>

int main()
{
	sml_gpio_handle_t hled = sml_gpio_open("17");
	sml_gpio_set_direction( hled, SML_GPIO_OUT );
	
	sml_gpio_handle_t hbutton = sml_gpio_open("20");
	sml_gpio_set_direction( hbutton, SML_GPIO_IN );
	
	sml_coroutine_wait( sml_gpio_get_level( hbutton ) );
		
	printstr("button pressed");
	
	sml_gpio_set_level( hled, 1 );
	sleep(1);
	sml_gpio_set_level( hled, 0 );
	
	sml_gpio_close("17");
	sml_gpio_close("20");
	return 0;	
}
