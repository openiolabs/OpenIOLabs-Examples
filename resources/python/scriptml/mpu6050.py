## @file
#  @package mpu6050
# 
#  @brief MPU6050 device driver
# 
#  MPU5060 Digital Gyroscope and Accelerometer 
#  ===========================================
#  
#  Read `who_am_i` to confirm device presence.
#  
#  Write `pwr_mgmt_1` and `pwr_mgmt_2` to configure the device and take it out of sleep.
#  
#  Read raw values from `accel_xout` etc and `gyro_xout` etc.
#  
#  Perform conversions as specified by the data sheet.
#  
#  
#  
#  Auto-generated 21 May 2018; do not edit
#  
#  Copyright (c) Open IO Labs Ltd 2017
#  All Rights Reserved
# 

from i2c_regmap import *
from gpio import *

BASE_ADDR = 0x68

CONFIG_EXT_SYNC_SET_ACCEL_YOUT = 0x6
CONFIG_EXT_SYNC_SET_GYRO_XOUT = 0x2
CONFIG_EXT_SYNC_SET_GYRO_ZOUT = 0x4
CONFIG_EXT_SYNC_SET_ACCEL_ZOUT = 0x7
CONFIG_EXT_SYNC_SET_DISABLED = 0x0
CONFIG_EXT_SYNC_SET_TEMP_OUT = 0x1
CONFIG_EXT_SYNC_SET_ACCEL_XOUT = 0x5
CONFIG_EXT_SYNC_SET_GYRO_YOUT = 0x3

GYRO_CONFIG_FS_SEL_250 = 0x0
GYRO_CONFIG_FS_SEL_2000 = 0x3
GYRO_CONFIG_FS_SEL_500 = 0x1
GYRO_CONFIG_FS_SEL_1000 = 0x2

ACCEL_CONFIG_AFS_SEL_8 = 0x2
ACCEL_CONFIG_AFS_SEL_2 = 0x0
ACCEL_CONFIG_AFS_SEL_4 = 0x1
ACCEL_CONFIG_AFS_SEL_16 = 0x3

PWR_MGMT_1_CLKSEL_PLL_19M = 0x5
PWR_MGMT_1_CLKSEL_STOP = 0x7
PWR_MGMT_1_CLKSEL_INTERNAL = 0x0
PWR_MGMT_1_CLKSEL_PLL_X = 0x1
PWR_MGMT_1_CLKSEL_PLL_Y = 0x2
PWR_MGMT_1_CLKSEL_PLL_Z = 0x3
PWR_MGMT_1_CLKSEL_PLL_32K = 0x4

PWR_MGMT_2_LP_WAKE_CTRL_20 = 0x2
PWR_MGMT_2_LP_WAKE_CTRL_1_25 = 0x0
PWR_MGMT_2_LP_WAKE_CTRL_5 = 0x1
PWR_MGMT_2_LP_WAKE_CTRL_40 = 0x3

