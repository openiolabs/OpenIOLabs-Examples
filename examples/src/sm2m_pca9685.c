#include <lwm2m.h> // lwm2m.h is auto-generated

#include <scriptml/i2c.h>
#include <scriptml/pca9685.h>

#include <stdint.h>
#include <unistd.h>

/* Hookup details */
#define I2C_DEV_PATH "/dev/i2c-1"
#define ADDR_OFFSET 0x38
#define NUM_LEDS 16

/* Define instances of the LWM2M objects */
LWM2M_IPSO_Light_Control_T LWM2M_IPSO_Light_Control[NUM_LEDS];

int main()
{
    /* Register the LWM2M objects with the Server */
    sml_lwm2m_register_object(LWM2M_IPSO_Light_Control);

    /* Create the device objects */
    sml_i2c_t i2c_bus = sml_i2c_open( I2C_DEV_PATH ); // This is the I2C bus
    sml_pca9685_t device = sml_pca9685_create( i2c_bus, ADDR_OFFSET ); 
    
    // Configure device: restart disabled, internal clk, auto-inc, power-up, subaddresses disabled, all-call enabled
    sml_pca9685_set_mode1( device, 0, 0, 1, 0, 0, 0, 0, 1 ); 
    usleep(500);
    // Configure device: restart enabled, internal clk, auto-inc, power-up, subaddresses disabled, all-call enabled
    sml_pca9685_set_mode1( device, 1, 0, 1, 0, 0, 0, 0, 1 ); 
    sml_pca9685_set_mode2( device, 0, SML_PCA9685_MODE2_OCH_ACK, SML_PCA9685_MODE2_OUTDRV_TOTEM_POLE, SML_PCA9685_MODE2_OUTNE_0 );
    sml_pca9685_set_all_led_on_off(	device, 0, 0, 0, 0 );

    /* Continually read the device and update the LWM2M object */
    while(1)
    {
        int i, on_count, full_on, off_count, full_off;
        for( i=0; i<NUM_LEDS; i++ )        
        {
            on_count = i*4096/16; // Distribute phasing to minimise power supply burst loading
            off_count = (on_count + (LWM2M_IPSO_Light_Control[i].Dimmer*4096+50)/100) % 4096;
            full_on = LWM2M_IPSO_Light_Control[i].OnOff && LWM2M_IPSO_Light_Control[i].Dimmer==100;
            full_off = !LWM2M_IPSO_Light_Control[i].OnOff || LWM2M_IPSO_Light_Control[i].Dimmer==0;
            sml_pca9685_set_led_on_off(	device, i, on_count, full_on, off_count, full_off );
        }
        usleep(100000);
    }

    return 0;
}
