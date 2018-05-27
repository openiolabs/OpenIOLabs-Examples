## @file
#  @package pcf8563
# 
#  @brief Real-time clock
# 
#  Real-time clock/calendar
#  ------------------------
#  
#  
#  
#  
#  Auto-generated 27 May 2018; do not edit
#  
#  Copyright (c) Open IO Labs Ltd 2017
#  All Rights Reserved
# 

from i2c_regmap import *
from gpio import *

BASE_ADDR = 0x51

CONTROL_STATUS_1_STOP_RTC_RUNS = 0x0
CONTROL_STATUS_1_STOP_RTC_STOPPED = 0x1

CONTROL_STATUS_2_TI_TP_TF_ACTIVE = 0x0
CONTROL_STATUS_2_TI_TP_PULSE = 0x0

VL_AND_TIME_COMBINED_VL_GUARANTEED = 0x0
VL_AND_TIME_COMBINED_VL_NOT_GUARANTEED = 0x1
VL_AND_TIME_COMBINED_WEEKDAYS_SUNDAY = 0x0
VL_AND_TIME_COMBINED_WEEKDAYS_MONDAY = 0x1
VL_AND_TIME_COMBINED_WEEKDAYS_TUESDAY = 0x2
VL_AND_TIME_COMBINED_WEEKDAYS_WEDNSDAY = 0x3
VL_AND_TIME_COMBINED_WEEKDAYS_THURSDAY = 0x4
VL_AND_TIME_COMBINED_WEEKDAYS_FRIDAY = 0x5
VL_AND_TIME_COMBINED_WEEKDAYS_SATURDAY = 0x6

CLKOUT_CONTROL_FD_32KHZ = 0x0
CLKOUT_CONTROL_FD_1KHZ = 0x1
CLKOUT_CONTROL_FD_32HZ = 0x2
CLKOUT_CONTROL_FD_1HZ = 0x3

TIMER_CONTROL_TD_4KHZ = 0x0
TIMER_CONTROL_TD_64HZ = 0x1
TIMER_CONTROL_TD_1HZ = 0x2
TIMER_CONTROL_TD_1_60HZ = 0x3

