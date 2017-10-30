/*
 * C Standard Library assertions
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

/**
 *  @file
 *  @brief C Standard Library assertions
 *
 *  See https://www.mankier.com/0p/assert.h
 *
 */

#ifndef __ASSERT_H
#define __ASSERT_H

/** @cond INTERNAL */

void __assert( int cond, char *msg )
{
	// Use the intrinsic
	___Assert(test:cond, msg:msg);
}

/** @endcond */

#ifdef NDEBUG
/** Empty assertion macro for when assertions are disabled */ 
#define assert( ignore ) ((void) 0)
#else
/** Assertion macro generates an error if COND is false */ 
#define assert( COND ) __assert( COND, #COND )
#endif

#endif
