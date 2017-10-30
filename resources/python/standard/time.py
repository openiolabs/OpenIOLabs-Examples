## @file
#  @package time
#
#  @brief ScriptML standard time module
#
# See https://docs.python.org/2/library/time.html
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#


##
#  @brief Get the time since the epoch in seconds
#
# @return time in seconds as a float - includes fractional part
#
def time():
    l = ___GetTimeOfDay( args_list=___ArgsList(args=___ISeq() ) )
    secs = l[0]
    microsecs = l[1]
    return float(secs) + (float(microsecs)/1000000.0)

##
#  @brief Get time since the epoch as two integers
#
# @return a tuple of the form (seconds, microseconds)
#
# Note: this is a ScriptML extension designed to permit the user
# to avoid error due to loss of precision in floating point
# representations (double is just about capable of microsecond
# precision in 2017; float cannot even get to the nearest minute)
#
def integer_time():
    return ___GetTimeOfDay( args_list=___ArgsList(args=___ISeq() ) )
    

##
#  @brief Stop execution for a period of time
#
# @param secs Time to wait in seconds
#
# Fractional values may be used for the wait time, to obtain sub-second
# resolution down to an implementation-defined granularity.
#
def sleep( secs ):
	___Sleep( seconds=int(secs), useconds=int(1000000*secs)%1000000 )
	
