#include <scriptml/serial.h>
#include <test_print.h>
#include <unistd.h>

int main()
{
	sml_serial_handle_t h = sml_serial_open();
	
	sml_serial_write( h, "hello\n" );

	sml_serial_close();

	printstr("done");
	
	return 0;	
}
