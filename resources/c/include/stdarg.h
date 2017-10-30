/*
 * VarArgs functions
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */
 
/**
 *  @file
 *  @brief VarArgs functions
 *
 *  See https://www.mankier.com/0p/stdarg.h
 *  Support for functions with a variable number of arguments.
 */
 
#ifndef __STDARG_H
#define __STDARG_H

#include <stddef.h>

/** Data type that holds a variable length list of arguments */
// va_list is just a List with no fixed length or element type
#define va_list ___ListType_T(element_type:___NULL(), size:___NULL())

/** Prepare a va_list object */
// Startup just takes a copy of the intrinsic one provided by the interpreter
#define va_start( ap, last ) do { ap = __VarArgs; } while(0)

/** Extract one argument from a va_list object */
// Rotate the slice to bring next element to the end, then pick off the end element
// and cast it to the expected type.
#define va_arg( ap, type ) ( ap = ap[___RangeExpr(start:1, stop:___NULL(), step:___NULL())] + \
								  ap[___RangeExpr(start:___NULL(), stop:1, step:___NULL())], \
						     (type)(ap[-1]) )

/** Destroy a va_list object */
// No action required but we clear down the list in case that saves memory
#define va_end( ap ) do { ap = ___List( elts:___ISeq(), type:___ListType(element_type:___NULL(), size:___NULL()) ); } while(0)

/** Copying va_list objects */
// Simple assignment for the copy opperation
#define va_copy( aq, ap ) do { aq = ap; } while(0)

#endif
