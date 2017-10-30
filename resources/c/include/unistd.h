/** @file
 * 
 *  @brief Miscellaneous C definitions
 *
 *  See https://www.mankier.com/0p/unistd.h
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __UNISTD_H
#define __UNISTD_H

// Some sources say NULL and size_t etc are here, but I put them in stddef.h
#include <stddef.h>

// Using macros rather than functions will be more compact, since a 
// Sleep node is smaller than a Call node with 2 args.

/** Sleep for s seconds */
#define sleep(s) ___Sleep( seconds:s, useconds:___NULL() )

/** Sleep for us microseconds */
#define usleep(us) ___Sleep( seconds:___NULL(), useconds:us )

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#endif
 
