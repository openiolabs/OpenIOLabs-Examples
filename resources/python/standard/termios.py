## @file
#  @package serial
#
#  @brief Simple serial port driver
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

import devsysfs
from numpy import *

# c_cc characters 
VINTR = 0
VQUIT = 1
VERASE = 2
VKILL = 3
VEOF = 4
VTIME = 5
VMIN = 6
VSWTC = 7
VSTART = 8
VSTOP = 9
VSUSP = 10
VEOL = 11
VREPRINT = 12
VDISCARD = 13
VWERASE = 14
VLNEXT = 15
VEOL2 = 16

# c_iflag bits 
IGNBRK  = 0o000001
BRKINT  = 0o000002
IGNPAR  = 0o000004
PARMRK  = 0o000010
INPCK   = 0o000020
ISTRIP  = 0o000040
INLCR   = 0o000100
IGNCR   = 0o000200
ICRNL   = 0o000400
IUCLC   = 0o001000
IXON    = 0o002000
IXANY   = 0o004000
IXOFF   = 0o010000
IMAXBEL = 0o020000
IUTF8   = 0o040000

# c_oflag bits
OPOST   = 0o000001
OLCUC   = 0o000002
ONLCR   = 0o000004
OCRNL   = 0o000010
ONOCR   = 0o000020
ONLRET  = 0o000040
OFILL   = 0o000100
OFDEL   = 0o000200
NLDLY  = 0o000400
NL0  = 0o000000
NL1  = 0o000400
CRDLY  = 0o003000
CR0  = 0o000000
CR1  = 0o001000
CR2  = 0o002000
CR3  = 0o003000
TABDLY = 0o014000
TAB0 = 0o000000
TAB1 = 0o004000
TAB2 = 0o010000
TAB3 = 0o014000
BSDLY  = 0o020000
BS0  = 0o000000
BS1  = 0o020000
FFDLY  = 0o100000
FF0  = 0o000000
FF1  = 0o100000

VTDLY   = 0o040000
VT0   = 0o000000
VT1   = 0o040000

XTABS  = 0o014000

# c_cflag bit meaning 
CBAUD  = 0o010017
B0     = 0o000000         # hang up 
B50    = 0o000001
B75    = 0o000002
B110   = 0o000003
B134   = 0o000004
B150   = 0o000005
B200   = 0o000006
B300   = 0o000007
B600   = 0o000010
B1200  = 0o000011
B1800  = 0o000012
B2400  = 0o000013
B4800  = 0o000014
B9600  = 0o000015
B19200 = 0o000016
B38400 = 0o000017
EXTA = B19200
EXTB = B38400
CSIZE   = 0o000060
CS5   = 0o000000
CS6   = 0o000020
CS7   = 0o000040
CS8   = 0o000060
CSTOPB  = 0o000100
CREAD   = 0o000200
PARENB  = 0o000400
PARODD  = 0o001000
HUPCL   = 0o002000
CLOCAL  = 0o004000
CBAUDEX = 0o010000
B57600   = 0o010001
B115200  = 0o010002
B230400  = 0o010003
B460800  = 0o010004
B500000  = 0o010005
B576000  = 0o010006
B921600  = 0o010007
B1000000 = 0o010010
B1152000 = 0o010011
B1500000 = 0o010012
B2000000 = 0o010013
B2500000 = 0o010014
B3000000 = 0o010015
B3500000 = 0o010016
B4000000 = 0o010017
__MAX_BAUD = B4000000
CIBAUD   = 0o02003600000          # input baud rate (not used) 
CMSPAR   = 0o10000000000          # mark or space (stick) parity 
CRTSCTS  = 0o20000000000          # flow control 

# c_lflag bits 
ISIG    = 0o000001
ICANON  = 0o000002
XCASE   = 0o000004
ECHO    = 0o000010
ECHOE   = 0o000020
ECHOK   = 0o000040
ECHONL  = 0o000100
NOFLSH  = 0o000200
TOSTOP  = 0o000400

