## @file
#  @package numpy
#  
#  @brief ScriptML elments of numpy
#
# See https://docs.python.org/2/library/time.html
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

import math

___TypeDeclaration( type=___BoolType_T(), target=___NamedTypeIdentifier_T(name="bool_", category=0), specifiers=___ISeq() )
___TypeDeclaration( type=___IntegerType_T(), target=___NamedTypeIdentifier_T(name="int_", category=0), specifiers=___ISeq() )
___TypeDeclaration( type=___IntegerType_T(), target=___NamedTypeIdentifier_T(name="intc", category=0), specifiers=___ISeq() )
___TypeDeclaration( type=___IntegerType_T(), target=___NamedTypeIdentifier_T(name="intp", category=0), specifiers=___ISeq() )

___TypeDeclaration( type=___ByteType_T(), target=___NamedTypeIdentifier_T(name="int8", category=0), specifiers=___ISeq() )
___TypeDeclaration( type=___ShortType_T(), target=___NamedTypeIdentifier_T(name="int16", category=0), specifiers=___ISeq() )
___TypeDeclaration( type=___IntegerType_T(), target=___NamedTypeIdentifier_T(name="int32", category=0), specifiers=___ISeq() )
___TypeDeclaration( type=___Integer64Type_T(), target=___NamedTypeIdentifier_T(name="int64", category=0), specifiers=___ISeq() )
___TypeDeclaration( type=___UnsignedByteType_T(), target=___NamedTypeIdentifier_T(name="uint8", category=0), specifiers=___ISeq() )
___TypeDeclaration( type=___UnsignedShortType_T(), target=___NamedTypeIdentifier_T(name="uint16", category=0), specifiers=___ISeq() )
___TypeDeclaration( type=___UnsignedIntegerType_T(), target=___NamedTypeIdentifier_T(name="uint32", category=0), specifiers=___ISeq() )

___TypeDeclaration( type=___FloatType_T(), target=___NamedTypeIdentifier_T(name="float32", category=0), specifiers=___ISeq() )

##
#  @brief Arithmetic mean
# 
#  @param l list of numeric values
#  @return The mean value
# 
def mean(l):
    return float(sum(l)) / len(l)
    
    
##
#  @brief Median value
# 
#  @param l list of numeric values
#  @return The median value
# 
def median(l):
    sl = sorted(l)
    lm = []
    if len(sl) % 2 == 1:
        lm = [sl[(len(sl)-1)/2]]
    else:
        lm = [sl[len(sl)/2-1], sl[len(sl)/2]]         
    return mean(lm)
    
    
##
#  @brief Mode value
# 
#  @param l list of numeric values
#  @return The mode value
# 
def mode(l):
    hist={}
    for x in l:
        if x in hist:
            hist[x] += 1
        else:
            hist[x] = 1
    mx=l[0]
    mh=hist[mx]
    for x in hist:
        h = hist[x]
        if h > mh:
            mh = h
            mx = x
    return mx
        
        
##
#  @brief Variance
# 
#  @param l list of numeric values
#  @return The variance
# 
def var(l):
    m = mean(l)
    vs = 0.0
    for x in l:
        vs += (x-m)*(x-m)
    return vs / len(l)
    
    
##
#  @brief Standard deviation 
# 
#  @param l list of numeric values
#  @return The standard deviation
# 
def std(l):
    return math.sqrt( var(l) )
        
        
## 
# @brief Product of elements in a list
#
# @param items The list of values
# @return The product
#
def prod( items ):
	return reduce( lambda x, y: x*y, items )
        
        
    