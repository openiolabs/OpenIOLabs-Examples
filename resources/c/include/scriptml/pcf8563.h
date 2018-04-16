/** @file
 * 
 *  @brief Real-time clock
 * 
 *  Real-time clock/calendar
 *  ------------------------
 *  
 *  
 *  
 *  
 *  Auto-generated 16 April 2018; do not edit
 *  
 *  Copyright (c) Open IO Labs Ltd 2017
 *  All Rights Reserved
 */

#ifndef __PCF8563_H
#define __PCF8563_H

#include <i2c_regmap.h>
#include <gpio.h>

#define SML_PCF8563_BASE_ADDR 0x51

#define SML_PCF8563_CONTROL_STATUS_1_STOP_RTC_RUNS 0x0
#define SML_PCF8563_CONTROL_STATUS_1_STOP_RTC_STOPPED 0x1

#define SML_PCF8563_CONTROL_STATUS_2_TI_TP_TF_ACTIVE 0x0
#define SML_PCF8563_CONTROL_STATUS_2_TI_TP_PULSE 0x0

#define SML_PCF8563_VL_AND_TIME_COMBINED_VL_GUARANTEED 0x0
#define SML_PCF8563_VL_AND_TIME_COMBINED_VL_NOT_GUARANTEED 0x1
#define SML_PCF8563_VL_AND_TIME_COMBINED_WEEKDAYS_SUNDAY 0x0
#define SML_PCF8563_VL_AND_TIME_COMBINED_WEEKDAYS_MONDAY 0x1
#define SML_PCF8563_VL_AND_TIME_COMBINED_WEEKDAYS_TUESDAY 0x2
#define SML_PCF8563_VL_AND_TIME_COMBINED_WEEKDAYS_WEDNSDAY 0x3
#define SML_PCF8563_VL_AND_TIME_COMBINED_WEEKDAYS_THURSDAY 0x4
#define SML_PCF8563_VL_AND_TIME_COMBINED_WEEKDAYS_FRIDAY 0x5
#define SML_PCF8563_VL_AND_TIME_COMBINED_WEEKDAYS_SATURDAY 0x6

#define SML_PCF8563_CLKOUT_CONTROL_FD_32KHZ 0x0
#define SML_PCF8563_CLKOUT_CONTROL_FD_1KHZ 0x1
#define SML_PCF8563_CLKOUT_CONTROL_FD_32HZ 0x2
#define SML_PCF8563_CLKOUT_CONTROL_FD_1HZ 0x3

#define SML_PCF8563_TIMER_CONTROL_TD_4KHZ 0x0
#define SML_PCF8563_TIMER_CONTROL_TD_64HZ 0x1
#define SML_PCF8563_TIMER_CONTROL_TD_1HZ 0x2
#define SML_PCF8563_TIMER_CONTROL_TD_1_60HZ 0x3

typedef struct
{
    sml_i2c_regmap_t iic;
    sml_gpio_handle_t intr_gpio;
} sml_pcf8563_t;

/**
 *  @brief Create device driver instance
 * 
 *  @param i2c An instance of the I2C driver for the bus on which the device is placed
 *  @param intr_pin An instance of the GPIO driver for the pin connected to the interrupt line
 *  @return Device handle
 */
sml_pcf8563_t sml_pcf8563_create( sml_i2c_t i2c, sml_gpio_handle_t intr_pin )
{
    sml_pcf8563_t dev;
    dev.intr_gpio = intr_pin;
    dev.iic = sml_i2c_regmap_create( i2c, SML_PCF8563_BASE_ADDR, 0x100, 0 );
    return dev;
} 

/**
 *  @brief Set Control and status register 1
 * 
 *  @param dev The device handle
 *  @param stop STOP
 */
void sml_pcf8563_set_control_status_1( sml_pcf8563_t dev, int stop )
{
    uint8_t _value;
    _value = ((stop & 0x1) << 5);
    sml_i2c_regmap_write( dev.iic, &_value, 0x0, 1 );
} 

/**
 *  @brief Get Control and status register 1
 * 
 *  @param dev The device handle
 *  @param stop pointer to STOP bit
 */
void sml_pcf8563_get_control_status_1( sml_pcf8563_t dev, int* stop )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x0, 1 );
    *stop = (_bytes[0] >> 5) & 0x1;
} 

