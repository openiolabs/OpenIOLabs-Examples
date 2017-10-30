## @file
#
# @brief Enable script to start running automatically when system powers up.
#
# Note: some implementations may introduce a delay of a few seconds before 
# starting the script, to allow required systems to come up.
#
# Copyright (c) Open IO Labs Ltd 2017
# All Rights Reserved
#

import persistent

##
#  @brief Enable auto-restart of script on reboot or power-up
#
def enable():
	persistent.flag("auto_start").write_int(1)


##
#  @brief Disable auto-restart of script on reboot or power-up
#
def disable():
	persistent.flag("auto_start").write_int(0)
