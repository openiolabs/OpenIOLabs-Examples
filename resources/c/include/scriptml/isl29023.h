/** @file
 * 
 *  @brief ISL29023 device driver
 * 
 *  Detects the level of visible light or infra-red.
 *  =========================
 *  
 *  Program the two `command` registers and then read back from the `data` register.
 *  
 *  
 *  Auto-generated 07 June 2018; do not edit
 *  
 *  Copyright (c) Open IO Labs Ltd 2017
 *  All Rights Reserved
 */

#ifndef __ISL29023_H
#define __ISL29023_H

#include <i2c_regmap.h>
#include <gpio.h>

#define SML_ISL29023_BASE_ADDR 0x44

#define SML_ISL29023_COMMAND_1_MODE_IR_ONCE 0x2
#define SML_ISL29023_COMMAND_1_MODE_IR_CONTINUOUS 0x6
#define SML_ISL29023_COMMAND_1_MODE_ALS_CONTINUOUS 0x5
#define SML_ISL29023_COMMAND_1_MODE_POWER_DOWN 0x0
#define SML_ISL29023_COMMAND_1_MODE_ALS_INTEGRATION_CYCLE 0x1
#define SML_ISL29023_COMMAND_1_PERSIST_1_CYCLE 0x0
#define SML_ISL29023_COMMAND_1_PERSIST_8_CYCLES 0x2
#define SML_ISL29023_COMMAND_1_PERSIST_16_CYCLES 0x3
#define SML_ISL29023_COMMAND_1_PERSIST_4_CYCLES 0x1

#define SML_ISL29023_COMMAND_2_RESOLUTION_4_BIT 0x3
#define SML_ISL29023_COMMAND_2_RESOLUTION_12_BIT 0x1
#define SML_ISL29023_COMMAND_2_RESOLUTION_8_BIT 0x2
#define SML_ISL29023_COMMAND_2_RESOLUTION_16_BIT 0x0
#define SML_ISL29023_COMMAND_2_RANGE_16000_LUX 0x2
#define SML_ISL29023_COMMAND_2_RANGE_64000_LUX 0x3
#define SML_ISL29023_COMMAND_2_RANGE_1000_LUX 0x0
#define SML_ISL29023_COMMAND_2_RANGE_4000_LUX 0x1

typedef struct
{
    sml_i2c_regmap_t iic;
    sml_gpio_handle_t intr_gpio;
} sml_isl29023_t;

/**
 *  @brief Create device driver instance
 * 
 *  @param i2c An instance of the I2C driver for the bus on which the device is placed
 *  @param intr_pin An instance of the GPIO driver for the pin connected to the interrupt line
 *  @return Device handle
 */
sml_isl29023_t sml_isl29023_create( sml_i2c_t i2c, sml_gpio_handle_t intr_pin )
{
    sml_isl29023_t dev;
    dev.intr_gpio = intr_pin;
    dev.iic = sml_i2c_regmap_create( i2c, SML_ISL29023_BASE_ADDR, 0x100, 1 );
    return dev;
} 

/**
 *  @brief Set the device's operation mode
 * 
 *  @param dev The device handle
 *  @param mode operation mode
 *  @param persist interrupt persistance mode
 */
void sml_isl29023_set_command_1( sml_isl29023_t dev, int mode, int persist )
{
    uint8_t _value;
    _value = ((mode & 0x7) << 5) | (persist & 0x3);
    sml_i2c_regmap_write( dev.iic, &_value, 0x0, 1 );
} 

/**
 *  @brief Set the device's resolution and range
 * 
 *  @param dev The device handle
 *  @param resolution ADC resolution
 *  @param range full scale range
 */
void sml_isl29023_set_command_2( sml_isl29023_t dev, int resolution, int range )
{
    uint8_t _value;
    _value = ((resolution & 0x3) << 2) | (range & 0x3);
    sml_i2c_regmap_write( dev.iic, &_value, 0x1, 1 );
} 

/**
 *  @brief Get data registers
 * 
 *  @param dev The device handle
 *  @return data registers
 */
uint16_t sml_isl29023_get_data( sml_isl29023_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x2, 2 );
    return (uint16_t)((int)(_bytes[0]) | ((int)(_bytes[1]) << 8));
} 

/**
 *  @brief Set lower interrupt threshold
 * 
 *  @param dev The device handle
 *  @param int_lt lower interrupt threshold
 */
void sml_isl29023_set_int_lt( sml_isl29023_t dev, uint16_t int_lt )
{
    uint8_t _bytes[2];
    _bytes[0] = int_lt & 0xff;
    _bytes[1] = (int_lt >> 8) & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x4, 2 );
} 

/**
 *  @brief Set upper interrupt threshold
 * 
 *  @param dev The device handle
 *  @param int_ht upper interrupt threshold
 */
void sml_isl29023_set_int_ht( sml_isl29023_t dev, uint16_t int_ht )
{
    uint8_t _bytes[2];
    _bytes[0] = int_ht & 0xff;
    _bytes[1] = (int_ht >> 8) & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x6, 2 );
} 

#endif /* ISL29023_H */