/**
 *  @brief Set Control and status register 2
 * 
 *  @param dev The device handle
 *  @param ti_tp Timer interrupt type
 *  @param af Alarm flag
 *  @param tf Timer flag
 *  @param aie Alarm interrupt enable
 *  @param tie Timer interrupt enable
 */
void sml_pcf8563_set_control_status_2( sml_pcf8563_t dev, int ti_tp, int af, int tf, int aie, int tie )
{
    uint8_t _value;
    _value = ((ti_tp & 0x1) << 4) | ((af & 0x1) << 3) | ((tf & 0x1) << 2) | ((aie & 0x1) << 1) | (tie & 0x1);
    sml_i2c_regmap_write( dev.iic, &_value, 0x1, 1 );
} 

/**
 *  @brief Get Control and status register 2
 * 
 *  @param dev The device handle
 *  @param ti_tp pointer to Timer interrupt type bit
 *  @param af pointer to Alarm flag bit
 *  @param tf pointer to Timer flag bit
 *  @param aie pointer to Alarm interrupt enable bit
 *  @param tie pointer to Timer interrupt enable bit
 */
void sml_pcf8563_get_control_status_2( sml_pcf8563_t dev, int* ti_tp, int* af, int* tf, int* aie, int* tie )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x1, 1 );
    *ti_tp = (_bytes[0] >> 4) & 0x1;
    *af = (_bytes[0] >> 3) & 0x1;
    *tf = (_bytes[0] >> 2) & 0x1;
    *aie = (_bytes[0] >> 1) & 0x1;
    *tie = _bytes[0] & 0x1;
} 

/**
 *  @brief Set All current time fields; must be a single access for coherency
 * 
 *  @param dev The device handle
 *  @param vl clock integrity status
 *  @param seconds_units Seconds units place
 *  @param seconds_tens Seconds tens place
 *  @param minutes_units Minutes units place
 *  @param minutes_tens Minutes tens place
 *  @param hours_units Hours units place
 *  @param hours_tens Hours tens place
 *  @param days_units Days units place
 *  @param days_tens Days tens place
 *  @param weekdays Weekdays (whole value)
 *  @param century Century modulo 2
 *  @param months_units Months units place
 *  @param months_tens Months tens place
 *  @param years_units Years units place
 *  @param years_tens Years tens place
 */
void sml_pcf8563_set_vl_and_time_combined( sml_pcf8563_t dev, int vl, int seconds_units, int seconds_tens, int minutes_units, int minutes_tens, int hours_units, int hours_tens, int days_units, int days_tens, int weekdays, int century, int months_units, int months_tens, int years_units, int years_tens )
{
    uint8_t _bytes[7];
    _bytes[0] = ((vl & 0x1) << 7) | (seconds_units & 0xf) | ((seconds_tens & 0x7) << 4);
    _bytes[1] = (minutes_units & 0xf) | ((minutes_tens & 0x7) << 4);
    _bytes[2] = (hours_units & 0xf) | ((hours_tens & 0x3) << 4);
    _bytes[3] = (days_units & 0xf) | ((days_tens & 0x3) << 4);
    _bytes[4] = (weekdays & 0x7);
    _bytes[5] = ((century & 0x1) << 7) | (months_units & 0xf) | ((months_tens & 0x1) << 4);
    _bytes[6] = (years_units & 0xf) | ((years_tens & 0xf) << 4);
    sml_i2c_regmap_write( dev.iic, _bytes, 0x2, 7 );
} 

/**
 *  @brief Get All current time fields; must be a single access for coherency
 * 
 *  @param dev The device handle
 *  @param vl pointer to clock integrity status bit
 *  @param seconds_units pointer to Seconds units place
 *  @param seconds_tens pointer to Seconds tens place
 *  @param minutes_units pointer to Minutes units place
 *  @param minutes_tens pointer to Minutes tens place
 *  @param hours_units pointer to Hours units place
 *  @param hours_tens pointer to Hours tens place
 *  @param days_units pointer to Days units place
 *  @param days_tens pointer to Days tens place
 *  @param weekdays pointer to Weekdays (whole value)
 *  @param century pointer to Century modulo 2 bit
 *  @param months_units pointer to Months units place
 *  @param months_tens pointer to Months tens place bit
 *  @param years_units pointer to Years units place
 *  @param years_tens pointer to Years tens place
 */
