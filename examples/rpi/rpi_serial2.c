#include <scriptml/serial.h>
#include <test_print.h>
#include <unistd.h>

int main()
{
	sml_serial_handle_t h = sml_serial_open();
	
	char *text = sml_serial_read( h );

	printstr(text);
	
	sml_serial_close();
	
	printstr("done");
	
	return 0;	
}
