/*
 * Standard system time functions
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

/**
 *  @file
 *  @brief Standard system time functions
 *
 * See https://www.mankier.com/0p/sys_time.h
 * Get and set the system time in seconds from the epoch. Note: 
 * timezone functionality is not implemented and NULL must be passed
 * for tz. This is justified by the following from the Linux Programmer's Manual
 * 
 * "The use of the timezone structure is obsolete; the tz argument should
 *  normally be specified as NULL.  (See NOTES below.)"
 */

#ifndef __SYS_TIME_H
#define __SYS_TIME_H

#include <stddef.h>

typedef int time_t;
typedef int suseconds_t;

/** Time value structure */
struct timeval {
	time_t      tv_sec;     /* seconds */
	suseconds_t tv_usec;    /* microseconds */
};


/** Time zone structure */
struct timezone {
    int tz_minuteswest;     /* minutes west of Greenwich */
    int tz_dsttime;         /* type of DST correction */
};


/**
 *  @brief Get the current time
 *
 *  @param tv Pointer to the timeval structure to write the time into
 *  @param tz Unused
 *  @return Zero on success, non-zero on failure
 */
int gettimeofday(struct timeval *tv, struct timezone *tz)
{
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___GetTimeOfDay( args_list:___ArgsList(args:___ISeq() ) );	
	tv->tv_sec = l[0];
	tv->tv_usec = l[1];
	return 0;
}


/**
 *  @brief Set the current time
 *
 *  @param tv Pointer to the timeval structure to read the time from
 *  @param tz Unused
 *  @return Zero on success, non-zero on failure
 */
int settimeofday(const struct timeval *tv, const struct timezone *tz)
{
	___SetTimeOfDay( args_list:___ArgsList(args:___ISeq(tv->tv_sec, tv->tv_usec) ) );
	return 0;
}

#endif