void sml_pcf8563_get_vl_and_time_combined( sml_pcf8563_t dev, int* vl, int* seconds_units, int* seconds_tens, int* minutes_units, int* minutes_tens, int* hours_units, int* hours_tens, int* days_units, int* days_tens, int* weekdays, int* century, int* months_units, int* months_tens, int* years_units, int* years_tens )
{
    uint8_t _bytes[7];
    sml_i2c_regmap_read( dev.iic, _bytes, 0x2, 7 );
    *vl = (_bytes[0] >> 7) & 0x1;
    *seconds_units = _bytes[0] & 0xf;
    *seconds_tens = (_bytes[0] >> 4) & 0x7;
    *minutes_units = _bytes[1] & 0xf;
    *minutes_tens = (_bytes[1] >> 4) & 0x7;
    *hours_units = _bytes[2] & 0xf;
    *hours_tens = (_bytes[2] >> 4) & 0x3;
    *days_units = _bytes[3] & 0xf;
    *days_tens = (_bytes[3] >> 4) & 0x3;
    *weekdays = _bytes[4] & 0x7;
    *century = (_bytes[5] >> 7) & 0x1;
    *months_units = _bytes[5] & 0xf;
    *months_tens = (_bytes[5] >> 4) & 0x1;
    *years_units = _bytes[6] & 0xf;
    *years_tens = (_bytes[6] >> 4) & 0xf;
} 

/**
 *  @brief Set Alarm minutes
 * 
 *  @param dev The device handle
 *  @param ae_m Minute alarm disable
 *  @param minutes_units Minutes units place
 *  @param minutes_tens Minutes tens place
 */
void sml_pcf8563_set_minute_alarm( sml_pcf8563_t dev, int ae_m, int minutes_units, int minutes_tens )
{
    uint8_t _value;
    _value = ((ae_m & 0x1) << 7) | (minutes_units & 0xf) | ((minutes_tens & 0x7) << 4);
    sml_i2c_regmap_write( dev.iic, &_value, 0x9, 1 );
} 

/**
 *  @brief Get Alarm minutes
 * 
 *  @param dev The device handle
 *  @param ae_m pointer to Minute alarm disable bit
 *  @param minutes_units pointer to Minutes units place
 *  @param minutes_tens pointer to Minutes tens place
 */
void sml_pcf8563_get_minute_alarm( sml_pcf8563_t dev, int* ae_m, int* minutes_units, int* minutes_tens )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0x9, 1 );
    *ae_m = (_bytes[0] >> 7) & 0x1;
    *minutes_units = _bytes[0] & 0xf;
    *minutes_tens = (_bytes[0] >> 4) & 0x7;
} 

/**
 *  @brief Set Alarm hours
 * 
 *  @param dev The device handle
 *  @param ae_h Hour alarm disable
 *  @param hours_units Hours units place
 *  @param hours_tens Hours tens place
 */
void sml_pcf8563_set_hour_alarm( sml_pcf8563_t dev, int ae_h, int hours_units, int hours_tens )
{
    uint8_t _value;
    _value = ((ae_h & 0x1) << 7) | (hours_units & 0xf) | ((hours_tens & 0x3) << 4);
    sml_i2c_regmap_write( dev.iic, &_value, 0xa, 1 );
} 

/**
 *  @brief Get Alarm hours
 * 
 *  @param dev The device handle
 *  @param ae_h pointer to Hour alarm disable bit
 *  @param hours_units pointer to Hours units place
 *  @param hours_tens pointer to Hours tens place
 */
void sml_pcf8563_get_hour_alarm( sml_pcf8563_t dev, int* ae_h, int* hours_units, int* hours_tens )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0xa, 1 );
    *ae_h = (_bytes[0] >> 7) & 0x1;
    *hours_units = _bytes[0] & 0xf;
    *hours_tens = (_bytes[0] >> 4) & 0x3;
} 

/**
 *  @brief Set Alarm days
 * 
 *  @param dev The device handle
 *  @param ae_d Day alarm disable
 *  @param days_units Days units place
 *  @param days_tens Days tens place
 */
