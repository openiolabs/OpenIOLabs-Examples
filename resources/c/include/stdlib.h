/** @file
 * 
 *  @brief Standard library
 *
 *  See https://www.mankier.com/0p/stdlib.h
 *  Miscellaneous standard library functions
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __STDLIB_H
#define __STDLIB_H

#include <stddef.h>

typedef struct 
{
	int quot;
	int rem;
} div_t;

typedef struct
{
	int quot;
	int rem;
} ldiv_t;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

/**
 *  @brief Exit script
 *
 *  @param status Script exit status
 *  @return never returns
 */
void exit( int status )
{
	___Exit( value:status );
}


/**
 *  @brief Allocate an array of bytes
 *
 *  @param size Number of bytes
 *  @return pointer to start of buffer
 */
void *malloc(size_t size)
{
    return ___ListDefaultExpr( element_type:___ByteType(), size:size );
}

 
/**
 *  @brief Free an array of bytes
 *
 *  @param ptr Pointer to data
 */
void free(void *ptr)
{
} 

#include "stdlib_math.h"

#endif
