#include <auto_start.h>
#include <test_print.h>
#include <unistd.h>

int main()
{
	printstr("main()");	

	sml_auto_start_enable();

	printstr("Enabled auto-start");
	
	// General flags test; write after read so value only seen on second run
	char b[256];
	sml_persistent_flag_read_str("abc", b);
	printstr( b );
	sml_persistent_flag_write_float("abc", 6.54);
	
	return 0;
}

void _restart()
{
	//sleep(30);
	
	printstr("_restart()");	

	sml_auto_start_disable();

	printstr("Disabled auto-start");	
}
