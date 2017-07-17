#include <scriptml/spi.h>
#include <stdint.h>
#include <test_print.h>

int main()
{	
    sml_spi_t spi = sml_spi_open( "/dev/spidev0.0" );
    
    sml_spi_config( spi, 
                    0, // mode 0
                    0, // Big endian
                    1000000, // speed not greater than 1MHz,
                    8 ); // bits_per_word 
        
    while(1)
    {
        sml_spi_write( spi,
                       "ABCD",
                       4 );
        char c;
        sml_spi_read( spi,
                      &c,
                      1 );
        printint((int)c);
    }
    
	return 0;
}

