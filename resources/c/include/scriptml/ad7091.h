/** @file
 * 
 *  @brief Quad channel 12 bit ADC
 * 
 *  The ADI AD7091R quad channel ADC with 12 bits resolution, accessed via the I2C interface.
 *  
 *  Auto-generated 05 February 2018; do not edit
 *  
 *  Copyright (c) Open IO Labs Ltd 2017
 *  All Rights Reserved
 */

#ifndef __AD7091_H
#define __AD7091_H

#include <i2c_regmap.h>

#define SML_AD7091_BASE_ADDR 0x22

#define SML_AD7091_CONV_RES_ALERT_FLAG_NO_ALERT 0x0
#define SML_AD7091_CONV_RES_ALERT_FLAG_ALERT 0x1
#define SML_AD7091_CONV_RES_CHAN_CH0 0x0
#define SML_AD7091_CONV_RES_CHAN_CH1 0x1
#define SML_AD7091_CONV_RES_CHAN_CH2 0x2
#define SML_AD7091_CONV_RES_CHAN_CH3 0x3

#define SML_AD7091_CHANNEL_REGISTER_CH0_DISABLED 0x0
#define SML_AD7091_CHANNEL_REGISTER_CH0_ENABLED 0x1
#define SML_AD7091_CHANNEL_REGISTER_CH1_DISABLED 0x0
#define SML_AD7091_CHANNEL_REGISTER_CH1_ENABLED 0x1
#define SML_AD7091_CHANNEL_REGISTER_CH2_DISABLED 0x0
#define SML_AD7091_CHANNEL_REGISTER_CH2_ENABLED 0x1
#define SML_AD7091_CHANNEL_REGISTER_CH3_DISABLED 0x0
#define SML_AD7091_CHANNEL_REGISTER_CH3_ENABLED 0x1

#define SML_AD7091_CONF_REG_P_DOWN_MODE_0 0x0
#define SML_AD7091_CONF_REG_P_DOWN_MODE_1 0x1
#define SML_AD7091_CONF_REG_P_DOWN_MODE_2 0x2
#define SML_AD7091_CONF_REG_P_DOWN_MODE_3 0x3
#define SML_AD7091_CONF_REG_GPO1_DRIVE_0 0x0
#define SML_AD7091_CONF_REG_GPO1_DRIVE_1 0x1
#define SML_AD7091_CONF_REG_ALERT_POL_OR_GPO0_PIN_ACTIVE_LOW 0x0
#define SML_AD7091_CONF_REG_ALERT_POL_OR_GPO0_PIN_ACTIVE_HIGH 0x1
#define SML_AD7091_CONF_REG_ALERT_EN_OR_GPO0_USED_FOR_GPO0 0x0
#define SML_AD7091_CONF_REG_ALERT_EN_OR_GPO0_USED_FOR_ALERT 0x1
#define SML_AD7091_CONF_REG_BUSY_NOT_USED_FOR_BUSY 0x0
#define SML_AD7091_CONF_REG_BUSY_USED_FOR_BUSY 0x1
#define SML_AD7091_CONF_REG_CYCLE_TIMER_100_US 0x0
#define SML_AD7091_CONF_REG_CYCLE_TIMER_200_US 0x1
#define SML_AD7091_CONF_REG_CYCLE_TIMER_400_US 0x2
#define SML_AD7091_CONF_REG_CYCLE_TIMER_800_US 0x3
#define SML_AD7091_CONF_REG_AUTO_MODE_SAMP_OR_CMD_MODE 0x0
#define SML_AD7091_CONF_REG_AUTO_MODE_AUTO_OR_SAMP_MODE 0x1
#define SML_AD7091_CONF_REG_SRST_DONT_ACTIVATE 0x0
#define SML_AD7091_CONF_REG_SRST_ACTIVATE 0x1
#define SML_AD7091_CONF_REG_CMD_SAMP_OR_AUTO_MODE 0x0
#define SML_AD7091_CONF_REG_CMD_CMD_OR_SAMP_MODE 0x1
#define SML_AD7091_CONF_REG_FLTR_ENABLE 0x0
#define SML_AD7091_CONF_REG_FLTR_BYPASS 0x1
#define SML_AD7091_CONF_REG_GPO2_DRIVE_0 0x0
#define SML_AD7091_CONF_REG_GPO2_DRIVE_1 0x1
#define SML_AD7091_CONF_REG_ALERT_DRIVE_TYPE_OPEN_DRAIN 0x0
#define SML_AD7091_CONF_REG_ALERT_DRIVE_TYPE_CMOS 0x1