class device:
    ##
    #  @brief Create device driver instance
    # 
    #  @param i2c An instance of the I2C driver for the bus on which the device is placed
    #  @param intr_pin An instance of the GPIO driver for the pin connected to the interrupt line
    #  @return Device handle
    # 
    def __init__( self, i2c, intr_pin ):
        self.intr_gpio = intr_pin
        self.iic = i2c_regmap( i2c, BASE_ADDR, 0x100, False )

    ##
    #  @brief Set Control and status register 1
    # 
    #  @param stop STOP
    # 
    def set_control_status_1( self, stop ):
        _value = uint8(((stop & 0x1) << 5))
        self.iic.write( [_value], 0x0, 1 )

    ##
    #  @brief Get Control and status register 1
    # 
    #  @param stop list containing STOP bit
    # 
    def get_control_status_1( self, stop ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x0, 1 )
        stop[0] = (_bytes[0] >> 5) & 0x1

    ##
    #  @brief Set Control and status register 2
    # 
    #  @param ti_tp Timer interrupt type
    #  @param af Alarm flag
    #  @param tf Timer flag
    #  @param aie Alarm interrupt enable
    #  @param tie Timer interrupt enable
    # 
    def set_control_status_2( self, ti_tp, af, tf, aie, tie ):
        _value = uint8(((ti_tp & 0x1) << 4) | ((af & 0x1) << 3) | ((tf & 0x1) << 2) | ((aie & 0x1) << 1) | (tie & 0x1))
        self.iic.write( [_value], 0x1, 1 )

    ##
    #  @brief Get Control and status register 2
    # 
    #  @param ti_tp list containing Timer interrupt type bit
    #  @param af list containing Alarm flag bit
    #  @param tf list containing Timer flag bit
    #  @param aie list containing Alarm interrupt enable bit
    #  @param tie list containing Timer interrupt enable bit
    # 
    def get_control_status_2( self, ti_tp, af, tf, aie, tie ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x1, 1 )
        ti_tp[0] = (_bytes[0] >> 4) & 0x1
        af[0] = (_bytes[0] >> 3) & 0x1
        tf[0] = (_bytes[0] >> 2) & 0x1
        aie[0] = (_bytes[0] >> 1) & 0x1
        tie[0] = _bytes[0] & 0x1

    ##
    #  @brief Set All current time fields; must be a single access for coherency
    # 
    #  @param vl clock integrity status
    #  @param seconds_units Seconds units place
    #  @param seconds_tens Seconds tens place
    #  @param minutes_units Minutes units place
    #  @param minutes_tens Minutes tens place
    #  @param hours_units Hours units place
    #  @param hours_tens Hours tens place
    #  @param days_units Days units place
    #  @param days_tens Days tens place
    #  @param weekdays Weekdays (whole value)
    #  @param century Century modulo 2
    #  @param months_units Months units place
    #  @param months_tens Months tens place
    #  @param years_units Years units place
    #  @param years_tens Years tens place
    # 
    def set_vl_and_time_combined( self, vl, seconds_units, seconds_tens, minutes_units, minutes_tens, hours_units, hours_tens, days_units, days_tens, weekdays, century, months_units, months_tens, years_units, years_tens ):
        _bytes = [uint8(), uint8(), uint8(), uint8(), uint8(), uint8(), uint8()]
        _bytes[0] = uint8(((vl & 0x1) << 7) | (seconds_units & 0xf) | ((seconds_tens & 0x7) << 4))
        _bytes[1] = uint8((minutes_units & 0xf) | ((minutes_tens & 0x7) << 4))
        _bytes[2] = uint8((hours_units & 0xf) | ((hours_tens & 0x3) << 4))
        _bytes[3] = uint8((days_units & 0xf) | ((days_tens & 0x3) << 4))
        _bytes[4] = uint8((weekdays & 0x7))
        _bytes[5] = uint8(((century & 0x1) << 7) | (months_units & 0xf) | ((months_tens & 0x1) << 4))
        _bytes[6] = uint8((years_units & 0xf) | ((years_tens & 0xf) << 4))
        self.iic.write( _bytes, 0x2, 7 )

    ##
    #  @brief Get All current time fields; must be a single access for coherency
    # 
    #  @param vl list containing clock integrity status bit
    #  @param seconds_units list containing Seconds units place
    #  @param seconds_tens list containing Seconds tens place
    #  @param minutes_units list containing Minutes units place
    #  @param minutes_tens list containing Minutes tens place
    #  @param hours_units list containing Hours units place
    #  @param hours_tens list containing Hours tens place
    #  @param days_units list containing Days units place
    #  @param days_tens list containing Days tens place
    #  @param weekdays list containing Weekdays (whole value)
    #  @param century list containing Century modulo 2 bit
    #  @param months_units list containing Months units place
    #  @param months_tens list containing Months tens place bit
    #  @param years_units list containing Years units place
    #  @param years_tens list containing Years tens place
    # 
    def get_vl_and_time_combined( self, vl, seconds_units, seconds_tens, minutes_units, minutes_tens, hours_units, hours_tens, days_units, days_tens, weekdays, century, months_units, months_tens, years_units, years_tens ):
        _bytes = [uint8(), uint8(), uint8(), uint8(), uint8(), uint8(), uint8()]
        _bytes = self.iic.read( 0x2, 7 )
        vl[0] = (_bytes[0] >> 7) & 0x1
        seconds_units[0] = _bytes[0] & 0xf
        seconds_tens[0] = (_bytes[0] >> 4) & 0x7
        minutes_units[0] = _bytes[1] & 0xf
        minutes_tens[0] = (_bytes[1] >> 4) & 0x7
        hours_units[0] = _bytes[2] & 0xf
        hours_tens[0] = (_bytes[2] >> 4) & 0x3
        days_units[0] = _bytes[3] & 0xf
        days_tens[0] = (_bytes[3] >> 4) & 0x3
        weekdays[0] = _bytes[4] & 0x7
        century[0] = (_bytes[5] >> 7) & 0x1
        months_units[0] = _bytes[5] & 0xf
        months_tens[0] = (_bytes[5] >> 4) & 0x1
        years_units[0] = _bytes[6] & 0xf
        years_tens[0] = (_bytes[6] >> 4) & 0xf

    ##
    #  @brief Set Alarm minutes
    # 
    #  @param ae_m Minute alarm disable
    #  @param minutes_units Minutes units place
    #  @param minutes_tens Minutes tens place
    # 
    def set_minute_alarm( self, ae_m, minutes_units, minutes_tens ):
        _value = uint8(((ae_m & 0x1) << 7) | (minutes_units & 0xf) | ((minutes_tens & 0x7) << 4))
        self.iic.write( [_value], 0x9, 1 )

    ##
    #  @brief Get Alarm minutes
    # 
    #  @param ae_m list containing Minute alarm disable bit
    #  @param minutes_units list containing Minutes units place
    #  @param minutes_tens list containing Minutes tens place
    # 
    def get_minute_alarm( self, ae_m, minutes_units, minutes_tens ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x9, 1 )
        ae_m[0] = (_bytes[0] >> 7) & 0x1
        minutes_units[0] = _bytes[0] & 0xf
        minutes_tens[0] = (_bytes[0] >> 4) & 0x7

    ##
    #  @brief Set Alarm hours
    # 
    #  @param ae_h Hour alarm disable
    #  @param hours_units Hours units place
    #  @param hours_tens Hours tens place
    # 
    def set_hour_alarm( self, ae_h, hours_units, hours_tens ):
        _value = uint8(((ae_h & 0x1) << 7) | (hours_units & 0xf) | ((hours_tens & 0x3) << 4))
        self.iic.write( [_value], 0xa, 1 )

    ##
    #  @brief Get Alarm hours
    # 
    #  @param ae_h list containing Hour alarm disable bit
    #  @param hours_units list containing Hours units place
    #  @param hours_tens list containing Hours tens place
    # 
    def get_hour_alarm( self, ae_h, hours_units, hours_tens ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0xa, 1 )
        ae_h[0] = (_bytes[0] >> 7) & 0x1
        hours_units[0] = _bytes[0] & 0xf
        hours_tens[0] = (_bytes[0] >> 4) & 0x3

    ##
    #  @brief Set Alarm days
    # 
    #  @param ae_d Day alarm disable
    #  @param days_units Days units place
    #  @param days_tens Days tens place
    # 
    def set_day_alarm( self, ae_d, days_units, days_tens ):
        _value = uint8(((ae_d & 0x1) << 7) | (days_units & 0xf) | ((days_tens & 0x3) << 4))
        self.iic.write( [_value], 0xb, 1 )

    ##
    #  @brief Get Alarm days
    # 
    #  @param ae_d list containing Day alarm disable bit
    #  @param days_units list containing Days units place
    #  @param days_tens list containing Days tens place
    # 
    def get_day_alarm( self, ae_d, days_units, days_tens ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0xb, 1 )
        ae_d[0] = (_bytes[0] >> 7) & 0x1
        days_units[0] = _bytes[0] & 0xf
        days_tens[0] = (_bytes[0] >> 4) & 0x3

    ##
    #  @brief Set Alarm weekday
    # 
    #  @param ae_w Weekday alarm disable
    #  @param weekdays Weekdays (whole field)
    # 
    def set_weekday_alarm( self, ae_w, weekdays ):
        _value = uint8(((ae_w & 0x1) << 7) | (weekdays & 0x7))
        self.iic.write( [_value], 0xc, 1 )

    ##
    #  @brief Get Alarm weekday
    # 
    #  @param ae_w list containing Weekday alarm disable bit
    #  @param weekdays list containing Weekdays (whole field)
    # 
    def get_weekday_alarm( self, ae_w, weekdays ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0xc, 1 )
        ae_w[0] = (_bytes[0] >> 7) & 0x1
        weekdays[0] = _bytes[0] & 0x7

    ##
    #  @brief Set CLKOUT control
    # 
    #  @param fe Activate CLKOUT output
    #  @param fd CLKOUT frequency
    # 
    def set_clkout_control( self, fe, fd ):
        _value = uint8(((fe & 0x1) << 7) | (fd & 0x3))
        self.iic.write( [_value], 0xd, 1 )

    ##
    #  @brief Get CLKOUT control
    # 
    #  @param fe list containing Activate CLKOUT output bit
    #  @param fd list containing CLKOUT frequency
    # 
    def get_clkout_control( self, fe, fd ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0xd, 1 )
        fe[0] = (_bytes[0] >> 7) & 0x1
        fd[0] = _bytes[0] & 0x3

    ##
    #  @brief Set Timer control
    # 
    #  @param te Timer enable
    #  @param td Timer frequency
    # 
    def set_timer_control( self, te, td ):
        _value = uint8(((te & 0x1) << 7) | (td & 0x3))
        self.iic.write( [_value], 0xe, 1 )

    ##
    #  @brief Get Timer control
    # 
    #  @param te list containing Timer enable bit
    #  @param td list containing Timer frequency
    # 
    def get_timer_control( self, te, td ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0xe, 1 )
        te[0] = (_bytes[0] >> 7) & 0x1
        td[0] = _bytes[0] & 0x3

    ##
    #  @brief Set Timer
    # 
    #  @param timer Timer
    # 
    def set_timer( self, timer ):
        self.iic.write( [timer], 0xf, 1 )

    ##
    #  @brief Get Timer
    # 
    #  @return Timer
    # 
    def get_timer( self ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0xf, 1 )
        return _bytes[0]