ECHOCTL = 0o001000
ECHOPRT = 0o002000
ECHOKE  = 0o004000
FLUSHO  = 0o010000
PENDIN  = 0o040000
IEXTEN  = 0o100000
EXTPROC = 0o200000

# tcflow() and TCXONC use these 
TCOOFF         = 0
TCOON          = 1
TCIOFF         = 2
TCION          = 3

# tcflush() and TCFLSH use these 
TCIFLUSH       = 0
TCOFLUSH       = 1
TCIOFLUSH      = 2

# tcsetattr uses these 
TCSANOW        = 0
TCSADRAIN      = 1
TCSAFLUSH      = 2

#Ioctl request codes
TCGETS          = 0x5401
TCSETS          = 0x5402
TCSETSW         = 0x5403
TCSETSF         = 0x5404
TCGETA          = 0x5405
TCSETA          = 0x5406
TCSETAW         = 0x5407
TCSETAF         = 0x5408
TCSBRK          = 0x5409
TCXONC          = 0x540A
TCFLSH          = 0x540B
TIOCEXCL        = 0x540C
TIOCNXCL        = 0x540D
TIOCSCTTY       = 0x540E
TIOCGPGRP       = 0x540F
TIOCSPGRP       = 0x5410
TIOCOUTQ        = 0x5411
TIOCSTI         = 0x5412
TIOCGWINSZ      = 0x5413
TIOCSWINSZ      = 0x5414
TIOCMGET        = 0x5415
TIOCMBIS        = 0x5416
TIOCMBIC        = 0x5417
TIOCMSET        = 0x5418
TIOCGSOFTCAR    = 0x5419
TIOCSSOFTCAR    = 0x541A
FIONREAD        = 0x541B
TIOCINQ         = FIONREAD
TIOCLINUX       = 0x541C
TIOCCONS        = 0x541D
TIOCGSERIAL     = 0x541E
TIOCSSERIAL     = 0x541F
TIOCPKT         = 0x5420
FIONBIO         = 0x5421
TIOCNOTTY       = 0x5422
TIOCSETD        = 0x5423
TIOCGETD        = 0x5424
TCSBRKP         = 0x5425  # Needed for POSIX tcsendbreak() 
TIOCSBRK        = 0x5427  # BSD compatibility 
TIOCCBRK        = 0x5428  # BSD compatibility 
TIOCGSID        = 0x5429  # Return the session ID of FD 

def tcgetattr(dev):
    c_cc = []
    for i in range(20):
        c_cc += [uint8(0)]
    data = [uint32(0), uint32(0), uint32(0), uint32(0), c_cc, uint32(0), uint32(0)]     
    dev.ioctl( TCGETS, devsysfs.pointer(data) )
    return data[:4] + data[5:] + [data[4]] # slight re-ordering necessetated by the Python API
  

# When is a TCS... constant    
def tcsetattr(dev, when, attributes):
    data = attributes[:4] + [attributes[6]] + attributes[4:6]
    request = {TCSANOW:TCSETS, TCSADRAIN:TCSETSW, TCSAFLUSH:TCSETSF}[when]
    dev.ioctl( request, devsysfs.pointer(data) )
  

# Send zero bits on FD.  
def tcsendbreak( dev, duration ):
    dev.ioctl(TCSBRK, devsysfs.pointer(duration));


# Wait for pending output to be written on FD.
def tcdrain( dev ):
    dev.ioctl(TCSBRK, devsysfs.pointer(1));


# Flush pending data on FD.
def tcflush( dev, queue_selector ):
    dev.ioctl(TCFLSH, devsysfs.pointer(queue_selector));


# Suspend or restart transmission on FD.
def tcflow( dev, action ):
    dev.ioctl(TCXONC, devsysfs.pointer(action));
  