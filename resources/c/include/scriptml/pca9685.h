/** @file
 * 
 *  @brief 16-channel, 12-bit PWM Fm+ I2C-bus LED Controller
 * 
 *  PCA9685 PWM LED Driver
 *  ======================
 *  
 *  The internal clock is 25MHz
 *  
 *  The PWM waveform frequency is `clock frequency` / (`pre_scale` * 4096)
 *  
 *  The device powers up in sleep mode, and must be powered up by clearing the `sleep! bit in the `mode1` register before use.
 *  
 *  The `ai` bit in register `mode1` must be set before any of the `led_on_off` APIs will function correctly, because they use auto-increment to access multiple registers efficiently.
 *  
 *  The device must be in sleep mode before the `pre_scale` register can be updated.
 *  
 *  Wakeup procedure: clear `sleep` bit of register `mode1`. Wait at least 500us for the clock to stabilise. set `restart` bit of `mode1` register.
 *  
 *  Auto-generated 15 December 2017; do not edit
 *  
 *  Copyright (c) Open IO Labs Ltd 2017
 *  All Rights Reserved
 */

#ifndef __PCA9685_H
#define __PCA9685_H

#include <i2c_regmap.h>

#define SML_PCA9685_BASE_ADDR 0x40

#define SML_PCA9685_MODE2_OCH_STOP_COMMAND 0x0
#define SML_PCA9685_MODE2_OCH_ACK 0x1
#define SML_PCA9685_MODE2_OUTDRV_OPEN_DRAIN 0x0
#define SML_PCA9685_MODE2_OUTDRV_TOTEM_POLE 0x1
#define SML_PCA9685_MODE2_OUTNE_0 0x0
#define SML_PCA9685_MODE2_OUTNE_1 0x1
#define SML_PCA9685_MODE2_OUTNE_HI_Z 0x2

typedef struct
{
    sml_i2c_regmap_t iic;
} sml_pca9685_t;

/**
 *  @brief Create device driver instance
 * 
 *  @param i2c An instance of the I2C driver for the bus on which the device is placed
 *  @param addr_offset The I2C address offset
 *  @return Device handle
 */
sml_pca9685_t sml_pca9685_create( sml_i2c_t i2c, int addr_offset )
{
    sml_pca9685_t dev;
    dev.iic = sml_i2c_regmap_create( i2c, SML_PCA9685_BASE_ADDR + addr_offset, 0x100, 1 );
    return dev;
} 

/**
 *  @brief Set mode register 1
 * 
 *  @param dev The device handle
 *  @param restart RESTART logic state and reset
 *  @param extclk external Clock
 *  @param ai register auto-increment enable
 *  @param sleep low power mode
 *  @param sub1 PCA9685 responds to I2C-bus subaddress 1
 *  @param sub2 PCA9685 responds to I2C-bus subaddress 2
 *  @param sub3 PCA9685 responds to I2C-bus subaddress 3
 *  @param allcall PCA9685 responds to LED All Call I2C-bus
 */
void sml_pca9685_set_mode1( sml_pca9685_t dev, int restart, int extclk, int ai, int sleep, int sub1, int sub2, int sub3, int allcall )
{
    uint8_t _value;
    _value = ((restart & 0x1) << 7) | ((extclk & 0x1) << 6) | ((ai & 0x1) << 5) | ((sleep & 0x1) << 4) | ((sub1 & 0x1) << 3) | ((sub2 & 0x1) << 2) | ((sub3 & 0x1) << 1) | (allcall & 0x1);
    sml_i2c_regmap_write( dev.iic, &_value, 0x0, 1 );
} 

/**
 *  @brief Get mode register 1
 * 
 *  @param dev The device handle
 *  @param restart pointer to RESTART logic state and reset bit
 *  @param extclk pointer to external Clock bit
 *  @param ai pointer to register auto-increment enable bit
 *  @param sleep pointer to low power mode bit
 *  @param sub1 pointer to PCA9685 responds to I2C-bus subaddress 1 bit
 *  @param sub2 pointer to PCA9685 responds to I2C-bus subaddress 2 bit
 *  @param sub3 pointer to PCA9685 responds to I2C-bus subaddress 3 bit
 *  @param allcall pointer to PCA9685 responds to LED All Call I2C-bus bit
 */
