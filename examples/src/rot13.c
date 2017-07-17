#include <scriptml/serial.h>
#include <test_print.h>
#include <unistd.h>
#include <coroutines.h>

char rot13( char c )
{
	if( c<'A' || (c>'Z' && c<'a') || c>'z' )
		return c;
		
	if( c%32 >= 13+('A'%32) )
		c-=13;
	else
		c+=13;
		
	return c;
}

int main()
{
	sml_serial_handle_t h = sml_serial_open();
	
	char *text = sml_serial_read( h );

	char *p;
	for( p=text; *p; p++ )
		*p = rot13(*p);

	char *text = sml_serial_write( h, p );
	
	sml_serial_close();
	
	printstr("done");
	
	return 0;	
}
