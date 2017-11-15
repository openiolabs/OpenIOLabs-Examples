/** @file
 * 
 *  @brief Serial port configuration
 *
 *  See https://www.mankier.com/3/termios
 *
 * Provides a serial port device with read and write functions, as well 
 * as serial port configurations. The open, read, and write functions
 * are in the standard ScriptML style and are specific to serial I/O.
 * However, the port configuration API is very similar to that of 
 * termios(3). Simply provide the serial port handle in place of the fd.
 * 
 * Note: this is a partial implementation. Serial port configuration is
 * included but certain terminal-specific features are omitted. Priority
 * is given to non-canonical and raw modes (i.e. this is the lower-level
 * part of the API).
 * 
 * Copyright (c) Open IO Labs Ltd 2017
 * All Rights Reserved
 */

#ifndef __TERMIOS_H
#define __TERMIOS_H

#include <devsysfs.h>
#include <stddef.h>

typedef unsigned char   cc_t;
typedef unsigned int    speed_t;
typedef unsigned int    tcflag_t;

#define NCCS 19
struct termios
  {
    tcflag_t c_iflag;           /* input mode flags */
    tcflag_t c_oflag;           /* output mode flags */
    tcflag_t c_cflag;           /* control mode flags */
    tcflag_t c_lflag;           /* local mode flags */
    cc_t c_cc[NCCS];            /* control characters */
    cc_t c_line;                /* line discipline */
    speed_t c_ispeed;           /* input speed */
    speed_t c_ospeed;           /* output speed */
#define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
#define _HAVE_STRUCT_TERMIOS_C_OSPEED 1
  };

/* c_cc characters */
#define VINTR 0
#define VQUIT 1
#define VERASE 2
#define VKILL 3
#define VEOF 4
#define VTIME 5
#define VMIN 6
#define VSWTC 7
#define VSTART 8
#define VSTOP 9
#define VSUSP 10
#define VEOL 11
#define VREPRINT 12
#define VDISCARD 13
#define VWERASE 14
#define VLNEXT 15
#define VEOL2 16

/* c_iflag bits */
#define IGNBRK  0000001
#define BRKINT  0000002
#define IGNPAR  0000004
#define PARMRK  0000010
#define INPCK   0000020
#define ISTRIP  0000040
#define INLCR   0000100
#define IGNCR   0000200
#define ICRNL   0000400
#define IUCLC   0001000
#define IXON    0002000
#define IXANY   0004000
#define IXOFF   0010000
#define IMAXBEL 0020000
#define IUTF8   0040000

/* c_oflag bits */
#define OPOST   0000001
#define OLCUC   0000002
#define ONLCR   0000004
#define OCRNL   0000010
#define ONOCR   0000020
#define ONLRET  0000040
#define OFILL   0000100
#define OFDEL   0000200
#define NLDLY  0000400
#define   NL0  0000000
#define   NL1  0000400
#define CRDLY  0003000
#define   CR0  0000000
#define   CR1  0001000
#define   CR2  0002000
#define   CR3  0003000
#define TABDLY 0014000
#define   TAB0 0000000
#define   TAB1 0004000
#define   TAB2 0010000
#define   TAB3 0014000
#define BSDLY  0020000
#define   BS0  0000000
#define   BS1  0020000
#define FFDLY  0100000
#define   FF0  0000000
#define   FF1  0100000

#define VTDLY   0040000
#define   VT0   0000000
#define   VT1   0040000

#define XTABS  0014000

/* c_cflag bit meaning */
#define CBAUD  0010017
#define  B0     0000000         /* hang up */
#define  B50    0000001
#define  B75    0000002
#define  B110   0000003
#define  B134   0000004
#define  B150   0000005
#define  B200   0000006
#define  B300   0000007
#define  B600   0000010
#define  B1200  0000011
#define  B1800  0000012
#define  B2400  0000013
#define  B4800  0000014
#define  B9600  0000015
#define  B19200 0000016
#define  B38400 0000017
#define EXTA B19200
#define EXTB B38400
#define CSIZE   0000060
#define   CS5   0000000
#define   CS6   0000020
#define   CS7   0000040
#define   CS8   0000060
#define CSTOPB  0000100
#define CREAD   0000200
#define PARENB  0000400
#define PARODD  0001000
#define HUPCL   0002000
#define CLOCAL  0004000
#define CBAUDEX 0010000
#define  B57600   0010001
#define  B115200  0010002
#define  B230400  0010003
#define  B460800  0010004
#define  B500000  0010005
#define  B576000  0010006
#define  B921600  0010007
#define  B1000000 0010010
#define  B1152000 0010011
#define  B1500000 0010012
#define  B2000000 0010013
#define  B2500000 0010014
#define  B3000000 0010015
#define  B3500000 0010016
#define  B4000000 0010017
#define __MAX_BAUD B4000000
#define CIBAUD   002003600000          /* input baud rate (not used) */
#define CMSPAR   010000000000          /* mark or space (stick) parity */
#define CRTSCTS  020000000000          /* flow control */

