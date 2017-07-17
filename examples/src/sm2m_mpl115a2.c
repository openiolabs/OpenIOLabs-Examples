#include <lwm2m.h> // lwm2m.h is auto-generated

#include <scriptml/i2c.h>
#include <scriptml/mpl115a2.h>
#include <stdint.h>
#include <unistd.h>

/* Hookup details */
#define I2C_DEV_PATH "/dev/i2c-1"

/* Define instances of the LWM2M objects */
LWM2M_IPSO_Pressure_T LWM2M_IPSO_Pressure;

int main()
{
    float a0, b1, b2, c12;
    
    LWM2M_IPSO_Pressure.Sensor_Units = "kPa";
    LWM2M_IPSO_Pressure.Min_Range_Value = 50.0;
    LWM2M_IPSO_Pressure.Max_Range_Value = 115.0;

    /* Register the LWM2M objects with the Server */
    sml_lwm2m_register_object(LWM2M_IPSO_Pressure);
    
    /* Create the device objects */
    sml_i2c_t i2c_bus = sml_i2c_open( I2C_DEV_PATH ); // This is the I2C bus
    sml_mpl115a2_t device = sml_mpl115a2_create( i2c_bus ); 
    
    a0 = (float)sml_mpl115a2_get_a0(device) / 8.0; // Q3
    b1 = (float)sml_mpl115a2_get_b1(device) / 8192.0; // Q13
    b2 = (float)sml_mpl115a2_get_b2(device) / 16384.0; // Q14
    c12 = (float)sml_mpl115a2_get_c12(device) / 65536.0 / 256.0; // Q24

    /* Continually read the device and update the LWM2M object */
    while(1)
    {
        int Padc=0, Tadc=0;
        float Pcomp, pressure;
        sml_mpl115a2_convert( device );
        usleep(100000);

        sml_mpl115a2_get_padc( device, &Padc );
        sml_mpl115a2_get_tadc( device, &Tadc );
        Pcomp = a0 + (b1 + c12*Tadc)*Padc + b2*Tadc;
        pressure = Pcomp * (115.0-50.0) / 1023.0 + 50.0;
        LWM2M_IPSO_Pressure.Sensor_Value = pressure;
    }

    return 0;
}
