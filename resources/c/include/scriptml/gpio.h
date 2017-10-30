/** @file
 *
 * @brief Drive GPIOs using the sysfs interface.
 *
 * The GPIO pins are specified using strings. This is because some platforms
 * use a combination of numbers and letters to specify ports, eg ports
 * named A, B, C and D and pins A0, A1, ... A7, B0, B1, ... and so on.
 *
 * Recommended practice is to hard-code these strings. If GPIO ports need
 * to be indexed by a numerical expression, simply place the GPIO 
 * instances in an list:
 *
 * gpios = [ gpio.device("A0"), gpio.device("A1"), gpio.device("A2"), gpio.device("A3") ]
 * gpio[index].set_level(...)
 *
 * This provides robustness against arbitrary re-assignment of GPIOs.
 *
 * It is recommended to ensure that gpio.device objects are destructed before
 * exiting the executable, because if this is not done, the GPIO device will 
 * be left inaccessible (until unexport is performed manually).
 *
 * Note: On Raspberry Pi, these pins are numbered according to the BCM scheme, 
 * not the BOARD scheme. That is to say, the GPIO numbers are as defined at 
 * chip-level, not board-pinout-level.
 * 
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __RPI_GPIO_H
#define __RPI_GPIO_H

#include <scriptml/devsysfs.h>
#include <unistd.h>
#include <assert.h>

#ifndef __SCRIPTML
#error "This header file can only be used with ScriptML" 
#endif

#define SML_GPIO_IN  0
#define SML_GPIO_OUT 1

typedef ___StringType_T( size:___NULL() ) _str;

struct sml_gpio_handle {
    _str path;         /** Path to GPIO pin sysfs directory       */
    int direction;	   /** Configured direction                   */
};

typedef struct sml_gpio_handle *sml_gpio_handle_t;

/**
 *  @brief Set pin direction
 *
 *  @param dev Device handle
 *  @param dir Direction; one of SML_GPIO_IN or SML_GPIO_OUT
 */
void sml_gpio_set_direction( sml_gpio_handle_t dev, int dir )
{
    dev->direction = dir;
	sml_devsysfs_mono_write( dev->path+"direction", dev->direction==SML_GPIO_OUT?"out":"in" );	
}	 
	 
	 
/**
 *  @brief Initialise access to a GPIO pin
 *
 *  @param num GPIO pin number (as a string) or name 
 *  @return Device handle
 */
sml_gpio_handle_t sml_gpio_open( char *pin )
{
    struct sml_gpio_handle dev; 
	_str spin = pin;
	_str s0 = "/sys/class/gpio/gpio"+spin;
	dev.path = s0+"/";
    sml_gpio_set_direction( &dev, SML_GPIO_IN ); 
    return &dev;
}
	 
	 
/**
 *  @brief End access to a GPIO pin
 *
 *  @param num GPIO pin number (note: not the handle)
 */
void sml_gpio_close( char *pin )
{
}
	 

/**
 *  @brief Set level of an output pin
 *
 *  @param dev Device handle
 *  @param l Level; 0 or 1
 */
void sml_gpio_set_level( sml_gpio_handle_t dev, int l )
{
    assert( dev->direction == SML_GPIO_OUT );
	_str sl = l;
	sml_devsysfs_mono_write( dev->path+"value", sl );	
}	 
	 
	 
/**
 *  @brief Get level of an output pin
 *
 *  @param dev Device handle
 *  @return Level; 0 or 1
 */
int sml_gpio_get_level( sml_gpio_handle_t dev )
{
	_str sl = sml_devsysfs_mono_read_to_eof( dev->path+"value" );	
	int l = sl;
	return l;
}	 
	 	 
#endif
 
