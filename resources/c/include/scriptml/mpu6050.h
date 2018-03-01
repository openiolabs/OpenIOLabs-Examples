/** @file
 * 
 *  @brief MPU6050 device driver
 * 
 *  MPU5060 Digital Gyroscope and Accelerometer 
 *  ===========================================
 *  
 *  Read `who_am_i` to confirm device presence.
 *  
 *  Write `pwr_mgmt_1` and `pwr_mgmt_2` to configure the device and take it out of sleep.
 *  
 *  Read raw values from `accel_xout` etc and `gyro_xout` etc.
 *  
 *  Perform conversions as specified by the data sheet.
 *  
 *  
 *  
 *  Auto-generated 01 March 2018; do not edit
 *  
 *  Copyright (c) Open IO Labs Ltd 2017
 *  All Rights Reserved
 */

#ifndef __MPU6050_H
#define __MPU6050_H

#include <i2c_regmap.h>
#include <gpio.h>

#define SML_MPU6050_BASE_ADDR 0x68

#define SML_MPU6050_CONFIG_EXT_SYNC_SET_ACCEL_YOUT 0x6
#define SML_MPU6050_CONFIG_EXT_SYNC_SET_GYRO_XOUT 0x2
#define SML_MPU6050_CONFIG_EXT_SYNC_SET_GYRO_ZOUT 0x4
#define SML_MPU6050_CONFIG_EXT_SYNC_SET_ACCEL_ZOUT 0x7
#define SML_MPU6050_CONFIG_EXT_SYNC_SET_DISABLED 0x0
#define SML_MPU6050_CONFIG_EXT_SYNC_SET_TEMP_OUT 0x1
#define SML_MPU6050_CONFIG_EXT_SYNC_SET_ACCEL_XOUT 0x5
#define SML_MPU6050_CONFIG_EXT_SYNC_SET_GYRO_YOUT 0x3

#define SML_MPU6050_GYRO_CONFIG_FS_SEL_250 0x0
#define SML_MPU6050_GYRO_CONFIG_FS_SEL_2000 0x3
#define SML_MPU6050_GYRO_CONFIG_FS_SEL_500 0x1
#define SML_MPU6050_GYRO_CONFIG_FS_SEL_1000 0x2

#define SML_MPU6050_ACCEL_CONFIG_AFS_SEL_8 0x2
#define SML_MPU6050_ACCEL_CONFIG_AFS_SEL_2 0x0
#define SML_MPU6050_ACCEL_CONFIG_AFS_SEL_4 0x1
#define SML_MPU6050_ACCEL_CONFIG_AFS_SEL_16 0x3

#define SML_MPU6050_PWR_MGMT_1_CLKSEL_PLL_19M 0x5
#define SML_MPU6050_PWR_MGMT_1_CLKSEL_STOP 0x7
#define SML_MPU6050_PWR_MGMT_1_CLKSEL_INTERNAL 0x0
#define SML_MPU6050_PWR_MGMT_1_CLKSEL_PLL_X 0x1
#define SML_MPU6050_PWR_MGMT_1_CLKSEL_PLL_Y 0x2
#define SML_MPU6050_PWR_MGMT_1_CLKSEL_PLL_Z 0x3
#define SML_MPU6050_PWR_MGMT_1_CLKSEL_PLL_32K 0x4

#define SML_MPU6050_PWR_MGMT_2_LP_WAKE_CTRL_20 0x2
#define SML_MPU6050_PWR_MGMT_2_LP_WAKE_CTRL_1_25 0x0
#define SML_MPU6050_PWR_MGMT_2_LP_WAKE_CTRL_5 0x1
#define SML_MPU6050_PWR_MGMT_2_LP_WAKE_CTRL_40 0x3

typedef struct
{
    sml_i2c_regmap_t iic;
    sml_gpio_handle_t intr_gpio;
} sml_mpu6050_t;

/**
 *  @brief Create device driver instance
 * 
 *  @param i2c An instance of the I2C driver for the bus on which the device is placed
 *  @param addr_offset The I2C address offset
 *  @param intr_pin An instance of the GPIO driver for the pin connected to the interrupt line
 *  @return Device handle
 */
