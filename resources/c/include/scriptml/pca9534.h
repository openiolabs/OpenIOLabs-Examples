/** @file
 * 
 *  @brief GPIO Extender
 * 
 *  8-bit I2C-bus and SMBus low power I/O port with interrupt
 *  
 *  
 *  Configuration register is really a direction register. Bits set to 1 correspond to inputs and 0 to outputs.
 *  
 *  
 *  
 *  Auto-generated 14 January 2018; do not edit
 *  
 *  Copyright (c) Open IO Labs Ltd 2017
 *  All Rights Reserved
 */

#ifndef __PCA9534_H
#define __PCA9534_H

#include <i2c_regmap.h>
#include <gpio.h>

#define SML_PCA9534_BASE_ADDR 0x20

typedef struct
{
    sml_i2c_regmap_t iic;
    sml_gpio_handle_t intr_gpio;
} sml_pca9534_t;

/**
 *  @brief Create device driver instance
 * 
 *  @param i2c An instance of the I2C driver for the bus on which the device is placed
 *  @param addr_offset The I2C address offset
 *  @param intr_pin An instance of the GPIO driver for the pin connected to the interrupt line
 *  @return Device handle
 */
sml_pca9534_t sml_pca9534_create( sml_i2c_t i2c, int addr_offset, sml_gpio_handle_t intr_pin )
{
    sml_pca9534_t dev;
    dev.intr_gpio = intr_pin;
    dev.iic = sml_i2c_regmap_create( i2c, SML_PCA9534_BASE_ADDR + addr_offset, 0x100, 1 );
    return dev;
} 

/**
 *  @brief Get Input Port register
 * 
 *  @param dev The device handle
 *  @return Input Port register
 */
uint8_t sml_pca9534_get_input( sml_pca9534_t dev )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x0, 1 );
    return _bytes[0];
} 

/**
 *  @brief Set Output Port register
 * 
 *  @param dev The device handle
 *  @param output Output Port register
 */
void sml_pca9534_set_output( sml_pca9534_t dev, uint8_t output )
{
    sml_i2c_regmap_write( dev.iic, &output, 0x1, 1 );
} 

/**
 *  @brief Get Output Port register
 * 
 *  @param dev The device handle
 *  @return Output Port register
 */
uint8_t sml_pca9534_get_output( sml_pca9534_t dev )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x1, 1 );
    return _bytes[0];
} 

/**
 *  @brief Set Polarity Inversion register
 * 
 *  @param dev The device handle
 *  @param polarity Polarity Inversion register
 */
void sml_pca9534_set_polarity( sml_pca9534_t dev, uint8_t polarity )
{
    sml_i2c_regmap_write( dev.iic, &polarity, 0x2, 1 );
} 

/**
 *  @brief Get Polarity Inversion register
 * 
 *  @param dev The device handle
 *  @return Polarity Inversion register
 */
uint8_t sml_pca9534_get_polarity( sml_pca9534_t dev )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x2, 1 );
    return _bytes[0];
} 

/**
 *  @brief Set Configuration register
 * 
 *  @param dev The device handle
 *  @param configuration Configuration register
 */
void sml_pca9534_set_configuration( sml_pca9534_t dev, uint8_t configuration )
{
    sml_i2c_regmap_write( dev.iic, &configuration, 0x3, 1 );
} 

/**
 *  @brief Get Configuration register
 * 
 *  @param dev The device handle
 *  @return Configuration register
 */
uint8_t sml_pca9534_get_configuration( sml_pca9534_t dev )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x3, 1 );
    return _bytes[0];
} 

#endif /* PCA9534_H */
