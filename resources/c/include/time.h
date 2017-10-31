/*
 * Standard C time functions
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

/**
 *  @file
 *  @brief Standard C time functions
 *
 * See https://www.mankier.com/0p/time.h
 * Time conversions.
 */

#ifndef __TIME_H
#define __TIME_H

#include <stddef.h>
#include <sys/time.h>

/** time in seconds since the epoch */
typedef unsigned int time_t;


/**
 *  @brief Get the time in seconds since the epoch
 *
 *  @param tloc Filled in with the time if non-NULL
 *  @return The time
 */
time_t time(time_t *tloc)
{
   	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___GetTimeOfDay( args_list:___ArgsList(args:___ISeq() ), variadic_arg:___NULL() );
    time_t secs = l[0]; // seconds
    if( tloc )
        *tloc = secs;
    return secs;
}


/** time seperated into the traditional fields */
struct tm {
    int tm_sec;         /* seconds */
    int tm_min;         /* minutes */
    int tm_hour;        /* hours */
    int tm_mday;        /* day of the month */
    int tm_mon;         /* month */
    int tm_year;        /* year */
    int tm_wday;        /* day of the week */
    int tm_yday;        /* day in the year */
    int tm_isdst;       /* daylight saving time */
};

struct tm _tm;


/**
 *  @brief Seperate time into traditional fields
 *
 *  @param t A time in seconds since the epoch
 *  @return A struct tm filled in with the given time
 */
struct tm *localtime(const time_t *t)
{
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___LocalTime( args_list:___ArgsList(args:___ISeq(*t) ), variadic_arg:___NULL() );
	_tm.tm_sec = l[0];
	_tm.tm_min = l[1];
	_tm.tm_hour = l[2];
	_tm.tm_mday = l[3];
	_tm.tm_mon = l[4];
	_tm.tm_year = l[5];
	_tm.tm_wday = l[6];
	_tm.tm_yday = l[7];
	_tm.tm_isdst = l[8];
	return &_tm;
}

/**
 *  @brief Get the time in string form
 *
 *  @param t A struct tm filled in 
 *  @return The same time as a human-readable string
 */
char *asctime(const struct tm *t)
{
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___AscTime( args_list:___ArgsList(args:___ISeq(t->tm_sec, 
	                                                                                                         t->tm_min,
	                                                                                                         t->tm_hour,
	                                                                                                         t->tm_mday,
	                                                                                                         t->tm_mon,
	                                                                                                         t->tm_year,
	                                                                                                         t->tm_wday,
	                                                                                                         t->tm_yday,
	                                                                                                         t->tm_isdst) ), 
	                                                                      variadic_arg:___NULL() );
	return l[0];
}

#endif
