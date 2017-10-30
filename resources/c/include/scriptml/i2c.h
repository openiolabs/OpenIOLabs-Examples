/** @file
 *
 * @brief Generic I2C bus driver using /dev and ioctl.
 *
 * General:
 *
 * Broadly speaking this driver follows the precedents set by the internal
 * Linux API for device drivers that access their devices via I2C. 
 *
 * For maximum flexibility, this driver does not encode the paths to the
 * i2c nodes. This is because it will often be desirable to make such
 * paths a config option, or to use a symbolic link or other alias in
 * lieu of the usual path.
 *
 * Note: this driver does not keep track of I2C addresses. This is a more 
 * natural fit for individual device drivers. Firstly, the I2C base address 
 * is hard-coded into i2c ICs. Secondly, the address offset, if any, is 
 * managed by the IC according to its own documentation (eg as a function
 * of Ax pins). Finally, while the Linux i2c driver model carries a device 
 * address in its equivalent of our "device" class, that address is *overridden* 
 * by the one passed to i2c_transfer() in the i2c_msg struct. We are in fact 
 * consistent in behaviour because of this.
 *
 * C:
 *
 * The i2c_msg structure, the i2c_rdwr_ioctl_data structure and the 
 * sml_i2c_transfer() function have been designed to match the Linux 
 * internal device driver APIs for I2C, in order to simplify porting.
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __I2C_H
#define __I2C_H

#include <scriptml/devsysfs.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef sml_devsysfs_t sml_i2c_t;
 
/** I2C message structure from linux/i2c.h */
struct i2c_msg {
    uint16_t addr;     /** Slave address                        */
    uint16_t flags;	   /** An "or" comination of I2C_M_ values  */
    uint16_t len;      /** Msg length                           */
    uint8_t *buf;      /** Pointer to msg data                  */
};

typedef struct i2c_msg i2c_msg_t;

// Defines for I2C-only interface
#define I2C_M_RD                0x0001  /** read data, from slave to master 
                                         * I2C_M_RD is guaranteed to be 0x0001! */
#define I2C_M_TEN               0x0010  /** this is a ten bit chip address */
#define I2C_M_RECV_LEN          0x0400  /** length will be first received byte */
#define I2C_M_NO_RD_ACK         0x0800  /** if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK        0x1000  /** if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_REV_DIR_ADDR      0x2000  /** if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NOSTART           0x4000  /** if I2C_FUNC_NOSTART */
#define I2C_M_STOP              0x8000  /** if I2C_FUNC_PROTOCOL_MANGLING */

/* internals */
struct i2c_rdwr_ioctl_data {
    struct i2c_msg *msgs;    
    uint32_t nmsgs;          
};

/** @brief Create device driver instance
 *
 * @param path Absolute path to the device node. 
 * @return Device handle
 *
 * Example paths would be "/dev/i2c-1", "/dev/i2c-2" and so on
 */
sml_i2c_t sml_i2c_open( char *path )
{
	return sml_devsysfs_open( path );
}


/** @brief Destroy device driver instance
 * 
 * @param dev Device handle
 */
void sml_i2c_close( sml_i2c_t dev )
{
	return sml_devsysfs_close( dev );
}

// IOCTL request codes
#define I2C_RDWR    0x0707  /* Combined R/W transfer (one STOP only) */
#define I2C_SMBUS	0x0720	/* SMBus transfer */
#define I2C_SLAVE	0x0703	/* Use this slave address */



/** @brief Perform I2C transfer(s)
 * 
 * @param dev Device handle
 * @param msgs An array of i2c_msg structures
 * @param num The number of i2c_msg structures pointed to by msgs
 * 
 * The i2c_msg structures should be filled in with addr, flags and a pointer
 * to a char buffer containing bytes to read or write.
 */
void sml_i2c_transfer( sml_i2c_t dev, struct i2c_msg *msgs, int num )
{
	struct i2c_rdwr_ioctl_data rdwr_arg;
	rdwr_arg.msgs = msgs;
	rdwr_arg.nmsgs = num;
	sml_devsysfs_ioctl( dev, I2C_RDWR, &rdwr_arg );
}


/** @brief Write to I2C device registers
 * 
 * @param dev Device handle
 * @param addr I2C device address
 * @param buf Buffer of data to write
 * @param count Number of bytes to write
 *
 * Single block write transaction
 */
void sml_i2c_write( sml_i2c_t dev, uint8_t addr,
                    const uint8_t *buf, size_t count )	
{
	struct i2c_msg msg[1];	

    msg[0].addr = addr;
    msg[0].flags = 0; // Write
    msg[0].buf = buf;
    msg[0].len = count;
 
    sml_i2c_transfer( dev, msg, 1 );
}


/** @brief Read from I2C device registers
 *
 * @param dev Device handle
 * @param addr I2C device address
 * @param buf Buffer of data for read
 * @param count Number of bytes to read
 *
 * Single block read transaction
 */