sml_mpu6050_t sml_mpu6050_create( sml_i2c_t i2c, int addr_offset, sml_gpio_handle_t intr_pin )
{
    sml_mpu6050_t dev;
    dev.intr_gpio = intr_pin;
    dev.iic = sml_i2c_regmap_create( i2c, SML_MPU6050_BASE_ADDR + addr_offset, 0x100, 1 );
    return dev;
} 

/**
 *  @brief Set sample rate divisor
 * 
 *  @param dev The device handle
 *  @param smprt_div sample rate divisor
 */
void sml_mpu6050_set_smprt_div( sml_mpu6050_t dev, uint8_t smprt_div )
{
    sml_i2c_regmap_write( dev.iic, &smprt_div, 0x19, 1 );
} 

/**
 *  @brief Get sample rate divisor
 * 
 *  @param dev The device handle
 *  @return sample rate divisor
 */
uint8_t sml_mpu6050_get_smprt_div( sml_mpu6050_t dev )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x19, 1 );
    return _bytes[0];
} 

/**
 *  @brief Set configuration
 * 
 *  @param dev The device handle
 *  @param ext_sync_set external frame sync
 *  @param dlpf_cfg digital low-pass filter
 */
void sml_mpu6050_set_config( sml_mpu6050_t dev, int ext_sync_set, int dlpf_cfg )
{
    uint8_t _value;
    _value = ((ext_sync_set & 0x7) << 3) | (dlpf_cfg & 0x7);
    sml_i2c_regmap_write( dev.iic, &_value, 0x1a, 1 );
} 

/**
 *  @brief Set gyroscope configuration
 * 
 *  @param dev The device handle
 *  @param fs_sel full-scale selection
 */
void sml_mpu6050_set_gyro_config( sml_mpu6050_t dev, int fs_sel )
{
    uint8_t _value;
    _value = ((fs_sel & 0x3) << 3);
    sml_i2c_regmap_write( dev.iic, &_value, 0x1b, 1 );
} 

/**
 *  @brief Set accelerometer configuration
 * 
 *  @param dev The device handle
 *  @param afs_sel accelerometer full-scale selection
 */
void sml_mpu6050_set_accel_config( sml_mpu6050_t dev, int afs_sel )
{
    uint8_t _value;
    _value = ((afs_sel & 0x3) << 3);
    sml_i2c_regmap_write( dev.iic, &_value, 0x1c, 1 );
} 

/**
 *  @brief Set FIFO enable
 * 
 *  @param dev The device handle
 *  @param temp_fifo_en enable TEMP_OUT to be written to FIFO
 *  @param xg_fifo_en enable GYRO_XOUT to be written to FIFO
 *  @param yg_fifo_en enable GYRO_YOUT to be written to FIFO
 *  @param zg_fifo_en enable GYRO_ZOUT to be written to FIFO
 *  @param accel_fifo_en enable ACCEL_XOUT, ACCEL_YOUT and ACCEL_ZOUT to be written to FIFO
 *  @param slv2_fifo_en enable EXT_SENS_DATA for slave 2 to be written to FIFO
 *  @param slv1_fifo_en enable EXT_SENS_DATA for slave 1 to be written to FIFO
 *  @param slv0_fifo_en enable EXT_SENS_DATA for slave 0 to be written to FIFO
 */
void sml_mpu6050_set_fifo_en( sml_mpu6050_t dev, int temp_fifo_en, int xg_fifo_en, int yg_fifo_en, int zg_fifo_en, int accel_fifo_en, int slv2_fifo_en, int slv1_fifo_en, int slv0_fifo_en )
{
    uint8_t _value;
    _value = ((temp_fifo_en & 0x1) << 7) | ((xg_fifo_en & 0x1) << 6) | ((yg_fifo_en & 0x1) << 5) | ((zg_fifo_en & 0x1) << 4) | ((accel_fifo_en & 0x1) << 3) | ((slv2_fifo_en & 0x1) << 2) | ((slv1_fifo_en & 0x1) << 1) | (slv0_fifo_en & 0x1);
    sml_i2c_regmap_write( dev.iic, &_value, 0x23, 1 );
} 

/**
 *  @brief Set int pin/bypass enable configuration
 * 
 *  @param dev The device handle
 *  @param int_level int pin active low
 *  @param int_open int pin open drain
 *  @param latch_int_en int pin held high until int cleared
 *  @param int_rd_clear int bit cleared by any read
 *  @param fsync_int_level FSYNC int pin active low
 *  @param fsync_int_en enable FSYNC int
 *  @param i2c_bypass_en enable host access to aux I2C
 */
