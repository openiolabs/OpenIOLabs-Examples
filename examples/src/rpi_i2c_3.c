#include <scriptml/pcf8574a.h>
#include <scriptml/i2c.h>
#include <stdint.h>
#include <test_print.h>

int main()
{	
    sml_pcf8574a_t eeprom = sml_pcf8574a_create( sml_i2c_open( "/dev/i2c-1" ), 0 );
	uint8_t rd_buf[8], wr_buf[1];
    
    /* Set the In/Out to all In */
	wr_buf[0] = 0xFF;

	sml_pcf8574a_write( eeprom, wr_buf, 0, 1 );

	sleep(1);
    
    int i;
    sml_pcf8574a_read( eeprom, rd_buf, 0, 1 );
    
    /* Read contents of IO expander */
    for (i = 0; i < 1; i++){
        printint(rd_buf[i]);
        
    }
	return 0;
}