/* c_lflag bits */
#define ISIG    0000001
#define ICANON  0000002
#define XCASE   0000004
#define ECHO    0000010
#define ECHOE   0000020
#define ECHOK   0000040
#define ECHONL  0000100
#define NOFLSH  0000200
#define TOSTOP  0000400

#define ECHOCTL 0001000
#define ECHOPRT 0002000
#define ECHOKE  0004000
#define FLUSHO  0010000
#define PENDIN  0040000
#define IEXTEN  0100000
#define EXTPROC 0200000

/* tcflow() and TCXONC use these */
#define TCOOFF          0
#define TCOON           1
#define TCIOFF          2
#define TCION           3

/* tcflush() and TCFLSH use these */
#define TCIFLUSH        0
#define TCOFLUSH        1
#define TCIOFLUSH       2

/* tcsetattr uses these */
#define TCSANOW         0
#define TCSADRAIN       1
#define TCSAFLUSH       2


#define _IOT_termios /* Hurd ioctl type field.  */ \
  _IOT (_IOTS (cflag_t), 4, _IOTS (cc_t), NCCS, _IOTS (speed_t), 2)

#ifdef __USE_BSD
/* Compare a character C to a value VAL from the `c_cc' array in a
   `struct termios'.  If VAL is _POSIX_VDISABLE, no character can match it.  */
# define CCEQ(val, c)   ((c) == (val) && (val) != _POSIX_VDISABLE)
#endif

/* Ioctl request codes */
#define TCGETS          0x5401
#define TCSETS          0x5402
#define TCSETSW         0x5403
#define TCSETSF         0x5404
#define TCGETA          0x5405
#define TCSETA          0x5406
#define TCSETAW         0x5407
#define TCSETAF         0x5408
#define TCSBRK          0x5409
#define TCXONC          0x540A
#define TCFLSH          0x540B
#define TIOCEXCL        0x540C
#define TIOCNXCL        0x540D
#define TIOCSCTTY       0x540E
#define TIOCGPGRP       0x540F
#define TIOCSPGRP       0x5410
#define TIOCOUTQ        0x5411
#define TIOCSTI         0x5412
#define TIOCGWINSZ      0x5413
#define TIOCSWINSZ      0x5414
#define TIOCMGET        0x5415
#define TIOCMBIS        0x5416
#define TIOCMBIC        0x5417
#define TIOCMSET        0x5418
#define TIOCGSOFTCAR    0x5419
#define TIOCSSOFTCAR    0x541A
#define FIONREAD        0x541B
#define TIOCINQ         FIONREAD
#define TIOCLINUX       0x541C
#define TIOCCONS        0x541D
#define TIOCGSERIAL     0x541E
#define TIOCSSERIAL     0x541F
#define TIOCPKT         0x5420
#define FIONBIO         0x5421
#define TIOCNOTTY       0x5422
#define TIOCSETD        0x5423
#define TIOCGETD        0x5424
#define TCSBRKP         0x5425  /* Needed for POSIX tcsendbreak() */
#define TIOCSBRK        0x5427  /* BSD compatibility */
#define TIOCCBRK        0x5428  /* BSD compatibility */
#define TIOCGSID        0x5429  /* Return the session ID of FD */

typedef sml_devsysfs_t sml_serial_handle_t;

/**
 *  @brief Initialise access to the serial port
 *
 *  @return Device handle
 */
sml_serial_handle_t sml_serial_open( int portnum )
{
    char dev_path[200];
    sprintf(dev_path, "/dev/ttyUSB%d", portnum);
    return sml_devsysfs_open( dev_path );
}


