/** @file
 * 
 *  @brief Standard integer types
 *
 *  See https://www.mankier.com/0p/stdint.h
 *  Typedefs for integral types that guarantee bit widths
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __STDINT_H
#define __STDINT_H

/** 64-bit signed integer type */
typedef ___Integer64Type_T() 		int64_t;

/** 32-bit signed integer type */
typedef ___IntegerType_T() 			int32_t;

/** 16-bit signed integer type */
typedef ___ShortType_T() 			int16_t;

/** 8-bit signed integer type */
typedef ___ByteType_T() 			int8_t;

/** 32-bit unsigned integer type */
typedef ___UnsignedIntegerType_T() 	uint32_t;

/** 16-bit unsigned integer type */
typedef ___UnsignedShortType_T() 	uint16_t;

/** 8-bit unsigned integer type */
typedef ___UnsignedByteType_T() 	uint8_t;

#endif
