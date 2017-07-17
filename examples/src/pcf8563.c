#include <scriptml/i2c.h>
#include <scriptml/gpio.h>
#include <scriptml/pcf8563.h>

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

/* Hookup details */
#define I2C_DEV_PATH "/dev/i2c-1"
#define GPIO_NUM "6" // TODO fill in correctly

int main()
{
    /* Create the device objects */
    sml_i2c_t i2c_bus = sml_i2c_open( I2C_DEV_PATH ); // This is the I2C bus
    sml_gpio_handle_t intr_pin = sml_gpio_open( GPIO_NUM ); // GPIO that the interrupt pin is wired to    
    sml_pcf8563_t device = sml_pcf8563_create( i2c_bus, intr_pin ); 
        
    int vl;
    int seconds_units;
    int seconds_tens;
    int minutes_units;
    int minutes_tens;
    int hours_units;
    int hours_tens;
    int days_units;
    int days_tens;
    int weekdays;
    int century;
    int months_units;
    int months_tens;
    int years_units;
    int years_tens;     
    
    /* Continually read the device and print to console */
    while(1)
    {
        sml_pcf8563_get_vl_and_time_combined( device,
            &vl, 
            &seconds_units, &seconds_tens, &minutes_units, &minutes_tens, &hours_units, &hours_tens, 
            &days_units, &days_tens, &weekdays, &century, &months_units, &months_tens, &years_units, &years_tens );
        sleep(1);
        printf("%d%d/%d%d/%d%d%d %d%d:%d%d:%d%d\n", 
               days_tens, days_units, months_tens, months_units, 19+century, years_tens, years_units, 
               hours_tens, hours_units, minutes_tens, minutes_units, seconds_tens, seconds_units );        
    }

    return 0;
}
