#include <lwm2m.h> // lwm2m.h is auto-generated

#include <scriptml/i2c.h>
#include <scriptml/pca9534.h>
#include <scriptml/gpio.h>

#include <stdint.h>
#include <unistd.h>

/* Hookup details */
#define I2C_DEV_PATH "/dev/i2c-1"
#define ADDR_OFFSET 0
#define NUM_INS 4
#define NUM_OUTS 4
#define GPIO_NUM "21"


/* Define instances of the LWM2M objects */
LWM2M_IPSO_Digital_Input_T LWM2M_IPSO_Digital_Input[NUM_INS];
LWM2M_IPSO_Digital_Output_T LWM2M_IPSO_Digital_Output[NUM_OUTS];

int main()
{
    /* Register the LWM2M objects with the Server */
    sml_lwm2m_register_object(LWM2M_IPSO_Digital_Input);
    sml_lwm2m_register_object(LWM2M_IPSO_Digital_Output);

    /* Create the device objects */
    sml_i2c_t i2c_bus = sml_i2c_open( I2C_DEV_PATH ); // This is the I2C bus
    sml_gpio_handle_t intr_pin = sml_gpio_open( GPIO_NUM ); // GPIO that the interrupt pin is wired to    
    sml_pca9534_t device = sml_pca9534_create( i2c_bus, ADDR_OFFSET, intr_pin ); 
    
    // Configure device: restart disabled, internal clk, auto-inc, power-up, subaddresses disabled, all-call enabled
    sml_pca9534_set_configuration( device, (1<<NUM_INS)-1 ); // lower pins as ins, upper as outs

    /* Continually read the device and update the LWM2M object */
    while(1)
    {
        int i, data;
   
        // Process inputs
        data = sml_pca9534_get_input(device);
        for( i=0; i<NUM_INS; i++ )
            LWM2M_IPSO_Digital_Input[i].Digital_Input_State = (data>>i) & 1;
            
        // Process outputs
        data = 0;
        for( i=0; i<NUM_OUTS; i++ )            
            data |= LWM2M_IPSO_Digital_Output[i].Digital_Output_State << (i+NUM_INS);
        sml_pca9534_set_output( device, data );  
          
        usleep(100000);
    }

    return 0;
}
