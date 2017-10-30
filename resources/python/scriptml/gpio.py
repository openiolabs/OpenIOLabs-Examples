## @file
#  @package gpio
#
#  @brief Drive GPIOs using the sysfs interface.
#
# The GPIO pins are specified using strings. This is because some platforms
# use a combination of numbers and letters to specify ports, eg ports
# named A, B, C and D and pins A0, A1, ... A7, B0, B1, ... and so on.
#
# Recommended practice is to hard-code these strings. If GPIO ports need
# to be indexed by a numerical expression, simply place the GPIO 
# instances in an list:
#
# gpios = [ gpio.device("A0"), gpio.device("A1"), gpio.device("A2"), gpio.device("A3") ]
# gpio[index].set_level(...)
#
# This provides robustness against arbitrary re-assignment of GPIOs.
#
# It is recommended to ensure that gpio.device objects are destructed before
# exiting the executable, because if this is not done, the GPIO device will 
# be left inaccessible (until unexport is performed manually).
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

import devsysfs
import coroutines

IN=0
OUT=1

RISING = 0
FALLING = 1
BOTH = 2

def _watcher_coroutine_func( gpio_object, edge_type, callback ):            
    while True:
        l = gpio_object.get_level()
        while l == gpio_object.get_level():
            coroutines._yield()
        if edge_type==BOTH or (edge_type==RISING and l==0) or (edge_type==FALLING and l==1):
            callback(gpio_object.spin)

## @brief GPIO device driver class
#
# Instantiate one of these for each GPIO pin
class device:
    ##
    # @brief Set GPIO pin direction
    #
    # @param dir Direction; one of IN or OUT
    #
    def set_direction( self, d ):
        self.direction = d
        self.direction_dev.write( "out" if self.direction==OUT else "in" )

    ##
    # @brief Initialise access to a GPIO pin
    #
    # @param num GPIO pin number (as a string) or name
    #
    def __init__( self, pin ):
        self.spin = str(pin)
        path = "/sys/class/gpio/gpio"+self.spin+"/"
        self.value_dev = devsysfs.device( path+"value" )
        self.direction_dev = devsysfs.device( path+"direction" )
        self.set_direction( IN )
        self.watcher = None
        
    ##
    # @brief Destroy device driver instance
    #
    def __del__( self ):
        del self.value_dev
        del self.direction_dev
         
    ##
    # @brief Set level of a GPIO output pin
    #
    # @param l Level; 0 or 1
    #
    def set_level( self, l ):
        assert self.direction==OUT, "Attempt to set level of GPIO configured as input"
        self.value_dev.write( str(int(l)) )  
     
    ##
    # @brief Get level of a GPIO output pin
    #
    # @return Level; 0 or 1
    #
    def get_level( self ):
        sl = self.value_dev.read_block_to_eof(0)
        return int(sl)
    
          
    ##
    # @brief Register a callback to be invoked on certain level changes
    #
    # @param edge_type Which edges should invoke the function: RISING, FALLING or BOTH
    # @param callback The callback function. Takes one argument which is the GPIO string
    #
    def set_callback( self, edge_type, callback ):
        self.watcher = coroutines.coroutine( _watcher_coroutine_func, [self, edge_type, callback] )
        
