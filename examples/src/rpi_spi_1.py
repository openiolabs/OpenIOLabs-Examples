import spi
import time
from numpy import *

device = spi.device( "/dev/spidev0.0" )

device.config( 0, 0, 1000000, 8 )
    
while True:
    device.write( "ABCD", 4 )
    c = uint8()
    device.read( [c], 1 )
    print c