void sml_pca9685_get_mode1( sml_pca9685_t dev, int* restart, int* extclk, int* ai, int* sleep, int* sub1, int* sub2, int* sub3, int* allcall )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x0, 1 );
    *restart = (_bytes[0] >> 7) & 0x1;
    *extclk = (_bytes[0] >> 6) & 0x1;
    *ai = (_bytes[0] >> 5) & 0x1;
    *sleep = (_bytes[0] >> 4) & 0x1;
    *sub1 = (_bytes[0] >> 3) & 0x1;
    *sub2 = (_bytes[0] >> 2) & 0x1;
    *sub3 = (_bytes[0] >> 1) & 0x1;
    *allcall = _bytes[0] & 0x1;
} 

/**
 *  @brief Set mode register 2
 * 
 *  @param dev The device handle
 *  @param invrt output logic state inverted
 *  @param och output change on
 *  @param outdrv LEDn output configuration (when enabled)
 *  @param outne LEDn output configuration when ~OE = 1 (output drivers not enabled)
 */
void sml_pca9685_set_mode2( sml_pca9685_t dev, int invrt, int och, int outdrv, int outne )
{
    uint8_t _value;
    _value = ((invrt & 0x1) << 4) | ((och & 0x1) << 3) | ((outdrv & 0x1) << 2) | (outne & 0x3);
    sml_i2c_regmap_write( dev.iic, &_value, 0x1, 1 );
} 

/**
 *  @brief Set I2C-bus subaddress
 * 
 *  @param dev The device handle
 *  @param channel Channel number; 0 to 2
 *  @param subadr I2C-bus subaddress
 */
void sml_pca9685_set_subadr( sml_pca9685_t dev, int channel, uint8_t subadr )
{
    sml_i2c_regmap_write( dev.iic, &subadr, 0x2+channel, 1 );
} 

/**
 *  @brief Set LED output and brightness control
 * 
 *  @param dev The device handle
 *  @param channel Channel number; 0 to 15
 *  @param on_count LED on count
 *  @param full_on LED full on
 *  @param off_count LED off count
 *  @param full_off LED full off
 */
void sml_pca9685_set_led_on_off( sml_pca9685_t dev, int channel, int on_count, int full_on, int off_count, int full_off )
{
    uint32_t _value;
    uint8_t _bytes[4];
    _value = (on_count & 0xfff) | ((full_on & 0x1) << 12) | ((off_count & 0xfff) << 16) | ((full_off & 0x1) << 28);
    _bytes[0] = _value & 0xff;
    _bytes[1] = (_value >> 8) & 0xff;
    _bytes[2] = (_value >> 16) & 0xff;
    _bytes[3] = (_value >> 24) & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x6+channel*4, 4 );
} 

/**
 *  @brief Set all the LED control registers
 * 
 *  @param dev The device handle
 *  @param on_count LED on count
 *  @param full_on LED full on
 *  @param off_count LED off count
 *  @param full_off LED full off
 */
void sml_pca9685_set_all_led_on_off( sml_pca9685_t dev, int on_count, int full_on, int off_count, int full_off )
{
    uint32_t _value;
    uint8_t _bytes[4];
    _value = (on_count & 0xfff) | ((full_on & 0x1) << 12) | ((off_count & 0xfff) << 16) | ((full_off & 0x1) << 28);
    _bytes[0] = _value & 0xff;
    _bytes[1] = (_value >> 8) & 0xff;
    _bytes[2] = (_value >> 16) & 0xff;
    _bytes[3] = (_value >> 24) & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0xfa, 4 );
} 

/**
 *  @brief Set prescaler for PWM output frequency
 * 
 *  @param dev The device handle
 *  @param pre_scale prescaler for PWM output frequency
 */
void sml_pca9685_set_pre_scale( sml_pca9685_t dev, uint8_t pre_scale )
{
    sml_i2c_regmap_write( dev.iic, &pre_scale, 0xfe, 1 );
} 

#endif /* PCA9685_H */
