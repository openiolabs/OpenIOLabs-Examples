/** @file
 *
 * @brief Generic SPI bus driver using /dev and ioctl.
 *
 * General:
 *
 * Broadly speaking this driver follows the precedents set by the internal
 * Linux API for device drivers that access their devices via I2C. 
 *
 * For maximum flexibility, this driver does not encode the paths to the
 * SPI nodes. This is because it will often be desirable to make such
 * paths a config option, or to use a symbolic link or other alias in
 * lieu of the usual path.
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __SPI_H
#define __SPI_H

#include <scriptml/devsysfs.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef sml_devsysfs_t sml_spi_t;
 
/** SPI message structure from linux/spi/spi.h */
struct spi_ioc_transfer {
	uint8_t *   tx_buf;
    uint32_t    pad0; // struct reserves 64 bits but RPi is 32-bit
	uint8_t *	rx_buf;
    uint32_t    pad1; // struct reserves 64 bits but RPi is 32-bit

	uint32_t	len;
	uint32_t	speed_hz;

	uint16_t	delay_usecs;
	uint8_t  	bits_per_word;
	uint8_t		cs_change;
	uint8_t		tx_nbits;
	uint8_t		rx_nbits;
	uint16_t	pad;
}; // Size 32


#define SPI_CPHA		0x01
#define SPI_CPOL		0x02

#define SPI_MODE_0		(0|0)
#define SPI_MODE_1		(0|SPI_CPHA)
#define SPI_MODE_2		(SPI_CPOL|0)
#define SPI_MODE_3		(SPI_CPOL|SPI_CPHA)

#define SPI_CS_HIGH		0x04
#define SPI_LSB_FIRST		0x08
#define SPI_3WIRE		0x10
#define SPI_LOOP		0x20
#define SPI_NO_CS		0x40
#define SPI_READY		0x80
#define SPI_TX_DUAL		0x100
#define SPI_TX_QUAD		0x200
#define SPI_RX_DUAL		0x400
#define SPI_RX_QUAD		0x800

/** @brief Create device driver instance
 *
 * @param path Absolute path to the device node. 
 * @return Device handle
 *
 * Example paths would be "/dev/spidev0.0", "/dev/spidev0.1" and so on
 */
sml_spi_t sml_spi_open( char *path )
{
	return sml_devsysfs_open( path );
}


/** @brief Destroy device driver instance
 * 
 * @param dev Device handle
 */
void sml_spi_close( sml_spi_t dev )
{
	return sml_devsysfs_close( dev );
}

// IOCTL request codes
#define SPI_IOC_MESSAGE(N) ( 0x40006b00 | (((uint32_t)(N)*32)<<16) )
#define SPI_IOC_RD_MODE 0x80016b01
#define SPI_IOC_WR_MODE 0x40016b01
#define SPI_IOC_RD_LSB_FIRST 0x80016b02
#define SPI_IOC_WR_LSB_FIRST 0x40016b02
#define SPI_IOC_RD_BITS_PER_WORD 0x80016b03
#define SPI_IOC_WR_BITS_PER_WORD 0x40016b03
#define SPI_IOC_RD_MAX_SPEED_HZ 0x80046b04
#define SPI_IOC_WR_MAX_SPEED_HZ 0x40046b04
#define SPI_IOC_RD_MODE32 0x80046b05
#define SPI_IOC_WR_MODE32 0x40046b05


/** @brief Configure SPI device
 * 
 * @param dev Device handle
 * @param mode SPI mode
 * @param endian 1 for litten-endian; 0 for big-endian
 * @param speed_hz Upper limit of SPI clock speed 
 * @param bits_per_word Word size in bits
 * 
 * The spi_msg structures should be filled in with addr, flags and a pointer
 * to a char buffer containing bytes to read or write.
 */
void sml_spi_config( sml_spi_t dev, uint32_t mode, uint8_t endian, uint32_t speed_hz, uint8_t bits_per_word )
{
    sml_devsysfs_ioctl( dev, SPI_IOC_WR_MODE32, &mode );
    sml_devsysfs_ioctl( dev, SPI_IOC_WR_LSB_FIRST, &endian );
    sml_devsysfs_ioctl( dev, SPI_IOC_WR_MAX_SPEED_HZ, &speed_hz );
    sml_devsysfs_ioctl( dev, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word );
}


/** @brief Generic synchronous SPI operation 
 * 
 * @param dev Device handle
 * @param xfers Array of transfer structures
 * @param num_xfers Number of transfer structures
*/
void sml_spi_sync_transfer(sml_spi_t dev, struct spi_ioc_transfer *xfers, unsigned int num_xfers)
{
    sml_devsysfs_ioctl( dev, SPI_IOC_MESSAGE(num_xfers), xfers );
}


/** @brief Write to SPI device 
 * 
 * @param dev Device handle
 * @param xfers buf Buffer of data to write
 * @param count Number of transfer structures
 *
 * Single block write transaction
 */
void sml_spi_write( sml_spi_t dev, const uint8_t *buf, size_t count )	
{
	struct spi_ioc_transfer xfer;
	xfer.tx_buf = buf;
	xfer.len = count;
	sml_spi_sync_transfer( dev, &xfer, 1 );
}


/** @brief Read from SPI device 
 *
 * @param dev Device handle
 * @param buf Buffer of data for read
 * @param count Number of bytes to read
 *
 * Single block read transaction
 */
void sml_spi_read( sml_spi_t dev, uint8_t *buf, size_t count )	
{
	struct spi_ioc_transfer xfer;
	xfer.rx_buf = buf;
	xfer.len = count;
	sml_spi_sync_transfer( dev, &xfer, 1 );
}

#endif