void sml_mpu6050_set_int_pin_cfg( sml_mpu6050_t dev, int int_level, int int_open, int latch_int_en, int int_rd_clear, int fsync_int_level, int fsync_int_en, int i2c_bypass_en )
{
    uint8_t _value;
    _value = ((int_level & 0x1) << 7) | ((int_open & 0x1) << 6) | ((latch_int_en & 0x1) << 5) | ((int_rd_clear & 0x1) << 4) | ((fsync_int_level & 0x1) << 3) | ((fsync_int_en & 0x1) << 2) | ((i2c_bypass_en & 0x1) << 1);
    sml_i2c_regmap_write( dev.iic, &_value, 0x37, 1 );
} 

/**
 *  @brief Set interrupt enable
 * 
 *  @param dev The device handle
 *  @param fifo_oflow_en enable FIFO overflow interrupt
 *  @param i2c_mst_int_en enable master I2C interrupt
 *  @param data_ready_en enable data ready I2C interrupt
 */
void sml_mpu6050_set_int_enable( sml_mpu6050_t dev, int fifo_oflow_en, int i2c_mst_int_en, int data_ready_en )
{
    uint8_t _value;
    _value = ((fifo_oflow_en & 0x1) << 4) | ((i2c_mst_int_en & 0x1) << 3) | (data_ready_en & 0x1);
    sml_i2c_regmap_write( dev.iic, &_value, 0x38, 1 );
} 

/**
 *  @brief Get interrupt status
 * 
 *  @param dev The device handle
 *  @param fifo_oflow_int pointer to FIFO overflow interrupt generated bit
 *  @param i2c_mst_int_int pointer to master I2C interrupt generated bit
 *  @param data_ready_int pointer to data ready I2C interrupt generated bit
 */
void sml_mpu6050_get_int_status( sml_mpu6050_t dev, int* fifo_oflow_int, int* i2c_mst_int_int, int* data_ready_int )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x3a, 1 );
    *fifo_oflow_int = (_bytes[0] >> 4) & 0x1;
    *i2c_mst_int_int = (_bytes[0] >> 3) & 0x1;
    *data_ready_int = _bytes[0] & 0x1;
} 

/**
 *  @brief Get accelerometer measurement
 * 
 *  @param dev The device handle
 *  @return accelerometer measurement
 */
