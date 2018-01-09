/** @file
 * 
 *  @brief LM75B device driver
 * 
 *  LM75B Digital Thermometer 
 *  =========================
 *  
 *  Program the the `conf` register then read the `temp` register
 *  
 *  Auto-generated 09 January 2018; do not edit
 *  
 *  Copyright (c) Open IO Labs Ltd 2017
 *  All Rights Reserved
 */

#ifndef __LM75B_H
#define __LM75B_H

#include <i2c_regmap.h>
#include <gpio.h>

#define SML_LM75B_BASE_ADDR 0x48

#define SML_LM75B_CONF_SHUTDOWN_SHUTDOWN 0x1
#define SML_LM75B_CONF_SHUTDOWN_NORMAL 0x0
#define SML_LM75B_CONF_OS_COMP_INT_INTERRUPT 0x1
#define SML_LM75B_CONF_OS_COMP_INT_COMPARATOR 0x0
#define SML_LM75B_CONF_OS_POL_ACTIVE_HIGH 0x1
#define SML_LM75B_CONF_OS_POL_ACTIVE_LOW 0x0
#define SML_LM75B_CONF_OS_F_QUE_1 0x0
#define SML_LM75B_CONF_OS_F_QUE_2 0x1
#define SML_LM75B_CONF_OS_F_QUE_4 0x2
#define SML_LM75B_CONF_OS_F_QUE_6 0x3

typedef struct
{
    sml_i2c_regmap_t iic;
    sml_gpio_handle_t intr_gpio;
} sml_lm75b_t;

/**
 *  @brief Create device driver instance
 * 
 *  @param i2c An instance of the I2C driver for the bus on which the device is placed
 *  @param addr_offset The I2C address offset
 *  @param intr_pin An instance of the GPIO driver for the pin connected to the interrupt line
 *  @return Device handle
 */
sml_lm75b_t sml_lm75b_create( sml_i2c_t i2c, int addr_offset, sml_gpio_handle_t intr_pin )
{
    sml_lm75b_t dev;
    dev.intr_gpio = intr_pin;
    dev.iic = sml_i2c_regmap_create( i2c, SML_LM75B_BASE_ADDR + addr_offset, 0x100, 0 );
    return dev;
} 

/**
 *  @brief Set configuration
 * 
 *  @param dev The device handle
 *  @param shutdown device operation mode
 *  @param os_comp_int OS operation mode
 *  @param os_pol OS polarity selection
 *  @param os_f_que OS fault queue programming
 */
void sml_lm75b_set_conf( sml_lm75b_t dev, int shutdown, int os_comp_int, int os_pol, int os_f_que )
{
    uint8_t _value;
    _value = (shutdown & 0x1) | ((os_comp_int & 0x1) << 1) | ((os_pol & 0x1) << 2) | ((os_f_que & 0x3) << 3);
    sml_i2c_regmap_write( dev.iic, &_value, 0x1, 1 );
} 

/**
 *  @brief Get temperature
 * 
 *  @param dev The device handle
 *  @return temperature
 */
int16_t sml_lm75b_get_temp( sml_lm75b_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x0, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set overtemperature shutdown threshold
 * 
 *  @param dev The device handle
 *  @param tos overtemperature shutdown threshold
 */
void sml_lm75b_set_tos( sml_lm75b_t dev, int16_t tos )
{
    uint8_t _bytes[2];
    _bytes[0] = (tos >> 8) & 0xff;
    _bytes[1] = tos & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x3, 2 );
} 

/**
 *  @brief Set hysteresis
 * 
 *  @param dev The device handle
 *  @param thyst hysteresis
 */
void sml_lm75b_set_thyst( sml_lm75b_t dev, int16_t thyst )
{
    uint8_t _bytes[2];
    _bytes[0] = (thyst >> 8) & 0xff;
    _bytes[1] = thyst & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x2, 2 );
} 

#endif /* LM75B_H */
