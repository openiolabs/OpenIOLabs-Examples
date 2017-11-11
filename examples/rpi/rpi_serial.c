#include <scriptml/serial.h>
#include <stdio.h>
#include <test_print.h>
#include <unistd.h>

int main()
{
    struct termios tattr;
  	sml_serial_handle_t h = sml_serial_open(0); // open port 0
	
    /* Set the funny terminal modes. */
    tcgetattr (h, &tattr);
    tattr.c_lflag &= ~(ECHO); 
    tattr.c_cflag |= CRTSCTS | CLOCAL; 
    tattr.c_iflag &= ~(IXON | IXOFF); 
    tcsetattr (h, TCSAFLUSH, &tattr);
	
	sml_serial_write( h, "hello\n" );

	printstr( sml_serial_read( h ) );

	sml_serial_close(h);

	printstr("done");
	
	return 0;	
}