int16_t sml_mpu6050_get_accel_xout( sml_mpu6050_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x3b, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Get accelerometer measurement
 * 
 *  @param dev The device handle
 *  @return accelerometer measurement
 */
int16_t sml_mpu6050_get_accel_yout( sml_mpu6050_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x3d, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Get accelerometer measurement
 * 
 *  @param dev The device handle
 *  @return accelerometer measurement
 */
int16_t sml_mpu6050_get_accel_zout( sml_mpu6050_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x3f, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Get temperature measurement
 * 
 *  @param dev The device handle
 *  @return temperature measurement
 */
int16_t sml_mpu6050_get_temp_out( sml_mpu6050_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x41, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Get gyroscope measurement
 * 
 *  @param dev The device handle
 *  @return gyroscope measurement
 */
int16_t sml_mpu6050_get_gyro_xout( sml_mpu6050_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x43, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Get gyroscope measurement
 * 
 *  @param dev The device handle
 *  @return gyroscope measurement
 */
int16_t sml_mpu6050_get_gyro_yout( sml_mpu6050_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x45, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Get gyroscope measurement
 * 
 *  @param dev The device handle
 *  @return gyroscope measurement
 */
int16_t sml_mpu6050_get_gyro_zout( sml_mpu6050_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x47, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set signal path reset
 * 
 *  @param dev The device handle
 *  @param gyro_reset reset gyroscope analog and digital signal paths
 *  @param accel_reset reset accelerometer analog and digital signal paths
 *  @param temp_reset reset temperature sensor analog and digital signal paths
 */
void sml_mpu6050_set_signal_path_reset( sml_mpu6050_t dev, int gyro_reset, int accel_reset, int temp_reset )
{
    uint8_t _value;
    _value = ((gyro_reset & 0x1) << 2) | ((accel_reset & 0x1) << 1) | (temp_reset & 0x1);
    sml_i2c_regmap_write( dev.iic, &_value, 0x68, 1 );
} 

/**
 *  @brief Set user control
 * 
 *  @param dev The device handle
 *  @param fifo_en enable FIFO operations
 *  @param i2c_mst_en enable I2C master mode
 *  @param i2c_if_dis disable I2C interface
 *  @param fifo_reset reset FIFO buffer
 *  @param i2c_mst_reset reset I2C master
 *  @param sig_cond_reset reset signal paths and interrupt condition
 */
void sml_mpu6050_set_user_ctrl( sml_mpu6050_t dev, int fifo_en, int i2c_mst_en, int i2c_if_dis, int fifo_reset, int i2c_mst_reset, int sig_cond_reset )
{
    uint8_t _value;
    _value = ((fifo_en & 0x1) << 6) | ((i2c_mst_en & 0x1) << 5) | ((i2c_if_dis & 0x1) << 4) | ((fifo_reset & 0x1) << 2) | ((i2c_mst_reset & 0x1) << 1) | (sig_cond_reset & 0x1);
    sml_i2c_regmap_write( dev.iic, &_value, 0x6a, 1 );
} 

/**
 *  @brief Set power management 1
 * 
 *  @param dev The device handle
 *  @param device_reset reset the entire device
 *  @param sleep low power sleep mode
 *  @param cycle cycle between sleep and sampling
 *  @param temp_dis disable temperature sensor
 *  @param clksel clock source
 */
void sml_mpu6050_set_pwr_mgmt_1( sml_mpu6050_t dev, int device_reset, int sleep, int cycle, int temp_dis, int clksel )
{
    uint8_t _value;
    _value = ((device_reset & 0x1) << 7) | ((sleep & 0x1) << 6) | ((cycle & 0x1) << 5) | ((temp_dis & 0x1) << 3) | (clksel & 0x7);
    sml_i2c_regmap_write( dev.iic, &_value, 0x6b, 1 );
} 

/**
 *  @brief Set power management 2
 * 
 *  @param dev The device handle
 *  @param lp_wake_ctrl low power wakeup frequency
 *  @param stby_xa x-axis accelerometer into standby mode
 *  @param stby_ya y-axis accelerometer into standby mode
 *  @param stby_za z-axis accelerometer into standby mode
 *  @param stby_xg x-axis gyroscope into standby mode
 *  @param stby_yg y-axis gyroscope into standby mode
 *  @param stby_zg z-axis gyroscope into standby mode
 */
void sml_mpu6050_set_pwr_mgmt_2( sml_mpu6050_t dev, int lp_wake_ctrl, int stby_xa, int stby_ya, int stby_za, int stby_xg, int stby_yg, int stby_zg )
{
    uint8_t _value;
    _value = ((lp_wake_ctrl & 0x3) << 6) | ((stby_xa & 0x1) << 5) | ((stby_ya & 0x1) << 4) | ((stby_za & 0x1) << 3) | ((stby_xg & 0x1) << 2) | ((stby_yg & 0x1) << 1) | (stby_zg & 0x1);
    sml_i2c_regmap_write( dev.iic, &_value, 0x6c, 1 );
} 

/**
 *  @brief Get FIFO count register
 * 
 *  @param dev The device handle
 *  @return FIFO count register
 */
uint16_t sml_mpu6050_get_fifo_count( sml_mpu6050_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x72, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set FIFO read write
 * 
 *  @param dev The device handle
 *  @param fifo_r_w FIFO read write
 */
void sml_mpu6050_set_fifo_r_w( sml_mpu6050_t dev, uint8_t fifo_r_w )
{
    sml_i2c_regmap_write( dev.iic, &fifo_r_w, 0x74, 1 );
} 

/**
 *  @brief Get FIFO read write
 * 
 *  @param dev The device handle
 *  @return FIFO read write
 */
uint8_t sml_mpu6050_get_fifo_r_w( sml_mpu6050_t dev )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x74, 1 );
    return _bytes[0];
} 

/**
 *  @brief Get who am I
 * 
 *  @param dev The device handle
 *  @param who_am_i pointer to who am I
 */
void sml_mpu6050_get_who_am_i( sml_mpu6050_t dev, int* who_am_i )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x75, 1 );
    *who_am_i = (_bytes[0] >> 1) & 0x3f;
} 

#endif /* MPU6050_H */
