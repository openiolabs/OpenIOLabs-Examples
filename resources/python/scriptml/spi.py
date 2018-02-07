## @file
#
# @brief Generic SPI bus driver using /dev and ioctl.
#
# General:
#
# Broadly speaking this driver follows the precedents set by the internal
# Linux API for device drivers that access their devices via I2C. 
#
# For maximum flexibility, this driver does not encode the paths to the
# SPI nodes. This is because it will often be desirable to make such
# paths a config option, or to use a symbolic link or other alias in
# lieu of the usual path.
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

import devsysfs
from numpy import *

SPI_CPHA		= 0x01
SPI_CPOL		= 0x02

SPI_MODE_0		= (0|0)
SPI_MODE_1		= (0|SPI_CPHA)
SPI_MODE_2		= (SPI_CPOL|0)
SPI_MODE_3		= (SPI_CPOL|SPI_CPHA)

SPI_CS_HIGH		= 0x04
SPI_LSB_FIRST	= 0x08
SPI_3WIRE		= 0x10
SPI_LOOP		= 0x20
SPI_NO_CS		= 0x40
SPI_READY		= 0x80
SPI_TX_DUAL		= 0x100
SPI_TX_QUAD		= 0x200
SPI_RX_DUAL		= 0x400
SPI_RX_QUAD		= 0x800


# IOCTL request codes
SPI_IOC_MESSAGE = lambda N : ( 0x40006b00 | (((uint32)(N)*32)<<16) )
SPI_IOC_RD_MODE = 0x80016b01
SPI_IOC_WR_MODE = 0x40016b01
SPI_IOC_RD_LSB_FIRST = 0x80016b02
SPI_IOC_WR_LSB_FIRST = 0x40016b02
SPI_IOC_RD_BITS_PER_WORD = 0x80016b03
SPI_IOC_WR_BITS_PER_WORD = 0x40016b03
SPI_IOC_RD_MAX_SPEED_HZ = 0x80046b04
SPI_IOC_WR_MAX_SPEED_HZ = 0x40046b04
SPI_IOC_RD_MODE32 = 0x80046b05
SPI_IOC_WR_MODE32 = 0x40046b05

# Produce a populated transfer structure with NULLs and zeros. Required 
# elements can then be filled in explicitly.
def make_transfer():
    return [
        devsysfs.pointer(None),  #  0:tx_buf
        uint32(),  #  pad0 # struct reserves 64 bits but RPi is 32-bit
        devsysfs.pointer(None),  #  2:rx_buf
        uint32(),  #  pad1 # struct reserves 64 bits but RPi is 32-bit
        uint32(0),  #  4:len
        uint32(0),  #  5:speed_hz
        uint16(0),  #  6:delay_usecs
        uint8(0),   #  7:bits_per_word
        uint8(0),   #  8:cs_change
        uint8(0),   #  9:tx_nbits
        uint8(0),   #  10:rx_nbits
        uint16() ] # pad

class device:
    ## @brief Create device driver instance
    #
    # @param path Absolute path to the device node. 
    #
    # Example paths would be "/dev/spidev0.0", "/dev/spidev0.1" and so on
    #
    def __init__( self, path ):
        self.dev = devsysfs.device( path )

    ## @brief Destroy device driver instance
    #
    def __del__( self, path ):
        del self.dev

    ## @brief Configure SPI device
    # 
    # @param mode SPI mode
    # @param endian 1 for litten-endian 0 for big-endian
    # @param speed_hz Upper limit of SPI clock speed 
    # @param bits_per_word Word size in bits
    # 
    # The spi_msg structures should be filled in with addr, flags and a pointer
    # to a char buffer containing bytes to read or write.
    #
    def config( self, mode, endian, speed_hz, bits_per_word ):
        self.dev.ioctl( SPI_IOC_WR_MODE32, devsysfs.pointer(mode) )
        self.dev.ioctl( SPI_IOC_WR_LSB_FIRST, devsysfs.pointer(endian) )
        self.dev.ioctl( SPI_IOC_WR_MAX_SPEED_HZ, devsysfs.pointer(speed_hz) )
        self.dev.ioctl( SPI_IOC_WR_BITS_PER_WORD, devsysfs.pointer(bits_per_word) )

    ## @brief Generic synchronous SPI operation 
    # 
    # @param xfers Array of transfer structures
    # @param num_xfers Number of transfer structures
    #
    def sync_transfer(self, xfers, num_xfers):
        self.dev.ioctl( SPI_IOC_MESSAGE(num_xfers), devsysfs.pointer(xfers) )


    ## @brief Write to SPI device 
    # 
    # @param buf List of data to write (type corresponds to bits_per_word or bytes if unset)
    # @param count Number of transfer structures
    #
    # Single block write transaction
    #
    def write( self, buf, count ):
        xfer = make_transfer()
        xfer[0] = devsysfs.pointer(buf)
        xfer[4] = uint32(count)
        self.sync_transfer( xfer, 1 )


    ## @brief Read from SPI device 
    #
    # @param buf List of data to read into (type corresponds to bits_per_word or bytes if unset)
    # @param count Number of bytes to read
    #
    # Single block read transaction
    #
    def read( self, buf, count ):
        xfer = make_transfer()
        xfer[2] = devsysfs.pointer(buf)
        xfer[4] = uint32(count)
        self.sync_transfer( xfer, 1 )
