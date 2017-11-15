## @file
#  @package serial
#
#  @brief Simple serial port driver
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

import devsysfs
import termios

FIVEBITS = termios.CS5
SIXBITS = termios.CS6
SEVENBITS = termios.CS7
EIGHTBITS = termios.CS8

PARITY_NONE = 0
PARITY_EVEN = termios.PARENB
PARITY_ODD = termios.PARENB | termios.PARODD
PARITY_MARK = termios.PARENB | termios.PARODD | termios.CMSPAR
PARITY_SPACE = termios.PARENB | termios.CMSPAR

STOPBITS_ONE = 0
STOPBITS_ONE_POINT_FIVE = termios.CSTOPB
STOPBITS_TWO = termios.CSTOPB

## @brief serial device driver class
#
# Instantiate one of these for each serial port
class Serial:
	##
	#  @brief Initialise access to the serial port
	#
	#  @return handle for the serial port
	#
	def __init__( self, 
                  port=None, 
                  baudrate=9600, 
                  bytesize=EIGHTBITS, 
                  parity=PARITY_NONE, 
                  stopbits=STOPBITS_ONE, 
                  timeout=None, 
                  xonxoff=False, 
                  rtscts=False, 
                  write_timeout=None, 
                  dsrdtr=False, 
                  inter_byte_timeout=None ):
        self.port = port        
        self.baudrate = baudrate        
        self.bytesize = bytesize        
        self.parity = parity        
        self.stopbits = stopbits        
        self.timeout = timeout        
        self.xonxoff = xonxoff        
        self.rtscts = rtscts        
        self.write_timeout = write_timeout        
        self.dsrdtr = dsrdtr        
        self.inter_byte_timeout = inter_byte_timeout  

    def open( self ):                      
        self.dev = devsysfs.device( port )
        self._reconfigure_port(True)
    
    def _reconfigure_port(self, force_update=False):
        [iflag, oflag, cflag, lflag, ispeed, ospeed, cc] = termios.tcgetattr(self.dev)
        iflag &= ~(termios.INLCR | termios.IGNCR | termios.ICRNL | termios.IGNBRK)
        iflag &= ~(termios.IUCLC)
        iflag &= ~(termios.PARMRK)
        if self.xonxoff:
            iflag |= (termios.IXON | termios.IXOFF
        else:
            iflag &= ~(termios.IXON | termios.IXOFF)

        oflag &= ~(termios.OPOST | termios.ONLCR | termios.OCRNL)

        cflag &= ~(termios.CRTSCTS | termios.CSIZE | termios.CLOCAL | termios.PARENB | termios.PARODD | termios.CMSPAR)
        cflag |= self.bytesize | self.parity | self.stopbits | termios.CREAD
        if self.rtscts:
            cflag |= termios.CRTSCTS;
        if not self.dsrdtr:
            cflag |= termios.CLOCAL;

        lflag &= ~(termios.ICANON | termios.ECHO | termios.ECHOE)
        lflag &= ~(termios.ECHOK | termios.ECHONL)
        lflag &= ~(termios.ISIG | termios.IEXTEN)        

        ispeed = ospeed = self.baudrate
        termios.tcsetattr(self.dev, TCSANOW, [iflag, oflag, cflag, lflag, ispeed, ospeed, cc])
		 		
	##
	#  @brief End access to the serial port
	#
	def close( self ):
		pass

	##
	#  @brief Write to serial port
	#
	#  @param h serial port handle
	#  @param text text to write to the port
	#
	def write( self, data ):
		self.dev.write( data )
		 
	##
	#  @brief Read from serial port
	#
	#  @param h serial port handle
	#  @return buffer for text read from port
	#
	def read( self, size=1 ):
		return self.dev.read( size )

    def flush( self ):
        termios.tcdrain(self.dev)

    def flush(self):
        termios.tcdrain(self.dev)

    def reset_input_buffer(self):
        termios.tcflush(self.dev, termios.TCIFLUSH)

    def reset_output_buffer(self):
        termios.tcflush(self.dev, termios.TCOFLUSH)

    def send_break(self, duration=0.25):
        termios.tcsendbreak(self.dev, int(duration / 0.25))
