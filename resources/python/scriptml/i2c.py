## @file
#  @package i2c
#
#  @brief Generic I2C bus driver using /dev and ioctl.
#
# General:
#
# Broadly speaking this driver follows the precedents set by the internal
# Linux API for device drivers that access their devices via I2C. 
#
# For maximum flexibility, this driver does not encode the paths to the
# i2c nodes. This is because it will often be desirable to make such
# paths a config option, or to use a symbolic link or other alias in
# lieu of the usual path.
#
# Note: this driver does not keep track of I2C addresses. This is a more 
# natural fit for individual device drivers. Firstly, the I2C base address 
# is hard-coded into i2c ICs. Secondly, the address offset, if any, is 
# managed by the IC according to its own documentation (eg as a function
# of Ax pins). Finally, while the Linux i2c driver model carries a device 
# address in its equivalent of our "device" class, that address is *overridden* 
# by the one passed to i2c_transfer() in the i2c_msg struct. We are in fact 
# consistent in behaviour because of this.
#
# Python:
#
# The i2c_msg structure has been encapsuated in free function msg() and 
# the i2c_rdwr_ioctl_data structure has been encapsulated in device.__init__().
# This avoids exposing the ioctl block-building process.
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

import devsysfs
from numpy import *

# Constants for plain I2C API
I2C_M_RD               = 0x0001  ## read data, from slave to master 
                                 # I2C_M_RD is guaranteed to be 0x0001! 
I2C_M_TEN              = 0x0010  ## this is a ten bit chip address 
I2C_M_RECV_LEN         = 0x0400  ## length will be first received byte 
I2C_M_NO_RD_ACK        = 0x0800  ## if I2C_FUNC_PROTOCOL_MANGLING 
I2C_M_IGNORE_NAK       = 0x1000  ## if I2C_FUNC_PROTOCOL_MANGLING 
I2C_M_REV_DIR_ADDR     = 0x2000  ## if I2C_FUNC_PROTOCOL_MANGLING 
I2C_M_NOSTART          = 0x4000  ## if I2C_FUNC_NOSTART 
I2C_M_STOP             = 0x8000  ## if I2C_FUNC_PROTOCOL_MANGLING 
  
# Constants for I2C/SMBUS API
I2C_SMBUS_BLOCK_MAX        = 32
I2C_SMBUS_BLOCK_MAX_PADDED = 34
 
I2C_SMBUS_READ  = 1
I2C_SMBUS_WRITE = 0

# SMBus transaction types (size parameter in the above functions)
#  Note: these no longer correspond to the (arbitrary) PIIX4 internal codes! 
I2C_SMBUS_QUICK            = 0
I2C_SMBUS_BYTE             = 1
I2C_SMBUS_BYTE_DATA        = 2
I2C_SMBUS_WORD_DATA        = 3
I2C_SMBUS_PROC_CALL        = 4
I2C_SMBUS_BLOCK_DATA       = 5
I2C_SMBUS_I2C_BLOCK_BROKEN = 6
I2C_SMBUS_BLOCK_PROC_CALL  = 7           # SMBus 2.0 
I2C_SMBUS_I2C_BLOCK_DATA   = 8
 
# internals
I2C_RDWR               = 0x0707  # Combined R/W transfer (one STOP only) 
I2C_SMBUS	           = 0x0720	 # SMBus transfer 
I2C_SLAVE	           = 0x0703  # Set I2C device address

