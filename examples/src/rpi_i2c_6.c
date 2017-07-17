#include <scriptml/ad7991.h>
#include <scriptml/max518.h> 

#include <scriptml/i2c.h>
#include <stdint.h>
#include <test_print.h>
#include <stdio.h>

int main()
{	
    /* Instantiate the ADC and the DAC on the I2C bus */
    sml_ad7991_t adc = sml_ad7991_create( sml_i2c_open( "/dev/i2c-1" ), 0 );
	sml_max518_t dac = sml_max518_create( sml_i2c_open( "/dev/i2c-1" ), 0 );
    
	uint8_t rd_buf[2], wr_buf[1];
    
    /* Get samples from Vin0 and Vin1 alternately, all other configs left at defaults */
	wr_buf[0] = 0x30;

    /* Write the config value to the ADC */
	sml_ad7991_write( adc, wr_buf, 0, 1 );

	sleep(1);
    
    int i = 0;
    
    /* Define two registers to hold the 16 bit ADC register contents. The 12 LSB are
       the ADC value, and the two bits above that, the channel identity */
    uint8_t MSB, LSB;
    uint8_t ChannelNumber;
    
    int adcValue;
    
    /* Set the DAC vale and then read contents of ADC */
    while(1){
        
        /* Set the DAC level for channels 1 and 2 */
        sml_max518_set_level( dac, 0, i );
        sml_max518_set_level( dac, 1, 255 - i );  
        
 
        
        /* Pause to allow DAC to settle (much longer than needed here to also slow display) */
        sleep(1);
        
        /* Read from the ADC, two bytes */
        sml_ad7991_read( adc, rd_buf, 0, 2 );
        MSB = rd_buf[0];
        LSB = rd_buf[1];
        
        /* Mask and bit shift to get the channel identifier */
        ChannelNumber = (MSB & 0x30) >> 4;
        
        /* Get the 12 bit ADC value */
        adcValue = LSB + ((MSB & 0x0F) << 8);
        
        /* Print the values */
        printf("Channel = %d, Value = %d, DAC0 value = %d, DAC1 value = %d\n", ChannelNumber, adcValue, i, 255-i);
        
        /* increment the DAC set value for the next iteration */
        i++;
    }
	return 0;
}