void sml_i2c_read( sml_i2c_t dev, uint8_t addr,
                   uint8_t *buf, size_t count )	
{
    struct i2c_msg msg[1];	
	
    msg[0].addr = addr;
    msg[0].flags = I2C_M_RD; // Read
    msg[0].buf = buf;
    msg[0].len = count;
  
    sml_i2c_transfer( dev, msg, 1 );
}

/****************************** I2C/SMBUS ALTERNATIVE API *******************************/

#define I2C_SMBUS_BLOCK_MAX        32
#define I2C_SMBUS_BLOCK_MAX_PADDED 34
struct i2c_smbus_ioctl_data {
	uint8_t read_write;
	uint8_t command;
	uint32_t size;
	uint8_t *data; // Block size I2C_SMBUS_BLOCK_MAX + 2
};

// Defines for I2c/SMBUS interface
#define I2C_SMBUS_READ  1
#define I2C_SMBUS_WRITE 0

/* SMBus transaction types (size parameter in the above functions)
    Note: these no longer correspond to the (arbitrary) PIIX4 internal codes! */
#define I2C_SMBUS_QUICK             0
#define I2C_SMBUS_BYTE              1
#define I2C_SMBUS_BYTE_DATA         2
#define I2C_SMBUS_WORD_DATA         3
#define I2C_SMBUS_PROC_CALL         4
#define I2C_SMBUS_BLOCK_DATA        5
#define I2C_SMBUS_I2C_BLOCK_BROKEN  6
#define I2C_SMBUS_BLOCK_PROC_CALL   7           /* SMBus 2.0 */
#define I2C_SMBUS_I2C_BLOCK_DATA    8


/** @brief Set I2C bus device address
 * 
 * @param dev Device handle
 * @param read_write Data direction; one of I2C_SMBUS_READ or I2C_SMBUS_WRITE
 */
void sml_i2c_smbus_set_addr( sml_i2c_t dev, uint8_t addr )
{
    sml_devsysfs_ioctl( dev, I2C_SLAVE, addr );
}


/** @brief Perform I2C/SMBUS access
 * 
 * @param dev Device handle
 * @param read_write Data direction; one of I2C_SMBUS_READ or I2C_SMBUS_WRITE
 * @param command Depends on the transaction type - usually the register or only byte to transfer
 * @param size The transaction type; one of I2C_SMBUS_QUICK etc
 * @param data Optional extra data block, organised as bytes
 * 
 * The size parameter chooses the kind of transaction (not the size). command is the first byte used
 * and additional bytes are in a block pointed to by data.
 */
void sml_i2c_smbus_access(sml_i2c_t dev, uint8_t read_write, uint8_t command,
		                  uint32_t size, uint8_t *data)
{
	struct i2c_smbus_ioctl_data args;

	args.read_write = read_write;
	args.command = command;
	args.size = size;
	args.data = data;

	sml_devsysfs_ioctl( dev, I2C_SMBUS, &args );
}


/** SMBus Quick Command
 * ====================
 *
 * This sends a single bit to the device, at the place of the Rd/Wr bit.
 * 
 * Bus sequence `A Addr Rd/Wr [A] P`
 * 
 * @param dev Device handle
 * @param value Value of bit (1 for read)
 */
void sml_i2c_smbus_write_quick(sml_i2c_t dev, uint8_t value)
{
	sml_i2c_smbus_access(dev, value, 0, I2C_SMBUS_QUICK, NULL);
}


/** SMBus Receive Byte: 
 * ====================
 *
 * This reads a single byte from a device, without specifying a device
 * register. Some devices are so simple that this interface is enough; for
 * others, it is a shorthand if you want to read the same register as in
 * the previous SMBus command.
 * 
 * Bus sequence `S Addr Rd [A] [Data] NA P`
 * 
 * @param dev Device handle
 * @return The byte that was read
 */
uint8_t sml_i2c_smbus_read_byte(sml_i2c_t dev)
{
	uint8_t byte;
	sml_i2c_smbus_access(dev, I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &byte);

	return byte;
}


/** SMBus Send Byte:
 * =================
 * 
 * This operation is the reverse of Receive Byte: it sends a single byte
 * to a device.  See Receive Byte for more information.
 * 
 * Bus sequence: `S Addr Wr [A] Data [A] P`
 * 
 * @param dev Device handle
 * @param value The byte to write
 */
void sml_i2c_smbus_write_byte(sml_i2c_t dev, uint8_t value)
{
	sml_i2c_smbus_access(dev, I2C_SMBUS_WRITE, value,
				I2C_SMBUS_BYTE, NULL);
}


/** SMBus Register Read Byte:  
 * ==========================
 * 
 * This reads a single byte from a device, from a designated register.
 * The register is specified through the Comm byte.
 * 
 * Bus sequence `S Addr Wr [A] Comm [A] S Addr Rd [A] [Data] NA P`
 * 
 * @param dev Device handle
 * @param command The register to read from
 * @return The byte that was read
 */
uint8_t sml_i2c_smbus_read_byte_data(sml_i2c_t dev, uint8_t command)
{
	uint8_t byte;
	sml_i2c_smbus_access(dev, I2C_SMBUS_READ, command,
			             I2C_SMBUS_BYTE_DATA, &byte);
                         
	return byte;
}