/**
 *  @brief End access to the serial port
 */
void sml_serial_close( sml_serial_handle_t dev )
{
    sml_devsysfs_close(dev);
}


/**
 *  @brief Write to serial port
 *
 *  @param dev Device handle
 *  @param data Text to write to the port
 */
void sml_serial_write( sml_serial_handle_t dev, char * data ) 
{
    sml_devsysfs_write( dev, data );
}


/**
 *  @brief Read from serial port
 *
 *  @param dev Device handle
 *  @return Buffer for text read from port
 */
char *sml_serial_read( sml_serial_handle_t dev ) 
{
    _str stext = sml_devsysfs_mono_read_to_eof( dev );      
    return stext;
}


/* Return the output baud rate stored in *TERMIOS_P.  */
speed_t cfgetospeed( struct termios *termios_p )
{
    return termios_p->c_ospeed;
}


/* Return the input baud rate stored in *TERMIOS_P.  */
speed_t cfgetispeed( struct termios *termios_p )
{
    return termios_p->c_ispeed;
}


/* Set the output baud rate stored in *TERMIOS_P to SPEED.  */
int cfsetospeed( struct termios *termios_p, speed_t speed )
{
    termios_p->c_ospeed = speed;
    return 0;
}


/* Set the input baud rate stored in *TERMIOS_P to SPEED.  */
int cfsetispeed( struct termios *termios_p, speed_t speed )
{
    termios_p->c_ispeed = speed;
    return 0;
}


/* Set both the input and output baud rates in *TERMIOS_OP to SPEED.  */
int cfsetspeed (struct termios *termios_p, speed_t speed)
{
    termios_p->c_ospeed = speed;
    termios_p->c_ispeed = speed;
    return 0;
}


/* Put the state of FD into *TERMIOS_P.  */
int tcgetattr( sml_serial_handle_t dev,
               struct termios *termios_p)
{
  sml_devsysfs_ioctl(dev, TCGETS, termios_p);    
  return 0;
}


/* Set the state of FD to *TERMIOS_P.
   Values for OPTIONAL_ACTIONS (TCSA*) are in <bits/termios.h>.  */
int tcsetattr( sml_serial_handle_t dev, 
               int optional_actions,
               struct termios *termios_p )
{
    unsigned int cmd;
    switch (optional_actions)
    {
    case TCSANOW:
        cmd = TCSETS;
        break;
    case TCSADRAIN:
        cmd = TCSETSW;
        break;
    case TCSAFLUSH:
        cmd = TCSETSF;
        break;
    default:
        return EINVAL;
    }
    sml_devsysfs_ioctl(dev, cmd, termios_p);
    return 0;
}                      


/* Set *TERMIOS_P to indicate raw mode.  */
void cfmakeraw (struct termios *termios_p)
{
    termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                           | INLCR | IGNCR | ICRNL | IXON);
    termios_p->c_oflag &= ~OPOST;
    termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    termios_p->c_cflag &= ~(CSIZE | PARENB);
    termios_p->c_cflag |= CS8;
    termios_p->c_cc[VMIN] = 1;                /* read returns when one char is available.  */
    termios_p->c_cc[VTIME] = 0;
}

/* Send zero bits on FD.  */
int tcsendbreak( sml_serial_handle_t dev, 
                 int duration )
{
    sml_devsysfs_ioctl(dev, TCSBRK, &duration);
    return 0;
}

/* Wait for pending output to be written on FD.  */
int tcdrain( sml_serial_handle_t dev )
{
    int d = 1;
    sml_devsysfs_ioctl(dev, TCSBRK, &d);
    return 0;
}

/* Flush pending data on FD.
   Values for QUEUE_SELECTOR (TC{I,O,IO}FLUSH) are in <bits/termios.h>.  */
int tcflush( sml_serial_handle_t dev, int queue_selector )
{
    sml_devsysfs_ioctl(dev, TCFLSH, &queue_selector);
    return 0;
}

/* Suspend or restart transmission on FD.
   Values for ACTION (TC[IO]{OFF,ON}) are in <bits/termios.h>.  */
int tcflow( sml_serial_handle_t dev, int action )
{
    sml_devsysfs_ioctl(dev, TCXONC, &action);
    return 0;
}

#endif
