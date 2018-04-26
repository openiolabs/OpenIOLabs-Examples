/** @file
 * 
 *  @brief Math constants
 * 
 *  Auto-generated 26 April 2018; do not edit
 *  
 *  Copyright (c) Open IO Labs Ltd 2017
 *  All Rights Reserved
 */

#ifndef __MATH_H
#define __MATH_H

/** @brief Base of natural logarithms */
#define M_E 2.718281828459045

/** @brief Natural logarithm of 2 */
#define M_LN2 0.6931471805599453

/** @brief Natural logarithm of 10 */
#define M_LN10 2.302585092994046

/** @brief Base-2 logarithm of E */
#define M_LOG2E 1.4426950408889634

/** @brief Base-10 logarithm of E */
#define M_LOG10E 0.4342944819032518

/** @brief Pi */
#define M_PI 3.141592653589793

/** @brief Square root of 1/2 */
#define M_SQRT1_2 0.7071067811865476

/** @brief Square root of 2 */
#define M_SQRT2 1.4142135623730951

/**
 *  @brief Sine
 * 
 *  @param a Angle in radians
 *  @return Sine of the angle a
 */
double sin( double a )
{
    return ___Sin( param0:a );
} 

/**
 *  @brief Cosine
 * 
 *  @param a Angle in radians
 *  @return Cosine of the angle a
 */
double cos( double a )
{
    return ___Cos( param0:a );
} 

/**
 *  @brief Tangent
 * 
 *  @param a Angle in radians
 *  @return Tangent of angle a
 */
double tan( double a )
{
    return ___Tan( param0:a );
} 

/**
 *  @brief Inverse sine
 * 
 *  @param x Sine of an angle
 *  @return The angle in radians
 */
double asin( double x )
{
    return ___ASin( param0:x );
} 

/**
 *  @brief Inverse cosine
 * 
 *  @param x Cosine of an angle
 *  @return The angle in radians
 */
double acos( double x )
{
    return ___ACos( param0:x );
} 

/**
 *  @brief Inverse tangent
 * 
 *  @param x Tangent of an angle
 *  @return The angle in radians
 */
double atan( double x )
{
    return ___ATan( param0:x );
} 

/**
 *  @brief Inverse tangent of a generalised rational (works when y=0)
 * 
 *  @param x Numerator of the tangent
 *  @param y Denominator of the tangent
 *  @return The angle with tangent x/y
 */
double atan2( double x, double y )
{
    return ___ATan2( param0:x, param1:y );
} 

/**
 *  @brief Hyperbolic sine
 * 
 *  @param a Angle in radians
 *  @return Hyperbolic sine of the angle a
 */
double sinh( double a )
{
    return ___Sin( param0:a );
} 

/**
 *  @brief Hyperbolic cosine
 * 
 *  @param a Angle in radians
 *  @return Hyperbolic cosine of the angle a
 */
double cosh( double a )
{
    return ___Cos( param0:a );
} 

/**
 *  @brief Hyperbolic tangent
 * 
 *  @param a Angle in radians
 *  @return Hyperbolic tangent of angle a
 */
double tanh( double a )
{
    return ___Tan( param0:a );
} 

/**
 *  @brief Inverse hyperbolic sine
 * 
 *  @param x Hyperbolic sine of an angle
 *  @return The angle in radians
 */
double asinh( double x )
{
    return ___ASin( param0:x );
} 

/**
 *  @brief Inverse hyperbolic cosine
 * 
 *  @param x Hyperbolic cosine of an angle
 *  @return The angle in radians
 */
double acosh( double x )
{
    return ___ACos( param0:x );
} 

/**
 *  @brief Inverse hyperbolic tangent
 * 
 *  @param x Hyperbolic tangent of an angle
 *  @return The angle in radians
 */
double atanh( double x )
{
    return ___ATan( param0:x );
} 

/**
 *  @brief Absolute value
 * 
 *  @return The absolute value of x
 */
double fabs( double x )
{
    return ___UnaryOperation( poperator:___Abs(), operand:x );
} 

/**
 *  @brief Round toward plus infinity
 * 
 *  @return x rounded toward plus infinity
 */
double ceil( double x )
{
    return ___Ceil( param0:x );
} 

/**
 *  @brief Round towrds minus infinity
 * 
 *  @return x rounded toward minus inifnity
 */
double floor( double x )
{
    return ___Floor( param0:x );
} 

/**
 *  @brief Square root
 * 
 *  @return The square root of x
 */
double sqrt( double x )
{
    return ___Sqrt( param0:x );
} 

/**
 *  @brief Natural exponent
 * 
 *  @return The exponent of x
 */
double exp( double x )
{
    return ___Exp( param0:x );
} 

/**
 *  @brief Natural logarithm
 * 
 *  @return The natural logarithm of x
 */
double log( double x )
{
    return ___Log( param0:x );
} 

/**
 *  @brief Base-10 logarithm
 * 
 *  @return The logarithm of x in base 10
 */
double log10( double x )
{
    return ___Log10( param0:x );
} 

/**
 *  @brief Raise to the power
 * 
 *  @param x Base
 *  @param y Exponent
 *  @return x to the power of y
 */
float powf( double x, double y )
{
    return ___BinaryOperation( poperator:___Power(), operands:___ISeq( x, y ) );
} 

/**
 *  @brief Round to nearest integer
 * 
 *  @param a Floating point number to be rounded
 *  @return Nearest iteger to a
 */
double round( double a )
{
    return ___UnaryOperation( poperator:___Round(), operand:a );
} 

/**
 *  @brief Cube root
 * 
 *  @return Cube root of x
 */
double cbrt( double x )
{
    return ___Cbrt( param0:x );
} 

/**
 *  @brief Floating-point modulo
 * 
 *  @param x Numerator
 *  @param y Denominator
 *  @return x - n * y, where n is the quotient of x / y rounded toward zero
 */
double fmod( double x, double y )
{
    return ___FMod( param0:x, param1:y );
} 

/**
 *  @brief Floating-point maximum value
 * 
 *  @param x Candidate
 *  @param y Candidate
 *  @return the largest value out of x and y
 */
double fmax( double x, double y )
{
    return ___FMax( param0:x, param1:y );
} 

/**
 *  @brief Floating-point minimum value
 * 
 *  @param x Candidate
 *  @param y Candidate
 *  @return the smallest value out of x and y
 */
double fmin( double x, double y )
{
    return ___FMin( param0:x, param1:y );
} 

#endif /* MATH_H */
