#include <scriptml/24lc64.h>
#include <scriptml/i2c.h>
#include <stdint.h>
#include <test_print.h>

int main()
{	
    sml_24lc64_t eeprom = sml_24lc64_create( sml_i2c_open( "/dev/i2c-1" ), 0 );
	uint8_t rd_buf[4], wr_buf[4];
	wr_buf[0] = 35;
	wr_buf[1] = 22;
	wr_buf[2] = 34;
	wr_buf[3] = 99;
	sml_24lc64_write( eeprom, wr_buf, 0, 4 );

	sleep(1);
	while(1)
	{
		sml_24lc64_read( eeprom, rd_buf, 0, 4 );
        int i;
        for(i=0; i<4; i++){ 
            printint(rd_buf[i]);
        }
	}
	return 0;
}