void sml_pcf8563_set_day_alarm( sml_pcf8563_t dev, int ae_d, int days_units, int days_tens )
{
    uint8_t _value;
    _value = ((ae_d & 0x1) << 7) | (days_units & 0xf) | ((days_tens & 0x3) << 4);
    sml_i2c_regmap_write( dev.iic, &_value, 0xb, 1 );
} 

/**
 *  @brief Get Alarm days
 * 
 *  @param dev The device handle
 *  @param ae_d pointer to Day alarm disable bit
 *  @param days_units pointer to Days units place
 *  @param days_tens pointer to Days tens place
 */
void sml_pcf8563_get_day_alarm( sml_pcf8563_t dev, int* ae_d, int* days_units, int* days_tens )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0xb, 1 );
    *ae_d = (_bytes[0] >> 7) & 0x1;
    *days_units = _bytes[0] & 0xf;
    *days_tens = (_bytes[0] >> 4) & 0x3;
} 

/**
 *  @brief Set Alarm weekday
 * 
 *  @param dev The device handle
 *  @param ae_w Weekday alarm disable
 *  @param weekdays Weekdays (whole field)
 */
void sml_pcf8563_set_weekday_alarm( sml_pcf8563_t dev, int ae_w, int weekdays )
{
    uint8_t _value;
    _value = ((ae_w & 0x1) << 7) | (weekdays & 0x7);
    sml_i2c_regmap_write( dev.iic, &_value, 0xc, 1 );
} 

/**
 *  @brief Get Alarm weekday
 * 
 *  @param dev The device handle
 *  @param ae_w pointer to Weekday alarm disable bit
 *  @param weekdays pointer to Weekdays (whole field)
 */
void sml_pcf8563_get_weekday_alarm( sml_pcf8563_t dev, int* ae_w, int* weekdays )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0xc, 1 );
    *ae_w = (_bytes[0] >> 7) & 0x1;
    *weekdays = _bytes[0] & 0x7;
} 

/**
 *  @brief Set CLKOUT control
 * 
 *  @param dev The device handle
 *  @param fe Activate CLKOUT output
 *  @param fd CLKOUT frequency
 */
void sml_pcf8563_set_clkout_control( sml_pcf8563_t dev, int fe, int fd )
{
    uint8_t _value;
    _value = ((fe & 0x1) << 7) | (fd & 0x3);
    sml_i2c_regmap_write( dev.iic, &_value, 0xd, 1 );
} 

/**
 *  @brief Get CLKOUT control
 * 
 *  @param dev The device handle
 *  @param fe pointer to Activate CLKOUT output bit
 *  @param fd pointer to CLKOUT frequency
 */
void sml_pcf8563_get_clkout_control( sml_pcf8563_t dev, int* fe, int* fd )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0xd, 1 );
    *fe = (_bytes[0] >> 7) & 0x1;
    *fd = _bytes[0] & 0x3;
} 

/**
 *  @brief Set Timer control
 * 
 *  @param dev The device handle
 *  @param te Timer enable
 *  @param td Timer frequency
 */
void sml_pcf8563_set_timer_control( sml_pcf8563_t dev, int te, int td )
{
    uint8_t _value;
    _value = ((te & 0x1) << 7) | (td & 0x3);
    sml_i2c_regmap_write( dev.iic, &_value, 0xe, 1 );
} 

/**
 *  @brief Get Timer control
 * 
 *  @param dev The device handle
 *  @param te pointer to Timer enable bit
 *  @param td pointer to Timer frequency
 */
void sml_pcf8563_get_timer_control( sml_pcf8563_t dev, int* te, int* td )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0xe, 1 );
    *te = (_bytes[0] >> 7) & 0x1;
    *td = _bytes[0] & 0x3;
} 

/**
 *  @brief Set Timer
 * 
 *  @param dev The device handle
 *  @param timer Timer
 */
void sml_pcf8563_set_timer( sml_pcf8563_t dev, uint8_t timer )
{
    sml_i2c_regmap_write( dev.iic, &timer, 0xf, 1 );
} 

/**
 *  @brief Get Timer
 * 
 *  @param dev The device handle
 *  @return Timer
 */
uint8_t sml_pcf8563_get_timer( sml_pcf8563_t dev )
{
    uint8_t _bytes[1];
    sml_i2c_regmap_read( dev.iic, &_bytes, 0xf, 1 );
    return _bytes[0];
} 

#endif /* PCF8563_H */
