/** @file
 * 
 *  @brief ScriptML lightweight printing operations
 *
 * These functions can be used to print numbers and strings using 
 * ScriptML's builtin printing capabilities, removing the need to 
 * include <stdio.h> and hence process the printf algoithm. This
 * is used in test scripts to speed up printing. For reference 
 * builds, a stdio-based alternative is swapped in.
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __TEST_PRINT_H
#define __TEST_PRINT_H

// Everything in this directory should have #ifdef __SCRIPTML checks, 
// because it is in the include path for native compilation in the
// "comparison" test suite
#ifndef __SCRIPTML
#include <stdio.h>
#endif

// This is a simplified version of printf - it can only print one int
#ifdef __SCRIPTML
/// Print a single integer - scriptml version
#define printint(value) ___Print(stream:1, values:___ISeq((int)(value)))
#else
/// Print a single integer - reference version
#define printint(value) printf("%d\n", (int)(value))
#endif	


// This is a simplified version of printf - it can only print one float
#ifdef __SCRIPTML
/// Print a single float - scriptml version
#define printfloat(value) ___Print(stream:1, values:___ISeq((float)(value)))
#else
/// Print a single float - reference version
#define printfloat(value) printf("%f\n", (float)(value))
#endif	


// This is a simplified version of printf - it can only print one string
#ifdef __SCRIPTML
/// Print a single string - scriptml version
#define printstr(value)	___Print(stream:1, values:___ISeq((const char *)(value)))
#else
/// Print a single string - reference version
#define printstr(value)	 printf("%s\n", (const char *)(value))
#endif	

#endif
