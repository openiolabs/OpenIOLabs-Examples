## @file
#  @package ad7091
# 
#  @brief Quad channel 12 bit ADC
# 
#  The ADI AD7091R quad channel ADC with 12 bits resolution, accessed via the I2C interface.
#  
#  Auto-generated 17 May 2018; do not edit
#  
#  Copyright (c) Open IO Labs Ltd 2017
#  All Rights Reserved
# 

from i2c_regmap import *

BASE_ADDR = 0x22

CONV_RES_ALERT_FLAG_NO_ALERT = 0x0
CONV_RES_ALERT_FLAG_ALERT = 0x1
CONV_RES_CHAN_CH0 = 0x0
CONV_RES_CHAN_CH1 = 0x1
CONV_RES_CHAN_CH2 = 0x2
CONV_RES_CHAN_CH3 = 0x3

CHANNEL_REGISTER_CH0_DISABLED = 0x0
CHANNEL_REGISTER_CH0_ENABLED = 0x1
CHANNEL_REGISTER_CH1_DISABLED = 0x0
CHANNEL_REGISTER_CH1_ENABLED = 0x1
CHANNEL_REGISTER_CH2_DISABLED = 0x0
CHANNEL_REGISTER_CH2_ENABLED = 0x1
CHANNEL_REGISTER_CH3_DISABLED = 0x0
CHANNEL_REGISTER_CH3_ENABLED = 0x1

CONF_REG_P_DOWN_MODE_0 = 0x0
CONF_REG_P_DOWN_MODE_1 = 0x1
CONF_REG_P_DOWN_MODE_2 = 0x2
CONF_REG_P_DOWN_MODE_3 = 0x3
CONF_REG_GPO1_DRIVE_0 = 0x0
CONF_REG_GPO1_DRIVE_1 = 0x1
CONF_REG_ALERT_POL_OR_GPO0_PIN_ACTIVE_LOW = 0x0
CONF_REG_ALERT_POL_OR_GPO0_PIN_ACTIVE_HIGH = 0x1
CONF_REG_ALERT_EN_OR_GPO0_USED_FOR_GPO0 = 0x0
CONF_REG_ALERT_EN_OR_GPO0_USED_FOR_ALERT = 0x1
CONF_REG_BUSY_NOT_USED_FOR_BUSY = 0x0
CONF_REG_BUSY_USED_FOR_BUSY = 0x1
CONF_REG_CYCLE_TIMER_100_US = 0x0
CONF_REG_CYCLE_TIMER_200_US = 0x1
CONF_REG_CYCLE_TIMER_400_US = 0x2
CONF_REG_CYCLE_TIMER_800_US = 0x3
CONF_REG_AUTO_MODE_SAMP_OR_CMD_MODE = 0x0
CONF_REG_AUTO_MODE_AUTO_OR_SAMP_MODE = 0x1
CONF_REG_SRST_DONT_ACTIVATE = 0x0
CONF_REG_SRST_ACTIVATE = 0x1
CONF_REG_CMD_SAMP_OR_AUTO_MODE = 0x0
CONF_REG_CMD_CMD_OR_SAMP_MODE = 0x1
CONF_REG_FLTR_ENABLE = 0x0
CONF_REG_FLTR_BYPASS = 0x1
CONF_REG_GPO2_DRIVE_0 = 0x0
CONF_REG_GPO2_DRIVE_1 = 0x1
CONF_REG_ALERT_DRIVE_TYPE_OPEN_DRAIN = 0x0
CONF_REG_ALERT_DRIVE_TYPE_CMOS = 0x1

