#include <scriptml/24lc64.h>
#include <scriptml/i2c.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <test_print.h>

#define BAD_ADDR 0x03

void h()
{
	printstr("Error detected");
	sleep(1); // avoid a hard spin
	exit(1);
}

int main()
{	
	// The handler function h should be called on error
	set_exception_handler( external_error, &h );
	
	// Expand the sml_24lc64_create() and modify it to use the wrong
	// address (according to i2cdetect, there's nothing there at 0x03)
	sml_24lc64_t eeprom;
	eeprom.piic = &sml_i2c_open( "/dev/i2c-1" );
	eeprom.addr = BAD_ADDR;

	uint8_t rd_buf[4], wr_buf[4];
	wr_buf[0] = 35;
	wr_buf[1] = 22;
	wr_buf[2] = 34;
	wr_buf[3] = 99;
	sml_24lc64_write( eeprom, wr_buf, 0, 4 );

	sleep(1);
	while(1)
		sml_24lc64_read( eeprom, rd_buf, 0, 4 );
        int i;
        for(i=0; i<4; i++){ 
            printint(rd_buf[i]);
        }
	}
	return 0;
}