class device:
    ##
    #  @brief Create device driver instance
    # 
    #  @param i2c An instance of the I2C driver for the bus on which the device is placed
    #  @param addr_offset The I2C address offset
    #  @param intr_pin An instance of the GPIO driver for the pin connected to the interrupt line
    #  @return Device handle
    # 
    def __init__( self, i2c, addr_offset, intr_pin ):
        self.intr_gpio = intr_pin
        self.iic = i2c_regmap( i2c, BASE_ADDR + addr_offset, 0x100, True )

    ##
    #  @brief Set sample rate divisor
    # 
    #  @param smprt_div sample rate divisor
    # 
    def set_smprt_div( self, smprt_div ):
        self.iic.write( [smprt_div], 0x19, 1 )

    ##
    #  @brief Get sample rate divisor
    # 
    #  @return sample rate divisor
    # 
    def get_smprt_div( self ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x19, 1 )
        return _bytes[0]

    ##
    #  @brief Set configuration
    # 
    #  @param ext_sync_set external frame sync
    #  @param dlpf_cfg digital low-pass filter
    # 
    def set_config( self, ext_sync_set, dlpf_cfg ):
        _value = uint8(((ext_sync_set & 0x7) << 3) | (dlpf_cfg & 0x7))
        self.iic.write( [_value], 0x1a, 1 )

    ##
    #  @brief Set gyroscope configuration
    # 
    #  @param fs_sel full-scale selection
    # 
    def set_gyro_config( self, fs_sel ):
        _value = uint8(((fs_sel & 0x3) << 3))
        self.iic.write( [_value], 0x1b, 1 )

    ##
    #  @brief Set accelerometer configuration
    # 
    #  @param afs_sel accelerometer full-scale selection
    # 
    def set_accel_config( self, afs_sel ):
        _value = uint8(((afs_sel & 0x3) << 3))
        self.iic.write( [_value], 0x1c, 1 )

    ##
    #  @brief Set FIFO enable
    # 
    #  @param temp_fifo_en enable TEMP_OUT to be written to FIFO
    #  @param xg_fifo_en enable GYRO_XOUT to be written to FIFO
    #  @param yg_fifo_en enable GYRO_YOUT to be written to FIFO
    #  @param zg_fifo_en enable GYRO_ZOUT to be written to FIFO
    #  @param accel_fifo_en enable ACCEL_XOUT, ACCEL_YOUT and ACCEL_ZOUT to be written to FIFO
    #  @param slv2_fifo_en enable EXT_SENS_DATA for slave 2 to be written to FIFO
    #  @param slv1_fifo_en enable EXT_SENS_DATA for slave 1 to be written to FIFO
    #  @param slv0_fifo_en enable EXT_SENS_DATA for slave 0 to be written to FIFO
    # 
    def set_fifo_en( self, temp_fifo_en, xg_fifo_en, yg_fifo_en, zg_fifo_en, accel_fifo_en, slv2_fifo_en, slv1_fifo_en, slv0_fifo_en ):
        _value = uint8(((temp_fifo_en & 0x1) << 7) | ((xg_fifo_en & 0x1) << 6) | ((yg_fifo_en & 0x1) << 5) | ((zg_fifo_en & 0x1) << 4) | ((accel_fifo_en & 0x1) << 3) | ((slv2_fifo_en & 0x1) << 2) | ((slv1_fifo_en & 0x1) << 1) | (slv0_fifo_en & 0x1))
        self.iic.write( [_value], 0x23, 1 )

    ##
    #  @brief Set int pin/bypass enable configuration
    # 
    #  @param int_level int pin active low
    #  @param int_open int pin open drain
    #  @param latch_int_en int pin held high until int cleared
    #  @param int_rd_clear int bit cleared by any read
    #  @param fsync_int_level FSYNC int pin active low
    #  @param fsync_int_en enable FSYNC int
    #  @param i2c_bypass_en enable host access to aux I2C
    # 
    def set_int_pin_cfg( self, int_level, int_open, latch_int_en, int_rd_clear, fsync_int_level, fsync_int_en, i2c_bypass_en ):
        _value = uint8(((int_level & 0x1) << 7) | ((int_open & 0x1) << 6) | ((latch_int_en & 0x1) << 5) | ((int_rd_clear & 0x1) << 4) | ((fsync_int_level & 0x1) << 3) | ((fsync_int_en & 0x1) << 2) | ((i2c_bypass_en & 0x1) << 1))
        self.iic.write( [_value], 0x37, 1 )

    ##
    #  @brief Set interrupt enable
    # 
    #  @param fifo_oflow_en enable FIFO overflow interrupt
    #  @param i2c_mst_int_en enable master I2C interrupt
    #  @param data_ready_en enable data ready I2C interrupt
    # 
    def set_int_enable( self, fifo_oflow_en, i2c_mst_int_en, data_ready_en ):
        _value = uint8(((fifo_oflow_en & 0x1) << 4) | ((i2c_mst_int_en & 0x1) << 3) | (data_ready_en & 0x1))
        self.iic.write( [_value], 0x38, 1 )

    ##
    #  @brief Get interrupt status
    # 
    #  @param fifo_oflow_int list containing FIFO overflow interrupt generated bit
    #  @param i2c_mst_int_int list containing master I2C interrupt generated bit
    #  @param data_ready_int list containing data ready I2C interrupt generated bit
    # 
    def get_int_status( self, fifo_oflow_int, i2c_mst_int_int, data_ready_int ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x3a, 1 )
        fifo_oflow_int[0] = (_bytes[0] >> 4) & 0x1
        i2c_mst_int_int[0] = (_bytes[0] >> 3) & 0x1
        data_ready_int[0] = _bytes[0] & 0x1

    ##
    #  @brief Get accelerometer measurement
    # 
    #  @return accelerometer measurement
    # 
    def get_accel_xout( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x3b, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Get accelerometer measurement
    # 
    #  @return accelerometer measurement
    # 
    def get_accel_yout( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x3d, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Get accelerometer measurement
    # 
    #  @return accelerometer measurement
    # 
    def get_accel_zout( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x3f, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Get temperature measurement
    # 
    #  @return temperature measurement
    # 
    def get_temp_out( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x41, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Get gyroscope measurement
    # 
    #  @return gyroscope measurement
    # 
    def get_gyro_xout( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x43, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Get gyroscope measurement
    # 
    #  @return gyroscope measurement
    # 
    def get_gyro_yout( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x45, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Get gyroscope measurement
    # 
    #  @return gyroscope measurement
    # 
    def get_gyro_zout( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x47, 2 )
        return int16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set signal path reset
    # 
    #  @param gyro_reset reset gyroscope analog and digital signal paths
    #  @param accel_reset reset accelerometer analog and digital signal paths
    #  @param temp_reset reset temperature sensor analog and digital signal paths
    # 
    def set_signal_path_reset( self, gyro_reset, accel_reset, temp_reset ):
        _value = uint8(((gyro_reset & 0x1) << 2) | ((accel_reset & 0x1) << 1) | (temp_reset & 0x1))
        self.iic.write( [_value], 0x68, 1 )

    ##
    #  @brief Set user control
    # 
    #  @param fifo_en enable FIFO operations
    #  @param i2c_mst_en enable I2C master mode
    #  @param i2c_if_dis disable I2C interface
    #  @param fifo_reset reset FIFO buffer
    #  @param i2c_mst_reset reset I2C master
    #  @param sig_cond_reset reset signal paths and interrupt condition
    # 
    def set_user_ctrl( self, fifo_en, i2c_mst_en, i2c_if_dis, fifo_reset, i2c_mst_reset, sig_cond_reset ):
        _value = uint8(((fifo_en & 0x1) << 6) | ((i2c_mst_en & 0x1) << 5) | ((i2c_if_dis & 0x1) << 4) | ((fifo_reset & 0x1) << 2) | ((i2c_mst_reset & 0x1) << 1) | (sig_cond_reset & 0x1))
        self.iic.write( [_value], 0x6a, 1 )

    ##
    #  @brief Set power management 1
    # 
    #  @param device_reset reset the entire device
    #  @param sleep low power sleep mode
    #  @param cycle cycle between sleep and sampling
    #  @param temp_dis disable temperature sensor
    #  @param clksel clock source
    # 
    def set_pwr_mgmt_1( self, device_reset, sleep, cycle, temp_dis, clksel ):
        _value = uint8(((device_reset & 0x1) << 7) | ((sleep & 0x1) << 6) | ((cycle & 0x1) << 5) | ((temp_dis & 0x1) << 3) | (clksel & 0x7))
        self.iic.write( [_value], 0x6b, 1 )

    ##
    #  @brief Set power management 2
    # 
    #  @param lp_wake_ctrl low power wakeup frequency
    #  @param stby_xa x-axis accelerometer into standby mode
    #  @param stby_ya y-axis accelerometer into standby mode
    #  @param stby_za z-axis accelerometer into standby mode
    #  @param stby_xg x-axis gyroscope into standby mode
    #  @param stby_yg y-axis gyroscope into standby mode
    #  @param stby_zg z-axis gyroscope into standby mode
    # 
    def set_pwr_mgmt_2( self, lp_wake_ctrl, stby_xa, stby_ya, stby_za, stby_xg, stby_yg, stby_zg ):
        _value = uint8(((lp_wake_ctrl & 0x3) << 6) | ((stby_xa & 0x1) << 5) | ((stby_ya & 0x1) << 4) | ((stby_za & 0x1) << 3) | ((stby_xg & 0x1) << 2) | ((stby_yg & 0x1) << 1) | (stby_zg & 0x1))
        self.iic.write( [_value], 0x6c, 1 )

    ##
    #  @brief Get FIFO count register
    # 
    #  @return FIFO count register
    # 
    def get_fifo_count( self ):
        _bytes = [uint8(), uint8()]
        _bytes = self.iic.read( 0x72, 2 )
        return uint16((_bytes[0] << 8) | _bytes[1])

    ##
    #  @brief Set FIFO read write
    # 
    #  @param fifo_r_w FIFO read write
    # 
    def set_fifo_r_w( self, fifo_r_w ):
        self.iic.write( [fifo_r_w], 0x74, 1 )

    ##
    #  @brief Get FIFO read write
    # 
    #  @return FIFO read write
    # 
    def get_fifo_r_w( self ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x74, 1 )
        return _bytes[0]

    ##
    #  @brief Get who am I
    # 
    #  @param who_am_i list containing who am I
    # 
    def get_who_am_i( self, who_am_i ):
        _bytes = [uint8()]
        _bytes = self.iic.read( 0x75, 1 )
        who_am_i[0] = (_bytes[0] >> 1) & 0x3f

