#include <scriptml/gpio.h>
#include <test_print.h>
#include <unistd.h>
#include <coroutines.h>

void f(sml_gpio_handle_t hled, int *stop)
{
	while(!*stop)
	{
		sml_gpio_set_level( hled, 1 );
		sleep(1);
		sml_gpio_set_level( hled, 0 );
		sleep(1);
	}
}

int main()
{
	sml_gpio_handle_t hled = sml_gpio_open("17");
	sml_gpio_set_direction( hled, SML_GPIO_OUT );
	
	sml_gpio_handle_t hbutton = sml_gpio_open("20");
	sml_gpio_set_direction( hbutton, SML_GPIO_IN );
	
	int stop = 0;
	sml_coroutine_handle_t cid = sml_coroutine_create_2(f, hled, &stop);
	
	sml_coroutine_wait( sml_gpio_get_level( hbutton ) );
		
	printstr("button pressed");

	stop = 1;
	sml_coroutine_join(cid);

	printstr("done");

	sml_gpio_close("17");
	sml_gpio_close("20");
		
	return 0;	
}
