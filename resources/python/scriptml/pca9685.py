## @file
#  @package pca9685
# 
#  @brief 16-channel, 12-bit PWM Fm+ I2C-bus LED Controller
# 
#  PCA9685 PWM LED Driver
#  ======================
#  
#  The internal clock is 25MHz
#  
#  The PWM waveform frequency is `clock frequency` / (`pre_scale` * 4096)
#  
#  The device powers up in sleep mode, and must be powered up by clearing the `sleep! bit in the `mode1` register before use.
#  
#  The `ai` bit in register `mode1` must be set before any of the `led_on_off` APIs will function correctly, because they use auto-increment to access multiple registers efficiently.
#  
#  The device must be in sleep mode before the `pre_scale` register can be updated.
#  
#  Wakeup procedure: clear `sleep` bit of register `mode1`. Wait at least 500us for the clock to stabilise. set `restart` bit of `mode1` register.
#  
#  Auto-generated 24 January 2018; do not edit
#  
#  Copyright (c) Open IO Labs Ltd 2017
#  All Rights Reserved
# 

from i2c_regmap import *

BASE_ADDR = 0x40

MODE2_OCH_STOP_COMMAND = 0x0
MODE2_OCH_ACK = 0x1
MODE2_OUTDRV_OPEN_DRAIN = 0x0
MODE2_OUTDRV_TOTEM_POLE = 0x1
MODE2_OUTNE_0 = 0x0
MODE2_OUTNE_1 = 0x1
MODE2_OUTNE_HI_Z = 0x2

class device:
    ##
    #  @brief Create device driver instance
    # 
    #  @param i2c An instance of the I2C driver for the bus on which the device is placed
    #  @param addr_offset The I2C address offset
    #  @return Device handle
    # 
    def __init__( self, i2c, addr_offset ):
        self.iic = i2c_regmap( i2c, BASE_ADDR + addr_offset, 0x100, True )

    ##
    #  @brief Set mode register 1
    # 
    #  @param restart RESTART logic state and reset
    #  @param extclk external Clock
    #  @param ai register auto-increment enable
    #  @param sleep low power mode
    #  @param sub1 PCA9685 responds to I2C-bus subaddress 1
    #  @param sub2 PCA9685 responds to I2C-bus subaddress 2
    #  @param sub3 PCA9685 responds to I2C-bus subaddress 3
    #  @param allcall PCA9685 responds to LED All Call I2C-bus
    # 
    def set_mode1( self, restart, extclk, ai, sleep, sub1, sub2, sub3, allcall ):
        _value = uint8(((restart & 0x1) << 7) | ((extclk & 0x1) << 6) | ((ai & 0x1) << 5) | ((sleep & 0x1) << 4) | ((sub1 & 0x1) << 3) | ((sub2 & 0x1) << 2) | ((sub3 & 0x1) << 1) | (allcall & 0x1))
        self.iic.write( [_value], 0x0, 1 )

    ##
    #  @brief Get mode register 1
    # 
    #  @param restart list containing RESTART logic state and reset bit
    #  @param extclk list containing external Clock bit
    #  @param ai list containing register auto-increment enable bit
    #  @param sleep list containing low power mode bit
    #  @param sub1 list containing PCA9685 responds to I2C-bus subaddress 1 bit
    #  @param sub2 list containing PCA9685 responds to I2C-bus subaddress 2 bit
    #  @param sub3 list containing PCA9685 responds to I2C-bus subaddress 3 bit
    #  @param allcall list containing PCA9685 responds to LED All Call I2C-bus bit
    # 
    def get_mode1( self, restart, extclk, ai, sleep, sub1, sub2, sub3, allcall ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x0, 1 )
        restart[0] = (_bytes[0] >> 7) & 0x1
        extclk[0] = (_bytes[0] >> 6) & 0x1
        ai[0] = (_bytes[0] >> 5) & 0x1
        sleep[0] = (_bytes[0] >> 4) & 0x1
        sub1[0] = (_bytes[0] >> 3) & 0x1
        sub2[0] = (_bytes[0] >> 2) & 0x1
        sub3[0] = (_bytes[0] >> 1) & 0x1
        allcall[0] = _bytes[0] & 0x1

    ##
    #  @brief Set mode register 2
    # 
    #  @param invrt output logic state inverted
    #  @param och output change on
    #  @param outdrv LEDn output configuration (when enabled)
    #  @param outne LEDn output configuration when ~OE = 1 (output drivers not enabled)
    # 
    def set_mode2( self, invrt, och, outdrv, outne ):
        _value = uint8(((invrt & 0x1) << 4) | ((och & 0x1) << 3) | ((outdrv & 0x1) << 2) | (outne & 0x3))
        self.iic.write( [_value], 0x1, 1 )

    ##
    #  @brief Set I2C-bus subaddress
    # 
    #  @param channel Channel number; 0 to 2
    #  @param subadr I2C-bus subaddress
    # 
    def set_subadr( self, channel, subadr ):
        self.iic.write( [subadr], 0x2+channel, 1 )

    ##
    #  @brief Set LED output and brightness control
    # 
    #  @param channel Channel number; 0 to 15
    #  @param on_count LED on count
    #  @param full_on LED full on
    #  @param off_count LED off count
    #  @param full_off LED full off
    # 
    def set_led_on_off( self, channel, on_count, full_on, off_count, full_off ):
        _bytes = [uint8(), uint8(), uint8(), uint8()]
        _value = uint32((on_count & 0xfff) | ((full_on & 0x1) << 12) | ((off_count & 0xfff) << 16) | ((full_off & 0x1) << 28))
        _bytes[0] = uint8(_value & 0xff)
        _bytes[1] = uint8((_value >> 8) & 0xff)
        _bytes[2] = uint8((_value >> 16) & 0xff)
        _bytes[3] = uint8((_value >> 24) & 0xff)
        self.iic.write( _bytes, 0x6+channel*4, 4 )

    ##
    #  @brief Set all the LED control registers
    # 
    #  @param on_count LED on count
    #  @param full_on LED full on
    #  @param off_count LED off count
    #  @param full_off LED full off
    # 
    def set_all_led_on_off( self, on_count, full_on, off_count, full_off ):
        _bytes = [uint8(), uint8(), uint8(), uint8()]
        _value = uint32((on_count & 0xfff) | ((full_on & 0x1) << 12) | ((off_count & 0xfff) << 16) | ((full_off & 0x1) << 28))
        _bytes[0] = uint8(_value & 0xff)
        _bytes[1] = uint8((_value >> 8) & 0xff)
        _bytes[2] = uint8((_value >> 16) & 0xff)
        _bytes[3] = uint8((_value >> 24) & 0xff)
        self.iic.write( _bytes, 0xfa, 4 )

    ##
    #  @brief Set prescaler for PWM output frequency
    # 
    #  @param pre_scale prescaler for PWM output frequency
    # 
    def set_pre_scale( self, pre_scale ):
        self.iic.write( [pre_scale], 0xfe, 1 )

