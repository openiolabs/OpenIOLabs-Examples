## @file
#  @package builtins
#  
#  @brief ScriptML Python built-in definitions.
#
# This file is automatically imported by ScriptML
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

## @brief Get the number of elements in an iterable object
#
#  @param l An iterable object
#  @return An integer containing the number of elements 
def len(l):
	return ___Len(target=l)
		
## @brief Create an iterable object spanning a range of values
#
#  @param start The value of the first element
#  @param stop The value of the last element, or an infinite range if omitted
#  @param step The difference between neighbouring elements, or one if omitted
#  @return An immutable iterable object spanning the required range
def range(start, stop=0, step=1):
	if stop==0 and step==1: # TODO use None as default values
		return ___RangeExpr(start=0, stop=start, step=1)
	else:
		return ___RangeExpr(start=start, stop=stop, step=step)
		
## @brief Convert to boolean
#
#  @param x The object to convert
#  @return A boolean value
def bool(x=0):
	return ___Convert(target=x, type=___BoolType())
	
## @brief Convert to integer
#
#  @param x The object to convert
#  @return An integer value
def int(x=0):
	return ___Convert(target=x, type=___IntegerType())
	
## @brief Convert to floating-point
#
#  @param x The object to convert
#  @return A floating-point value
def float(x=0.0):
	return ___Convert(target=x, type=___FloatType())
	
## @brief Convert to list
#
#  @param x The object to convert
#  @return A list object
def list(seq=[]):
	return ___Convert(target=seq, type=___ListType(element_type=___NULL(), size=___NULL()))
	
## @brief Convert to tuple
#
#  @param x The object to convert
#  @return A tuple object
def tuple(seq=[]):
	return ___Convert(target=seq, type=___TupleType(element_type=___NULL(), size=___NULL()))
	
## @brief Convert to string
#
#  @param x The object to convert
#  @return A string object
def str(s=""):
	return ___Convert(target=s, type=___StringType(size=___NULL()))
	
## The None value for unassigned objects
___Assign(target=___NamedObjectIdentifier(name="None"), operand=___None() )

## The KeyboardInterrupt exception type (2 is SIGINT)
___TypeDeclaration(type=___SignalExceptionType( signum=2 ), target=___NamedTypeIdentifier(name="KeyboardInterrupt", category=0))

## The ExternalError exception type 
___TypeDeclaration(type=___EnvironmentErrorExceptionType(), target=___NamedTypeIdentifier(name="EnvironmentError", category=0))

## @brief create a list containing only the elements that the lambda evaluates as true
#
# @param operation A lambda or function that is called with elements of items and returns a boolean
# @param items The items to process, iterable
# @return A list containing only the elements that the lambda evaluates as true
def filter( operation, items ):
	return ___ApplyFilter(operation=operation, items=items)

## @brief create a list containing the results of applying the lambda 
#
# @param operation A lambda or function that is called with elements of items and returns some new value
# @param items The items to process, iterable
# @return A list made of of the returns from the lambda
def map( operation, items ):
	return ___ApplyMap(operation=operation, items=items)

## @brief Apply the lambda repeatedly to the list to obtain a single value
#
# @param operation A lambda or function that is called with elements of items and returns some new value
# @param items The items to process, iterable
# @return A single value resulting from applying the lambda repeatedly
def reduce( operation, items ):
	return ___ApplyReduce(operation=operation, items=items)

## @brief Sum of elements in a list
#
# @param items The list to sum
# @return The total value
def sum( items ):
	return reduce( lambda x, y: x+y, items )

## @brief Get smallest element in a list
#
# @param items The list to test
# @return The smallest value
def min( items ):
	return reduce( lambda x, y: x if x<y else y, items )

## @brief Get biggeest element in a list
#
# @param items The list to test
# @return The biggest value
def max( items ):
	return reduce( lambda x, y: x if x>y else y, items )

## @brief Determine if any elements of list are true
#
# @param items The list to test
# @return True if any are true
def any( items ):
	return reduce( lambda x, y: x or y, items )

## @brief Determine if all elements of list are true
#
# @param items The list to test
# @return True if all are true
def all( items ):
	return reduce( lambda x, y: x and y, items )

## @brief Round to nearest whole number
#
# @param value The value to round
# @return Nearest whole number to value
def round( x ):
	return ___UnaryOperation( poperator=___Round(), operand=x )

## @brief Obtain the absolute value
#
# @param value The value
# @return Non-negative number with same absolute value as value
def abs( x ):
	return ___UnaryOperation( poperator=___Abs(), operand=x )

## @brief Obtain quotient and remainder
#
# Note: this version only correct for integer arguments
#
# @param a Numerator
# @param b denominator
# @return A list containing: quotient, remainder
def divmod( a, b ):
	return (a // b, a % b)

# Note: You can overwrite these objects in Python. 

## The boolean value true 
True = bool(1)

## The boolean value false
False = bool(0)

## @brief Sort a list
#
# @param l0 List to sort
#
# @return Sorted list, ascending
#
def sorted(l0):
    l = []
    for x in l0:
        l += [x]
    nl = []
    while len(l) > 0:
        mi=0
        m=l[0]
        for i in range(1, len(l)):
            if l[i] < m:
                m = l[i]
                mi = i
        l = l[0:mi] + l[mi+1:len(l)]
        nl = nl + [m]
    return nl
    
## @brief Stop the script
#    
# @param status The system status code, where 0 indicates success
def exit( status=0 ):
	___Exit( value=status );
    