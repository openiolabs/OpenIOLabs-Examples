/** @file
 * 
 *  @brief Miniature I2C Digital Barometer
 * 
 *  MPL115A2 Digital Barometer 
 *  ==========================
 *  
 *  Read out the constants `a0`, `b1`, `b2` and `c12`, then `convert` and finally read back `Padc` and `Tadc`
 *  
 *  Auto-generated 01 February 2018; do not edit
 *  
 *  Copyright (c) Open IO Labs Ltd 2017
 *  All Rights Reserved
 */

#ifndef __MPL115A2_H
#define __MPL115A2_H

#include <i2c_regmap.h>

#define SML_MPL115A2_BASE_ADDR 0x60

typedef struct
{
    sml_i2c_regmap_t iic;
} sml_mpl115a2_t;

/**
 *  @brief Create device driver instance
 * 
 *  @param i2c An instance of the I2C driver for the bus on which the device is placed
 *  @return Device handle
 */
sml_mpl115a2_t sml_mpl115a2_create( sml_i2c_t i2c )
{
    sml_mpl115a2_t dev;
    dev.iic = sml_i2c_regmap_create( i2c, SML_MPL115A2_BASE_ADDR, 0x100, 1 );
    return dev;
} 

/**
 *  @brief Get Pressure ADC output value
 * 
 *  @param dev The device handle
 *  @param padc pointer to Pressure ADC output value
 */
void sml_mpl115a2_get_padc( sml_mpl115a2_t dev, int* padc )
{
    uint16_t _value;
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x0, 2 );
    _value = ((int)(_bytes[0]) << 8) | (int)(_bytes[1]);
    *padc = (_value >> 6) & 0x3ff;
} 

/**
 *  @brief Get Temperature ADC output value
 * 
 *  @param dev The device handle
 *  @param tadc pointer to Temperature ADC output value
 */
void sml_mpl115a2_get_tadc( sml_mpl115a2_t dev, int* tadc )
{
    uint16_t _value;
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x2, 2 );
    _value = ((int)(_bytes[0]) << 8) | (int)(_bytes[1]);
    *tadc = (_value >> 6) & 0x3ff;
} 

/**
 *  @brief Get a0 coefficient
 * 
 *  @param dev The device handle
 *  @return a0 coefficient
 */
int16_t sml_mpl115a2_get_a0( sml_mpl115a2_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x4, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Get b1 coefficient
 * 
 *  @param dev The device handle
 *  @return b1 coefficient
 */
int16_t sml_mpl115a2_get_b1( sml_mpl115a2_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x6, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Get b2 coefficient
 * 
 *  @param dev The device handle
 *  @return b2 coefficient
 */
int16_t sml_mpl115a2_get_b2( sml_mpl115a2_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x8, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Get c12 coefficient
 * 
 *  @param dev The device handle
 *  @return c12 coefficient
 */
int16_t sml_mpl115a2_get_c12( sml_mpl115a2_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0xa, 2 );
    return (int16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Start Pressure and Temperature Conversion
 * 
 *  @param dev The device handle
 */
void sml_mpl115a2_convert( sml_mpl115a2_t dev )
{
    uint8_t _value;
    _value = 0;
    sml_i2c_regmap_write( dev.iic, &_value, 0x12, 1 );
} 

#endif /* MPL115A2_H */
