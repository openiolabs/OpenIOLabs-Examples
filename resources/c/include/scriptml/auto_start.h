/** @file
 *
 * @brief Enable script to start running automatically when system powers up
 *
 * Note: some implementations may introduce a delay of a few seconds before 
 * starting the script, to allow required systems to come up.
 *
 * Copyright (c) Open IO Labs Ltd 2017
 * All Rights Reserved
 */

#ifndef __AUTO_START_H
#define __AUTO_START_H

#include <unistd.h>
#include <assert.h>
#include <persistent.h>

/**
 *  @brief Enable auto-restart of script on reboot or power-up
 */
void sml_auto_start_enable()
{
	sml_persistent_flag_write_int( "auto_start", 1 );
}


/**
 *  @brief Disable auto-restart of script on reboot or power-up
 */
void sml_auto_start_disable()
{
	sml_persistent_flag_write_int( "auto_start", 0 );
}

#endif
 
