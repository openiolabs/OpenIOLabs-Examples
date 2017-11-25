/** @file
 * 
 *  @brief Standard library math functions
 * 
 *  Auto-generated 25 November 2017; do not edit
 *  
 *  Copyright (c) Open IO Labs Ltd 2017
 *  All Rights Reserved
 */

#ifndef __STDLIB_MATH_H
#define __STDLIB_MATH_H

/**
 *  @brief Integer absolute value
 * 
 *  @return The absolute value of x
 */
int abs( int x )
{
    return ___UnaryOperation( poperator:___Abs(), operand:x );
} 

/**
 *  @brief String to float
 * 
 *  @param x String to convert
 *  @return 
 */
double atof( const char * x )
{
    return (float)(___StringType_T( size:___NULL() ))x;
} 

/**
 *  @brief String to integer
 * 
 *  @param x String to convert
 *  @return 
 */
int atoi( const char * x )
{
    return (int)(___StringType_T( size:___NULL() ))x;
} 

#endif /* STDLIB_MATH_H */