## @brief I2C bus driver class
#
# Instantiate one of these for each I2C bus you need to use
class device:
    ## @brief Create device driver instance
    #
    # @param path Absolute path to the device node. 
    #
    # Example paths would be "/dev/i2c-1", "/dev/i2c-2" and so on
    #
    def __init__( self, path ):
        self.dev = devsysfs.device( path )

    ## @brief Destroy device driver instance
    def __del__( self, path ):
        del self.dev

    ## @brief Perform an i2c transfer
    #
    # @param msgs A list of message objects 
    # 
    # The message objects must have been created using the msg() function.
    # A list is always required, even if only one msg is present.
    # This function corresponds to the i2c_transfer() function defined in 
    # the Linux kernel. The i2c_rdwr_ioctl_data structure is created
    # automatically from the supplied message list.
    def transfer( self, msgs ):
        # Create struct i2c_rdwr_ioctl_data
        rdwr_arg = [devsysfs.block(msgs),uint32(len(msgs))]
        self.dev.ioctl( I2C_RDWR, devsysfs.block(rdwr_arg) )

    ## @brief Create a single I2C message
    #
    # @param addr I2c address for transfer (not including R/W bit)
    # @param flags Any OR-combinations of the I2C_M_ flags
    # @param buf A list of uint8 types serving as buffer for the transfer
    #
    # The size of the buffer is the length of the transfer, and so a buffer
    # must be provided for reads as well as writes. The buffer is mutated
    # by a read transfer, regardless of any apparent immutability of its 
    # elements. The message created by this call corresponds to the i2c_msg
    # structure defined in the Linux kernel.
    def msg( self, addr, flags, buf ):
        # Create strcut i2c_msg
        return [uint16(addr), uint16(flags), uint16(len(buf)), devsysfs.block(buf)]


    ## @brief Write to I2C device
    # 
    # @param self Device handle
    # @param addr I2C device address
    # @param buf Buffer of data to write
    # @param count Number of bytes to write
    #
    # Single block write transaction
    #
    def write( self, addr, buf ):
        msg = self.msg( addr, 0, buf )
        
        self.transfer([msg])


    ## @brief Read from I2C device
    #
    # @param self Device handle
    # @param addr I2C device address   
    # @param buf Buffer of data for read
    # @param count Number of bytes to read
    #
    # Single block read transaction
    #
    def read( self, addr, count=1 ):    
        buf = []
        for i in range(count):
            buf = buf + [uint8()]
        
        msgs = [self.msg( addr, i2c.I2C_M_RD, buf )]   
        
        self.transfer(msgs)    
        
        return buf
        
    # ======================= I2C/SMBUS ALTERNATIVE API ========================    
        
    ## @brief Set I2C bus device address
    # 
    # @param read_write Data direction; one of I2C_SMBUS_READ or I2C_SMBUS_WRITE
    def smbus_set_addr( self, addr ):
        self.dev.ioctl( I2C_SLAVE, uint32(addr) )
    
    ## @brief Perform I2C/SMBUS access
    # 
    # @param read_write Data direction; one of I2C_SMBUS_READ or I2C_SMBUS_WRITE
    # @param command Depends on the transaction type - usually the register or only byte to transfer
    # @param size The transaction type; one of I2C_SMBUS_QUICK etc
    # @param data Optional extra data block, organised as bytes
    # 
    # The size parameter chooses the kind of transaction (not the size). command is the first byte used
    # and additional bytes are in a block pointed to by data.
    def smbus_access( self, read_write, command, size, data ):
        args = [uint8(read_write), uint8(command), uint32(size), devsysfs.block(data)]        
        self.dev.ioctl( I2C_SMBUS, devsysfs.block(args) )        

    ## SMBus Quick Command
    # ====================
    #
    # This sends a single bit to the device, at the place of the Rd/Wr bit.
    # 
    # Bus sequence `A Addr Rd/Wr [A] P`
    # 
    # @param value Value of bit (1 for read)
    #
    def smbus_write_quick(self, value):
        self.smbus_access(value, 0, I2C_SMBUS_QUICK, [])

    ## SMBus Receive Byte: 
    # ====================
    #
    # This reads a single byte from a device, without specifying a device
    # register. Some devices are so simple that this interface is enough; for
    # others, it is a shorthand if you want to read the same register as in
    # the previous SMBus command.
    # 
    # Bus sequence `S Addr Rd [A] [Data] NA P`
    # 
    # @return The byte that was read
    #
    def smbus_read_byte(self):
        byte = uint8()
        self.smbus_access(I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, [byte])
        return byte

    ## SMBus Send Byte:
    # =================
    # 
    # This operation is the reverse of Receive Byte: it sends a single byte
    # to a device.  See Receive Byte for more information.
    # 
    # Bus sequence: `S Addr Wr [A] Data [A] P`
    # 
    # @param value The byte to write
    #
    def smbus_write_byte(self, value):
        self.smbus_access(I2C_SMBUS_WRITE, value, I2C_SMBUS_BYTE, [])

    ## SMBus Register Read Byte:  
    # ==========================
    # 
    # This reads a single byte from a device, from a designated register.
    # The register is specified through the Comm byte.
    # 
    # Bus sequence `S Addr Wr [A] Comm [A] S Addr Rd [A] [Data] NA P`
    # 
    # @param command The register to read from
    # @return The byte that was read
    #
    def smbus_read_byte_data(self, command):
        byte = uint8()
        self.smbus_access(I2C_SMBUS_READ, command,
                             I2C_SMBUS_BYTE_DATA, [byte])
        return byte

    ## SMBus Register Write Byte:
    # ===========================
    # 
    # This writes a single byte to a device, to a designated register. The
    # register is specified through the Comm byte. This is the opposite of
    # the Read Byte operation.
    # 
    # Bus sequence: `S Addr Wr [A] Comm [A] Data [A] P`
    # 
    # @param command The register to write to
    # @param value the byte to write
    #
    def smbus_write_byte_data(self, command, value):
        byte = uint8(value)
        self.smbus_access(I2C_SMBUS_WRITE, command, I2C_SMBUS_BYTE_DATA, [byte])

    ## SMBus Register Read Word:
    # ==========================
    # 
    # This operation is very like Read Byte; again, data is read from a
    # device, from a designated register that is specified through the Comm
    # byte. But this time, the data is a complete word (16 bits).
    # 
    # Bus sequence: `S Addr Wr [A] Comm [A] S Addr Rd [A] [DataLow] A [DataHigh] NA P`
    # 
    # @param command The register to read from
    # @return The word that was read
    #
    def smbus_read_word_data(self, command):
        word = uint16()
        self.smbus_access(I2C_SMBUS_READ, command, I2C_SMBUS_WORD_DATA, [word])                    
        return word


    ## SMBus Register Write Word: 
    # ===========================
    # 
    # This is the opposite of the Read Word operation. 16 bits
    # of data is written to a device, to the designated register that is
    # specified through the Comm byte. 
    # 
    # Bus sequence: `S Addr Wr [A] Comm [A] DataLow [A] DataHigh [A] P`
    # 
    # @param command The register to write to
    # @param value the word to write
    #
    def smbus_write_word_data(self, command, value):
        word = uint16(value)
        self.smbus_access(I2C_SMBUS_WRITE, command, I2C_SMBUS_WORD_DATA, [word])

    ## SMBus Process Call:
    # ===================
    # 
    # This command selects a device register (through the Comm byte), sends
    # 16 bits of data to it, and reads 16 bits of data in return.
    # 
    # Bus sequence: `S Addr Wr [A] Comm [A] DataLow [A] DataHigh [A] S Addr Rd [A] [DataLow] A [DataHigh] NA P`
    # 
    # @param command The register to write to/read from
    # @param value the word to write
    # @return The word that was read back
    #
    def smbus_process_call(self, command, value):
        word = uint16(value)
        self.smbus_access(I2C_SMBUS_WRITE, command, I2C_SMBUS_PROC_CALL, [word])        
        return word

    ## SMBus Block Read:
    # ==================
    # 
    # This command reads a block of up to 32 bytes from a device, from a 
    # designated register that is specified through the Comm byte. The amount
    # of data is specified by the device in the Count byte.
    # 
    # Bus sequence: `S Addr Wr [A] Comm [A] S Addr Rd [A] [Count] A [Data] A [Data] A ... A [Data] NA P`
    # 
    # @param command The register to read from
    # @return The number of read bytes, and a list containing the read bytes
    #
    def smbus_read_block_data(self, command):
        data = []
        for i in range(I2C_SMBUS_BLOCK_MAX_PADDED):
            data = data + [uint8()]
        self.smbus_access(I2C_SMBUS_READ, command, I2C_SMBUS_BLOCK_DATA, data)
        return data[0], data[1:]

    ## SMBus Block Write:
    # ===================
    # 
    # The opposite of the Block Read command, this writes up to 32 bytes to 
    # a device, to a designated register that is specified through the
    # Comm byte. The amount of data is specified in the Count byte.
    # 
    # Bus sequence: `S Addr Wr [A] Comm [A] Count [A] Data [A] Data [A] ... [A] Data [A] P`
    # 
    # @param command The register to write to
    # @param length The number of bytes
    # @param values Pointer to the block of bytes to write
    #
    def smbus_write_block_data(self, command, length, values):
        data = [length]
        for i in range(length):
            data = data + [uint8(values[i])]
        self.smbus_access(I2C_SMBUS_WRITE, command, I2C_SMBUS_BLOCK_DATA, data)

