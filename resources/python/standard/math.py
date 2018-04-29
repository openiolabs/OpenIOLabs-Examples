## @file
#  @package math
# 
#  @brief Math constants
# 
#  Auto-generated 29 April 2018; do not edit
#  
#  Copyright (c) Open IO Labs Ltd 2017
#  All Rights Reserved
# 

## @brief Base of natural logarithms
e = 2.718281828459045

## @brief Pi
pi = 3.141592653589793

##
#  @brief Sine
# 
#  @param a Angle in radians
#  @return Sine of the angle a
# 
def sin( a ):
    return ___Sin( param0=a )

##
#  @brief Cosine
# 
#  @param a Angle in radians
#  @return Cosine of the angle a
# 
def cos( a ):
    return ___Cos( param0=a )

##
#  @brief Tangent
# 
#  @param a Angle in radians
#  @return Tangent of angle a
# 
def tan( a ):
    return ___Tan( param0=a )

##
#  @brief Inverse sine
# 
#  @param x Sine of an angle
#  @return The angle in radians
# 
def asin( x ):
    return ___ASin( param0=x )

##
#  @brief Inverse cosine
# 
#  @param x Cosine of an angle
#  @return The angle in radians
# 
def acos( x ):
    return ___ACos( param0=x )

##
#  @brief Inverse tangent
# 
#  @param x Tangent of an angle
#  @return The angle in radians
# 
def atan( x ):
    return ___ATan( param0=x )

##
#  @brief Inverse tangent of a generalised rational (works when y=0)
# 
#  @param x Numerator of the tangent
#  @param y Denominator of the tangent
#  @return The angle with tangent x/y
# 
def atan2( x, y ):
    return ___ATan2( param0=x, param1=y )

##
#  @brief Hyperbolic sine
# 
#  @param a Angle in radians
#  @return Hyperbolic sine of the angle a
# 
def sinh( a ):
    return ___Sin( param0=a )

##
#  @brief Hyperbolic cosine
# 
#  @param a Angle in radians
#  @return Hyperbolic cosine of the angle a
# 
def cosh( a ):
    return ___Cos( param0=a )

##
#  @brief Hyperbolic tangent
# 
#  @param a Angle in radians
#  @return Hyperbolic tangent of angle a
# 
def tanh( a ):
    return ___Tan( param0=a )

##
#  @brief Inverse hyperbolic sine
# 
#  @param x Hyperbolic sine of an angle
#  @return The angle in radians
# 
def asinh( x ):
    return ___ASin( param0=x )

##
#  @brief Inverse hyperbolic cosine
# 
#  @param x Hyperbolic cosine of an angle
#  @return The angle in radians
# 
def acosh( x ):
    return ___ACos( param0=x )

##
#  @brief Inverse hyperbolic tangent
# 
#  @param x Hyperbolic tangent of an angle
#  @return The angle in radians
# 
def atanh( x ):
    return ___ATan( param0=x )

##
#  @brief Absolute value
# 
#  @return The absolute value of x
# 
def fabs( x ):
    return ___UnaryOperation( poperator=___Abs(), operand=x )

##
#  @brief Round toward plus infinity
# 
#  @return x rounded toward plus infinity
# 
def ceil( x ):
    return ___Ceil( param0=x )

##
#  @brief Round towrds minus infinity
# 
#  @return x rounded toward minus inifnity
# 
def floor( x ):
    return ___Floor( param0=x )

##
#  @brief Square root
# 
#  @return The square root of x
# 
def sqrt( x ):
    return ___Sqrt( param0=x )

##
#  @brief Natural exponent
# 
#  @return The exponent of x
# 
def exp( x ):
    return ___Exp( param0=x )

##
#  @brief Natural logarithm
# 
#  @return The natural logarithm of x
# 
def log( x ):
    return ___Log( param0=x )

##
#  @brief Base-10 logarithm
# 
#  @return The logarithm of x in base 10
# 
def log10( x ):
    return ___Log10( param0=x )

##
#  @brief Raise to the power
# 
#  @param x Base
#  @param y Exponent
#  @return x to the power of y
# 
def pow( x, y ):
    return ___BinaryOperation( poperator=___Power(), operands=___ISeq( x, y ) )

##
#  @brief Round to nearest integer
# 
#  @param a Floating point number to be rounded
#  @return Nearest iteger to a
# 
def round( a ):
    return ___UnaryOperation( poperator=___Round(), operand=a )