/** SMBus Register Write Byte:
 * ===========================
 * 
 * This writes a single byte to a device, to a designated register. The
 * register is specified through the Comm byte. This is the opposite of
 * the Read Byte operation.
 * 
 * Bus sequence: `S Addr Wr [A] Comm [A] Data [A] P`
 * 
 * @param dev Device handle
 * @param command The register to write to
 * @param value the byte to write
 */
void sml_i2c_smbus_write_byte_data(sml_i2c_t dev, uint8_t command, uint8_t value)
{
	sml_i2c_smbus_access(dev, I2C_SMBUS_WRITE, command,
				         I2C_SMBUS_BYTE_DATA, &value);
}


/** SMBus Register Read Word:
 * ==========================
 * 
 * This operation is very like Read Byte; again, data is read from a
 * device, from a designated register that is specified through the Comm
 * byte. But this time, the data is a complete word (16 bits).
 * 
 * Bus sequence: `S Addr Wr [A] Comm [A] S Addr Rd [A] [DataLow] A [DataHigh] NA P`
 * 
 * @param dev Device handle
 * @param command The register to read from
 * @return The word that was read
 */
uint16_t sml_i2c_smbus_read_word_data(sml_i2c_t dev, uint8_t command)
{
	uint16_t word;
	sml_i2c_smbus_access(dev, I2C_SMBUS_READ, command,
			       I2C_SMBUS_WORD_DATA, &word);
                   
    return word;

}


/** SMBus Register Write Word: 
 * ===========================
 * 
 * This is the opposite of the Read Word operation. 16 bits
 * of data is written to a device, to the designated register that is
 * specified through the Comm byte. 
 * 
 * Bus sequence: `S Addr Wr [A] Comm [A] DataLow [A] DataHigh [A] P`
 * 
 * @param dev Device handle
 * @param command The register to write to
 * @param value the word to write
 */
void sml_i2c_smbus_write_word_data(sml_i2c_t dev, uint8_t command, uint16_t value)
{
	sml_i2c_smbus_access(dev, I2C_SMBUS_WRITE, command,
				I2C_SMBUS_WORD_DATA, &value);
}


/** SMBus Process Call:
 * ===================
 * 
 * This command selects a device register (through the Comm byte), sends
 * 16 bits of data to it, and reads 16 bits of data in return.
 * 
 * Bus sequence: `S Addr Wr [A] Comm [A] DataLow [A] DataHigh [A] S Addr Rd [A] [DataLow] A [DataHigh] NA P`
 * 
 * @param dev Device handle
 * @param command The register to write to/read from
 * @param value the word to write
 * @return The word that was read back
 */
uint16_t sml_i2c_smbus_process_call(sml_i2c_t dev, uint8_t command, uint16_t value)
{
	uint16_t word = value;
	sml_i2c_smbus_access(dev, I2C_SMBUS_WRITE, command,
			     I2C_SMBUS_PROC_CALL, &word);
    
    return word;
}


/** SMBus Block Read:
 * ==================
 * 
 * This command reads a block of up to 32 bytes from a device, from a 
 * designated register that is specified through the Comm byte. The amount
 * of data is specified by the device in the Count byte.
 * 
 * Bus sequence: `S Addr Wr [A] Comm [A] S Addr Rd [A] [Count] A [Data] A [Data] A ... A [Data] NA P`
 * 
 * @param dev Device handle
 * @param command The register to read from
 * @param values Pointer to the block of bytes to read
 * @return The number of read bytes 
 */
int32_t sml_i2c_smbus_read_block_data(sml_i2c_t dev, uint8_t command, uint8_t *values)
{
	uint8_t data[I2C_SMBUS_BLOCK_MAX_PADDED];
	int i;

	sml_i2c_smbus_access(dev, I2C_SMBUS_READ, command,
			       I2C_SMBUS_BLOCK_DATA, &data);

	for (i = 1; i <= data[0]; i++)
		values[i-1] = data[i];
	return data[0];
}


/** SMBus Block Write:
 * ===================
 * 
 * The opposite of the Block Read command, this writes up to 32 bytes to 
 * a device, to a designated register that is specified through the
 * Comm byte. The amount of data is specified in the Count byte.
 * 
 * Bus sequence: `S Addr Wr [A] Comm [A] Count [A] Data [A] Data [A] ... [A] Data [A] P`
 * 
 * @param dev Device handle
 * @param command The register to write to
 * @param length The number of bytes
 * @param values Pointer to the block of bytes to write
 */
void sml_i2c_smbus_write_block_data(sml_i2c_t dev, uint8_t command, uint8_t length,
				 const uint8_t *values)
{
	uint8_t data[I2C_SMBUS_BLOCK_MAX_PADDED];
	int i;
	assert(length <= I2C_SMBUS_BLOCK_MAX);
	for (i = 1; i <= length; i++)
		data[i] = values[i-1];
	data[0] = length;
	sml_i2c_smbus_access(dev, I2C_SMBUS_WRITE, command,
				I2C_SMBUS_BLOCK_DATA, &data);
}

#endif