class device:
    ##
    #  @brief Create device driver instance
    # 
    #  @param i2c An instance of the I2C driver for the bus on which the device is placed
    #  @return Device handle
    # 
    def __init__( self, i2c ):
        self.iic = i2c_regmap( i2c, BASE_ADDR, 0x100, False )

    ##
    #  @brief Get Conversion result register
    # 
    #  @param result list containing 12-bit conversion result
    #  @param alert_flag list containing Alert flag bit
    #  @param chan list containing Analog input channel
    # 
    def get_conv_res( self, result, alert_flag, chan ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x0, 2 )
        _value = uint16((_bytes[0] << 8) | _bytes[1])
        result[0] = _value & 0xfff
        alert_flag[0] = (_value >> 12) & 0x1
        chan[0] = (_value >> 13) & 0x3

    ##
    #  @brief Set Channel Register
    # 
    #  @param ch0 Channel 0 status
    #  @param ch1 Channel 1 status
    #  @param ch2 Channel 2 status
    #  @param ch3 Channel 3 status
    # 
    def set_channel_register( self, ch0, ch1, ch2, ch3 ):
        _value = uint8((ch0 & 0x1) | ((ch1 & 0x1) << 1) | ((ch2 & 0x1) << 2) | ((ch3 & 0x1) << 3))
        self.iic.write( [_value], 0x1, 1 )

    ##
    #  @brief Get Channel Register
    # 
    #  @param ch0 list containing Channel 0 status bit
    #  @param ch1 list containing Channel 1 status bit
    #  @param ch2 list containing Channel 2 status bit
    #  @param ch3 list containing Channel 3 status bit
    # 
    def get_channel_register( self, ch0, ch1, ch2, ch3 ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x1, 1 )
        ch0[0] = _bytes[0] & 0x1
        ch1[0] = (_bytes[0] >> 1) & 0x1
        ch2[0] = (_bytes[0] >> 2) & 0x1
        ch3[0] = (_bytes[0] >> 3) & 0x1

    ##
    #  @brief Set Configuration register
    # 
    #  @param p_down Power down mode
    #  @param gpo1 Value at GPO 1
    #  @param alert_pol_or_gpo0 Polarity of ALERT/BUSY/GPO 0 pin if (ALERT_EN is 1) or value at GPO 0
    #  @param alert_en_or_gpo0 Enable alert or GPO0
    #  @param busy Alert busy pin indicates busy
    #  @param cycle_timer Timer value for Autocycle mode
    #  @param auto_mode Autocycle mode (depends on CMD mode field)
    #  @param srst Software Reset
    #  @param cmd command mode (depends on Auto mode field)
    #  @param fltr Enable glitch filter
    #  @param gpo2 Value at GPO2
    #  @param alert_drive_type Alert gpo 0 drive type
    # 
    def set_conf_reg( self, p_down, gpo1, alert_pol_or_gpo0, alert_en_or_gpo0, busy, cycle_timer, auto_mode, srst, cmd, fltr, gpo2, alert_drive_type ):
        _bytes = [uint8(), uint8()]
        _value = uint16((p_down & 0x3) | ((gpo1 & 0x1) << 2) | ((alert_pol_or_gpo0 & 0x1) << 3) | ((alert_en_or_gpo0 & 0x1) << 4) | ((busy & 0x1) << 5) | ((cycle_timer & 0x3) << 6) | ((auto_mode & 0x1) << 8) | ((srst & 0x1) << 9) | ((cmd & 0x1) << 10) | ((fltr & 0x1) << 11) | ((gpo2 & 0x1) << 14) | ((alert_drive_type & 0x1) << 15))
        _bytes[0] = uint8((_value >> 8) & 0xff)
        _bytes[1] = uint8(_value & 0xff)
        self.iic.write( _bytes, 0x2, 2 )

    ##
    #  @brief Get Configuration register
    # 
    #  @param p_down list containing Power down mode
    #  @param gpo1 list containing Value at GPO 1 bit
    #  @param alert_pol_or_gpo0 list containing Polarity of ALERT/BUSY/GPO 0 pin if (ALERT_EN is 1) or value at GPO 0 bit
    #  @param alert_en_or_gpo0 list containing Enable alert or GPO0 bit
    #  @param busy list containing Alert busy pin indicates busy bit
    #  @param cycle_timer list containing Timer value for Autocycle mode
    #  @param auto_mode list containing Autocycle mode (depends on CMD mode field) bit
    #  @param srst list containing Software Reset bit
    #  @param cmd list containing command mode (depends on Auto mode field) bit
    #  @param fltr list containing Enable glitch filter bit
    #  @param gpo2 list containing Value at GPO2 bit
    #  @param alert_drive_type list containing Alert gpo 0 drive type bit
    # 
    def get_conf_reg( self, p_down, gpo1, alert_pol_or_gpo0, alert_en_or_gpo0, busy, cycle_timer, auto_mode, srst, cmd, fltr, gpo2, alert_drive_type ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x2, 2 )
        _value = uint16((_bytes[0] << 8) | _bytes[1])
        p_down[0] = _value & 0x3
        gpo1[0] = (_value >> 2) & 0x1
        alert_pol_or_gpo0[0] = (_value >> 3) & 0x1
        alert_en_or_gpo0[0] = (_value >> 4) & 0x1
        busy[0] = (_value >> 5) & 0x1
        cycle_timer[0] = (_value >> 6) & 0x3
        auto_mode[0] = (_value >> 8) & 0x1
        srst[0] = (_value >> 9) & 0x1
        cmd[0] = (_value >> 10) & 0x1
        fltr[0] = (_value >> 11) & 0x1
        gpo2[0] = (_value >> 14) & 0x1
        alert_drive_type[0] = (_value >> 15) & 0x1

    ##
    #  @brief Set Channel 0 low limit register, only 12 least significant bits
    # 
    #  @param ch0_low_limit Channel 0 low limit register, only 12 least significant bits
    # 
    def set_ch0_low_limit( self, ch0_low_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch0_low_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch0_low_limit & 0xff)
        self.iic.write( _bytes, 0x4, 2 )

    ##
    #  @brief Get Channel 0 low limit register, only 12 least significant bits
    # 
    #  @return Channel 0 low limit register, only 12 least significant bits
    # 
    def get_ch0_low_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x4, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set Channel 0 high limit register, only 12 least significant bits
    # 
    #  @param ch0_high_limit Channel 0 high limit register, only 12 least significant bits
    # 
    def set_ch0_high_limit( self, ch0_high_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch0_high_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch0_high_limit & 0xff)
        self.iic.write( _bytes, 0x5, 2 )

    ##
    #  @brief Get Channel 0 high limit register, only 12 least significant bits
    # 
    #  @return Channel 0 high limit register, only 12 least significant bits
    # 
    def get_ch0_high_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x5, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set Channel 0 hysteresis register, only 12 least significant bits
    # 
    #  @param ch0_hyst_limit Channel 0 hysteresis register, only 12 least significant bits
    # 
    def set_ch0_hyst_limit( self, ch0_hyst_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch0_hyst_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch0_hyst_limit & 0xff)
        self.iic.write( _bytes, 0x6, 2 )

    ##
    #  @brief Get Channel 0 hysteresis register, only 12 least significant bits
    # 
    #  @return Channel 0 hysteresis register, only 12 least significant bits
    # 
    def get_ch0_hyst_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x6, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set Channel 1 low limit register, only 12 least significant bits
    # 
    #  @param ch1_low_limit Channel 1 low limit register, only 12 least significant bits
    # 
    def set_ch1_low_limit( self, ch1_low_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch1_low_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch1_low_limit & 0xff)
        self.iic.write( _bytes, 0x7, 2 )

    ##
    #  @brief Get Channel 1 low limit register, only 12 least significant bits
    # 
    #  @return Channel 1 low limit register, only 12 least significant bits
    # 
    def get_ch1_low_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x7, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set Channel 1 high limit register, only 12 least significant bits
    # 
    #  @param ch1_high_limit Channel 1 high limit register, only 12 least significant bits
    # 
    def set_ch1_high_limit( self, ch1_high_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch1_high_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch1_high_limit & 0xff)
        self.iic.write( _bytes, 0x8, 2 )

    ##
    #  @brief Get Channel 1 high limit register, only 12 least significant bits
    # 
    #  @return Channel 1 high limit register, only 12 least significant bits
    # 
    def get_ch1_high_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x8, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set Channel 1 hysteresis register, only 12 least significant bits
    # 
    #  @param ch1_hyst_limit Channel 1 hysteresis register, only 12 least significant bits
    # 
    def set_ch1_hyst_limit( self, ch1_hyst_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch1_hyst_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch1_hyst_limit & 0xff)
        self.iic.write( _bytes, 0x9, 2 )

    ##
    #  @brief Get Channel 1 hysteresis register, only 12 least significant bits
    # 
    #  @return Channel 1 hysteresis register, only 12 least significant bits
    # 
    def get_ch1_hyst_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x9, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set Channel 2 low limit register, only 12 least significant bits
    # 
    #  @param ch2_low_limit Channel 2 low limit register, only 12 least significant bits
    # 
    def set_ch2_low_limit( self, ch2_low_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch2_low_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch2_low_limit & 0xff)
        self.iic.write( _bytes, 0xa, 2 )

    ##
    #  @brief Get Channel 2 low limit register, only 12 least significant bits
    # 
    #  @return Channel 2 low limit register, only 12 least significant bits
    # 
    def get_ch2_low_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0xa, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set Channel 2 high limit register, only 12 least significant bits
    # 
    #  @param ch2_high_limit Channel 2 high limit register, only 12 least significant bits
    # 
    def set_ch2_high_limit( self, ch2_high_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch2_high_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch2_high_limit & 0xff)
        self.iic.write( _bytes, 0xb, 2 )

    ##
    #  @brief Get Channel 2 high limit register, only 12 least significant bits
    # 
    #  @return Channel 2 high limit register, only 12 least significant bits
    # 
    def get_ch2_high_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0xb, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set Channel 2 hysteresis register, only 12 least significant bits
    # 
    #  @param ch2_hyst_limit Channel 2 hysteresis register, only 12 least significant bits
    # 
    def set_ch2_hyst_limit( self, ch2_hyst_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch2_hyst_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch2_hyst_limit & 0xff)
        self.iic.write( _bytes, 0xc, 2 )

    ##
    #  @brief Get Channel 2 hysteresis register, only 12 least significant bits
    # 
    #  @return Channel 2 hysteresis register, only 12 least significant bits
    # 
    def get_ch2_hyst_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0xc, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set Channel 3 low limit register, only 12 least significant bits
    # 
    #  @param ch3_low_limit Channel 3 low limit register, only 12 least significant bits
    # 
    def set_ch3_low_limit( self, ch3_low_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch3_low_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch3_low_limit & 0xff)
        self.iic.write( _bytes, 0xd, 2 )

    ##
    #  @brief Get Channel 3 low limit register, only 12 least significant bits
    # 
    #  @return Channel 3 low limit register, only 12 least significant bits
    # 
    def get_ch3_low_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0xd, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set Channel 3 high limit register, only 12 least significant bits
    # 
    #  @param ch3_high_limit Channel 3 high limit register, only 12 least significant bits
    # 
    def set_ch3_high_limit( self, ch3_high_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch3_high_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch3_high_limit & 0xff)
        self.iic.write( _bytes, 0xe, 2 )

    ##
    #  @brief Get Channel 3 high limit register, only 12 least significant bits
    # 
    #  @return Channel 3 high limit register, only 12 least significant bits
    # 
    def get_ch3_high_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0xe, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set Channel 3 hysteresis register, only 12 least significant bits
    # 
    #  @param ch3_hyst_limit Channel 3 hysteresis register, only 12 least significant bits
    # 
    def set_ch3_hyst_limit( self, ch3_hyst_limit ):
        _bytes = [uint8(), uint8()]
        _bytes[0] = uint8((ch3_hyst_limit >> 8) & 0xff)
        _bytes[1] = uint8(ch3_hyst_limit & 0xff)
        self.iic.write( _bytes, 0xf, 2 )

    ##
    #  @brief Get Channel 3 hysteresis register, only 12 least significant bits
    # 
    #  @return Channel 3 hysteresis register, only 12 least significant bits
    # 
    def get_ch3_hyst_limit( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0xf, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