typedef struct
{
    sml_i2c_regmap_t iic;
} sml_ad7091_t;

/**
 *  @brief Create device driver instance
 * 
 *  @param i2c An instance of the I2C driver for the bus on which the device is placed
 *  @return Device handle
 */
sml_ad7091_t sml_ad7091_create( sml_i2c_t i2c )
{
    sml_ad7091_t dev;
    dev.iic = sml_i2c_regmap_create( i2c, SML_AD7091_BASE_ADDR, 0x100, 0 );
    return dev;
} 

/**
 *  @brief Get Conversion result register
 * 
 *  @param dev The device handle
 *  @param result pointer to 12-bit conversion result
 *  @param alert_flag pointer to Alert flag bit
 *  @param chan pointer to Analog input channel
 */
void sml_ad7091_get_conv_res( sml_ad7091_t dev, int* result, int* alert_flag, int* chan )
{
    uint16_t _value;
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x0, 2 );
    _value = ((int)(_bytes[0]) << 8) | (int)(_bytes[1]);
    *result = _value & 0xfff;
    *alert_flag = (_value >> 12) & 0x1;
    *chan = (_value >> 13) & 0x3;
} 

/**
 *  @brief Set Channel Register
 * 
 *  @param dev The device handle
 *  @param ch0 Channel 0 status
 *  @param ch1 Channel 1 status
 *  @param ch2 Channel 2 status
 *  @param ch3 Channel 3 status
 */
void sml_ad7091_set_channel_register( sml_ad7091_t dev, int ch0, int ch1, int ch2, int ch3 )
{
    uint8_t _value;
    _value = (ch0 & 0x1) | ((ch1 & 0x1) << 1) | ((ch2 & 0x1) << 2) | ((ch3 & 0x1) << 3);
    sml_i2c_regmap_write( dev.iic, &_value, 0x1, 1 );
} 

/**
 *  @brief Get Channel Register
 * 
 *  @param dev The device handle
 *  @param ch0 pointer to Channel 0 status bit
 *  @param ch1 pointer to Channel 1 status bit
 *  @param ch2 pointer to Channel 2 status bit
 *  @param ch3 pointer to Channel 3 status bit
 */
void sml_ad7091_get_channel_register( sml_ad7091_t dev, int* ch0, int* ch1, int* ch2, int* ch3 )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x1, 1 );
    *ch0 = _bytes[0] & 0x1;
    *ch1 = (_bytes[0] >> 1) & 0x1;
    *ch2 = (_bytes[0] >> 2) & 0x1;
    *ch3 = (_bytes[0] >> 3) & 0x1;
} 

/**
 *  @brief Set Configuration register
 * 
 *  @param dev The device handle
 *  @param p_down Power down mode
 *  @param gpo1 Value at GPO 1
 *  @param alert_pol_or_gpo0 Polarity of ALERT/BUSY/GPO 0 pin if (ALERT_EN is 1) or value at GPO 0
 *  @param alert_en_or_gpo0 Enable alert or GPO0
 *  @param busy Alert busy pin indicates busy
 *  @param cycle_timer Timer value for Autocycle mode
 *  @param auto_mode Autocycle mode (depends on CMD mode field)
 *  @param srst Software Reset
 *  @param cmd command mode (depends on Auto mode field)
 *  @param fltr Enable glitch filter
 *  @param gpo2 Value at GPO2
 *  @param alert_drive_type Alert gpo 0 drive type
 */
void sml_ad7091_set_conf_reg( sml_ad7091_t dev, int p_down, int gpo1, int alert_pol_or_gpo0, int alert_en_or_gpo0, int busy, int cycle_timer, int auto_mode, int srst, int cmd, int fltr, int gpo2, int alert_drive_type )
{
    uint16_t _value;
    uint8_t _bytes[2];
    _value = (p_down & 0x3) | ((gpo1 & 0x1) << 2) | ((alert_pol_or_gpo0 & 0x1) << 3) | ((alert_en_or_gpo0 & 0x1) << 4) | ((busy & 0x1) << 5) | ((cycle_timer & 0x3) << 6) | ((auto_mode & 0x1) << 8) | ((srst & 0x1) << 9) | ((cmd & 0x1) << 10) | ((fltr & 0x1) << 11) | ((gpo2 & 0x1) << 14) | ((alert_drive_type & 0x1) << 15);
    _bytes[0] = (_value >> 8) & 0xff;
    _bytes[1] = _value & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x2, 2 );
} 

