#include <lwm2m.h> // lwm2m.h is auto-generated

#include <scriptml/i2c.h>
#include <scriptml/gpio.h>
#include <scriptml/isl29023.h>

#include <stdint.h>
#include <unistd.h>

/* Hookup details */
#define I2C_DEV_PATH "/dev/i2c-1"
#define GPIO_NUM "6"

unsigned resolution = SML_ISL29023_COMMAND_2_RESOLUTION_16_BIT;
unsigned range = SML_ISL29023_COMMAND_2_RANGE_1000_LUX;
float r_ext = 499000.0; // Rext is nominally 499Kohm

/* [0] is visible light, [1] is IR */
LWM2M_IPSO_Illuminance_T LWM2M_IPSO_Illuminance[2];

int main()
{
    float fs, res;
    switch( resolution )
    {
        case SML_ISL29023_COMMAND_2_RESOLUTION_4_BIT:
            res = 16.0;
            break;
        case SML_ISL29023_COMMAND_2_RESOLUTION_8_BIT:
            res = 256.0;
            break;
        case SML_ISL29023_COMMAND_2_RESOLUTION_12_BIT:
            res = 4096.0;
            break;
        case SML_ISL29023_COMMAND_2_RESOLUTION_16_BIT:
            res = 65536.0;
            break;            
    }
    switch( range )
    {
        case SML_ISL29023_COMMAND_2_RANGE_1000_LUX:
            fs = 1000.0;
            break;
        case SML_ISL29023_COMMAND_2_RANGE_4000_LUX:
            fs = 4000.0;
            break;
        case SML_ISL29023_COMMAND_2_RANGE_16000_LUX:
            fs = 16000.0;
            break;
        case SML_ISL29023_COMMAND_2_RANGE_64000_LUX:
            fs = 64000.0;
            break;            
    }
    float scale = fs / res * 499000.0 / r_ext;    
    
    /* Initialise constant-valued resources */
    LWM2M_IPSO_Illuminance[0].Sensor_Units = "lux"; 
    LWM2M_IPSO_Illuminance[0].Min_Range_Value = 0;
    LWM2M_IPSO_Illuminance[0].Max_Range_Value = fs;        
    LWM2M_IPSO_Illuminance[1].Sensor_Units = "lux"; 
    LWM2M_IPSO_Illuminance[1].Min_Range_Value = 0;
    LWM2M_IPSO_Illuminance[1].Max_Range_Value = fs;
    
    /* Register the LWM2M objects with the Server */
    sml_lwm2m_register_object(LWM2M_IPSO_Illuminance);

    /* Create the device objects */
    sml_i2c_t i2c_bus = sml_i2c_open( I2C_DEV_PATH ); // This is the I2C bus
    sml_gpio_handle_t intr_pin = sml_gpio_open( GPIO_NUM ); // GPIO that the interrupt pin is wired to    
    sml_isl29023_t device = sml_isl29023_create( i2c_bus, intr_pin ); 
    
    /* Initialise the device */    
    sml_isl29023_set_command_1( device, 
                                SML_ISL29023_COMMAND_1_MODE_ALS_CONTINUOUS,  // NOTE: cannot place device in continuous IR and ALS TODO
                                SML_ISL29023_COMMAND_1_PERSIST_1_CYCLE ); 
    sml_isl29023_set_command_2( device, resolution, range );  

    /* Continually read the device and update the LWM2M object */
    while(1)
    {
        LWM2M_IPSO_Illuminance[0].Sensor_Value = sml_isl29023_get_data(device) * scale;
        usleep(100000);
    }

    return 0;
}
