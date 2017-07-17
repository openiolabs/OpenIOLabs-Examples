#include <lwm2m.h> // lwm2m.h is auto-generated

#include <scriptml/i2c.h>
#include <scriptml/gpio.h>
#include <scriptml/mpu6050.h>

#include <stdint.h>
#include <unistd.h>
#include <assert.h>

/* Hookup details */
#define I2C_DEV_PATH "/dev/i2c-1"
#define GPIO_NUM "21"
#define ADDR_OFFSET 0

/* Chosen configuration */
unsigned afs_sel = SML_MPU6050_ACCEL_CONFIG_AFS_SEL_2;
unsigned gfs_sel = SML_MPU6050_GYRO_CONFIG_FS_SEL_2000;

/* Define instances of the LWM2M objects */
LWM2M_IPSO_Accelerometer_T LWM2M_IPSO_Accelerometer;
LWM2M_IPSO_Gyrometer_T LWM2M_IPSO_Gyrometer;

int main()
{
    float afs, gfs, raw_fs = 32768.0;
    switch( afs_sel )
    {
        case SML_MPU6050_ACCEL_CONFIG_AFS_SEL_2:
            afs = 2.0;
            break;
        case SML_MPU6050_ACCEL_CONFIG_AFS_SEL_4:
            afs = 4.0;
            break;
        case SML_MPU6050_ACCEL_CONFIG_AFS_SEL_8:
            afs = 8.0;
            break;
        case SML_MPU6050_ACCEL_CONFIG_AFS_SEL_16:
            afs = 16.0;
            break;            
    }
    switch( gfs_sel )
    {
        case SML_MPU6050_GYRO_CONFIG_FS_SEL_250:
            gfs = 250.0;
            break;
        case SML_MPU6050_GYRO_CONFIG_FS_SEL_500:
            gfs = 500.0;
            break;
        case SML_MPU6050_GYRO_CONFIG_FS_SEL_1000:
            gfs = 1000.0;
            break;
        case SML_MPU6050_GYRO_CONFIG_FS_SEL_2000:
            gfs = 2000.0;
            break;
    }    

    /* Initialise constant-valued resources */
    LWM2M_IPSO_Accelerometer.Sensor_Units = "*g"; // Note: multiple of earth's magnetic field, not grammes
    LWM2M_IPSO_Accelerometer.Min_Range_Value = -afs;
    LWM2M_IPSO_Accelerometer.Max_Range_Value = afs;        
    LWM2M_IPSO_Gyrometer.Sensor_Units = "degrees/s"; // degrees per second
    LWM2M_IPSO_Gyrometer.Min_Range_Value = -gfs;
    LWM2M_IPSO_Gyrometer.Max_Range_Value = gfs;
    
    /* Register the LWM2M objects with the Server */
    sml_lwm2m_register_object(LWM2M_IPSO_Accelerometer);
    sml_lwm2m_register_object(LWM2M_IPSO_Gyrometer);

    /* Create the device objects */
    sml_i2c_t i2c_bus = sml_i2c_open( I2C_DEV_PATH ); // This is the I2C bus
    sml_gpio_handle_t intr_pin = sml_gpio_open( GPIO_NUM ); // GPIO that the interrupt pin is wired to    
    sml_mpu6050_t device = sml_mpu6050_create( i2c_bus, ADDR_OFFSET, intr_pin ); 
        
    /* Confirm device present */
    int who;
    sml_mpu6050_get_who_am_i( device, &who );
    assert( who == 0x34 );

    /* Initialise the device */
    sml_mpu6050_set_pwr_mgmt_1( device, 
                                0, // out of reset 
                                0, // out of sleep 
                                0, // out of cycle 
                                0, // do not disable temperature
                                SML_MPU6050_PWR_MGMT_1_CLKSEL_INTERNAL ); 
    sml_mpu6050_set_gyro_config( device, gfs_sel );
    sml_mpu6050_set_accel_config( device, afs_sel );

    /* Continually read the device and update the LWM2M object */
    while(1)
    {
        LWM2M_IPSO_Accelerometer.X_Value = sml_mpu6050_get_accel_xout(device) * afs / raw_fs;
        LWM2M_IPSO_Accelerometer.Y_Value = sml_mpu6050_get_accel_yout(device) * afs / raw_fs;
        LWM2M_IPSO_Accelerometer.Z_Value = sml_mpu6050_get_accel_zout(device) * afs / raw_fs;
        LWM2M_IPSO_Gyrometer.X_Value = sml_mpu6050_get_gyro_xout(device) * gfs / raw_fs;
        LWM2M_IPSO_Gyrometer.Y_Value = sml_mpu6050_get_gyro_yout(device) * gfs / raw_fs;
        LWM2M_IPSO_Gyrometer.Z_Value = sml_mpu6050_get_gyro_zout(device) * gfs / raw_fs;
        usleep(100000); // 100ms
    }

    return 0;
}