/**
 *  @brief Get Configuration register
 * 
 *  @param dev The device handle
 *  @param p_down pointer to Power down mode
 *  @param gpo1 pointer to Value at GPO 1 bit
 *  @param alert_pol_or_gpo0 pointer to Polarity of ALERT/BUSY/GPO 0 pin if (ALERT_EN is 1) or value at GPO 0 bit
 *  @param alert_en_or_gpo0 pointer to Enable alert or GPO0 bit
 *  @param busy pointer to Alert busy pin indicates busy bit
 *  @param cycle_timer pointer to Timer value for Autocycle mode
 *  @param auto_mode pointer to Autocycle mode (depends on CMD mode field) bit
 *  @param srst pointer to Software Reset bit
 *  @param cmd pointer to command mode (depends on Auto mode field) bit
 *  @param fltr pointer to Enable glitch filter bit
 *  @param gpo2 pointer to Value at GPO2 bit
 *  @param alert_drive_type pointer to Alert gpo 0 drive type bit
 */
void sml_ad7091_get_conf_reg( sml_ad7091_t dev, int* p_down, int* gpo1, int* alert_pol_or_gpo0, int* alert_en_or_gpo0, int* busy, int* cycle_timer, int* auto_mode, int* srst, int* cmd, int* fltr, int* gpo2, int* alert_drive_type )
{
    uint16_t _value;
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x2, 2 );
    _value = ((int)(_bytes[0]) << 8) | (int)(_bytes[1]);
    *p_down = _value & 0x3;
    *gpo1 = (_value >> 2) & 0x1;
    *alert_pol_or_gpo0 = (_value >> 3) & 0x1;
    *alert_en_or_gpo0 = (_value >> 4) & 0x1;
    *busy = (_value >> 5) & 0x1;
    *cycle_timer = (_value >> 6) & 0x3;
    *auto_mode = (_value >> 8) & 0x1;
    *srst = (_value >> 9) & 0x1;
    *cmd = (_value >> 10) & 0x1;
    *fltr = (_value >> 11) & 0x1;
    *gpo2 = (_value >> 14) & 0x1;
    *alert_drive_type = (_value >> 15) & 0x1;
} 

/**
 *  @brief Set Channel 0 low limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch0_low_limit Channel 0 low limit register, only 12 least significant bits
 */
void sml_ad7091_set_ch0_low_limit( sml_ad7091_t dev, uint16_t ch0_low_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch0_low_limit >> 8) & 0xff;
    _bytes[1] = ch0_low_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x4, 2 );
} 

/**
 *  @brief Get Channel 0 low limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 0 low limit register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch0_low_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x4, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set Channel 0 high limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch0_high_limit Channel 0 high limit register, only 12 least significant bits
 */
void sml_ad7091_set_ch0_high_limit( sml_ad7091_t dev, uint16_t ch0_high_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch0_high_limit >> 8) & 0xff;
    _bytes[1] = ch0_high_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x5, 2 );
} 

/**
 *  @brief Get Channel 0 high limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 0 high limit register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch0_high_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x5, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set Channel 0 hysteresis register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch0_hyst_limit Channel 0 hysteresis register, only 12 least significant bits
 */
void sml_ad7091_set_ch0_hyst_limit( sml_ad7091_t dev, uint16_t ch0_hyst_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch0_hyst_limit >> 8) & 0xff;
    _bytes[1] = ch0_hyst_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x6, 2 );
} 

/**
 *  @brief Get Channel 0 hysteresis register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 0 hysteresis register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch0_hyst_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x6, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set Channel 1 low limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch1_low_limit Channel 1 low limit register, only 12 least significant bits
 */
void sml_ad7091_set_ch1_low_limit( sml_ad7091_t dev, uint16_t ch1_low_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch1_low_limit >> 8) & 0xff;
    _bytes[1] = ch1_low_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x7, 2 );
} 

/**
 *  @brief Get Channel 1 low limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 1 low limit register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch1_low_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x7, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set Channel 1 high limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch1_high_limit Channel 1 high limit register, only 12 least significant bits
 */
void sml_ad7091_set_ch1_high_limit( sml_ad7091_t dev, uint16_t ch1_high_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch1_high_limit >> 8) & 0xff;
    _bytes[1] = ch1_high_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x8, 2 );
} 

/**
 *  @brief Get Channel 1 high limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 1 high limit register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch1_high_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x8, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set Channel 1 hysteresis register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch1_hyst_limit Channel 1 hysteresis register, only 12 least significant bits
 */
void sml_ad7091_set_ch1_hyst_limit( sml_ad7091_t dev, uint16_t ch1_hyst_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch1_hyst_limit >> 8) & 0xff;
    _bytes[1] = ch1_hyst_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0x9, 2 );
} 

/**
 *  @brief Get Channel 1 hysteresis register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 1 hysteresis register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch1_hyst_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x9, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set Channel 2 low limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch2_low_limit Channel 2 low limit register, only 12 least significant bits
 */
void sml_ad7091_set_ch2_low_limit( sml_ad7091_t dev, uint16_t ch2_low_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch2_low_limit >> 8) & 0xff;
    _bytes[1] = ch2_low_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0xa, 2 );
} 

/**
 *  @brief Get Channel 2 low limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 2 low limit register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch2_low_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0xa, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set Channel 2 high limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch2_high_limit Channel 2 high limit register, only 12 least significant bits
 */
void sml_ad7091_set_ch2_high_limit( sml_ad7091_t dev, uint16_t ch2_high_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch2_high_limit >> 8) & 0xff;
    _bytes[1] = ch2_high_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0xb, 2 );
} 

/**
 *  @brief Get Channel 2 high limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 2 high limit register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch2_high_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0xb, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set Channel 2 hysteresis register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch2_hyst_limit Channel 2 hysteresis register, only 12 least significant bits
 */
void sml_ad7091_set_ch2_hyst_limit( sml_ad7091_t dev, uint16_t ch2_hyst_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch2_hyst_limit >> 8) & 0xff;
    _bytes[1] = ch2_hyst_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0xc, 2 );
} 

/**
 *  @brief Get Channel 2 hysteresis register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 2 hysteresis register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch2_hyst_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0xc, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set Channel 3 low limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch3_low_limit Channel 3 low limit register, only 12 least significant bits
 */
void sml_ad7091_set_ch3_low_limit( sml_ad7091_t dev, uint16_t ch3_low_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch3_low_limit >> 8) & 0xff;
    _bytes[1] = ch3_low_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0xd, 2 );
} 

/**
 *  @brief Get Channel 3 low limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 3 low limit register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch3_low_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0xd, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set Channel 3 high limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch3_high_limit Channel 3 high limit register, only 12 least significant bits
 */
void sml_ad7091_set_ch3_high_limit( sml_ad7091_t dev, uint16_t ch3_high_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch3_high_limit >> 8) & 0xff;
    _bytes[1] = ch3_high_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0xe, 2 );
} 

/**
 *  @brief Get Channel 3 high limit register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 3 high limit register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch3_high_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0xe, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

/**
 *  @brief Set Channel 3 hysteresis register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @param ch3_hyst_limit Channel 3 hysteresis register, only 12 least significant bits
 */
void sml_ad7091_set_ch3_hyst_limit( sml_ad7091_t dev, uint16_t ch3_hyst_limit )
{
    uint8_t _bytes[2];
    _bytes[0] = (ch3_hyst_limit >> 8) & 0xff;
    _bytes[1] = ch3_hyst_limit & 0xff;
    sml_i2c_regmap_write( dev.iic, _bytes, 0xf, 2 );
} 

/**
 *  @brief Get Channel 3 hysteresis register, only 12 least significant bits
 * 
 *  @param dev The device handle
 *  @return Channel 3 hysteresis register, only 12 least significant bits
 */
uint16_t sml_ad7091_get_ch3_hyst_limit( sml_ad7091_t dev )
{
    uint8_t _bytes[2];
    sml_i2c_regmap_read( dev.iic, _bytes, 0xf, 2 );
    return (uint16_t)(((int)(_bytes[0]) << 8) | (int)(_bytes[1]));
} 

#endif /* AD7091_H */
