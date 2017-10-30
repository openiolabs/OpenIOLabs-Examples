/** @file
 * 
 *  @brief Standard input/output functions
 *
 * See https://www.mankier.com/0p/stdio.h
 * Simplified version of stdio.h, providing a simplified printf/sprintf
 * and putchar

	Copyright 2001, 2002 Georges Menie (www.menie.org)
	stdarg version contributed by Christian Ettinger

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __STDIO_H
#define __STDIO_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>


/**
 *  @brief Write a character to standard output
 *
 *  @param c The character to write
 *  @return Zero on success, non-zero on failure
 */
int putchar(int c)
{
	___PrintCharacter(stream:STDOUT_FILENO, target:c);
	return c;
}

/** @cond INTERNAL */

static void __printchar(char **str, int c)
{
	
	if (str) {
		**str = c;
		++(*str);
	}
	else (void)putchar(c);
}


#define __PAD_RIGHT 1
#define __PAD_ZERO 2

static int __prints(char **out, const char *string, int width, int pad)
{
	register int pc = 0, padchar = ' ';

	if (width > 0) {
		register int len = 0;
		register const char *ptr;
		for (ptr = string; *ptr; ++ptr) ++len;
		if (len >= width) width = 0;
		else width -= len;
		if (pad & __PAD_ZERO) padchar = '0';
	}
	if (!(pad & __PAD_RIGHT)) {
		for ( ; width > 0; --width) {
			__printchar (out, padchar);
			++pc;
		}
	}
	for ( ; *string ; ++string) {
		__printchar (out, *string);
		++pc;
	}
	for ( ; width > 0; --width) {
		__printchar (out, padchar);
		++pc;
	}

	return pc;
}


/* the following should be enough for 32 bit int */
#define __PRINT_BUF_LEN 12

static int __printi(char **out, int i, int b, int sg, int width, int pad, int letbase)
{
	int zeropad = ( width && (pad & __PAD_ZERO) );
	
	// In simple use cases, switch to the intrinsic int-to-string conversion
	if( b==10 && sg && !zeropad )
		return __prints (out, ___Convert(target:i, type:___StringType(size:___NULL())), width, pad);
	if( b==10 && !sg && !zeropad )
		return __prints (out, ___Convert(target:(unsigned)i, type:___StringType(size:___NULL())), width, pad);
		
	char print_buf[__PRINT_BUF_LEN];
	register char *s;
	register int t, neg = 0, pc = 0;
	register unsigned int u = i;

	if (i == 0) {
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return __prints (out, print_buf, width, pad);
	}

	if (sg && b == 10 && i < 0) {
		neg = 1;
		u = -i;
	}

	s = print_buf + __PRINT_BUF_LEN-1;
	*s = '\0';

	while (u) {
		t = u % b;
		if( t >= 10 )
			t += letbase - '0' - 10;
		*--s = t + '0';
		u /= b;
	}

	if (neg) {
		if( zeropad ) {
			__printchar (out, '-');
			++pc;
			--width;
		}
		else {
			*--s = '-';
		}
	}

	return pc + __prints (out, s, width, pad);
}


static int __printf(char **out, float i, int width, int pad)
{
    return __prints (out, ___Convert(target:i, type:___StringType(size:___NULL())), width, pad);
}


static int __print(char **out, const char *format, va_list args )
{
	register int width, pad;
	register int pc = 0;
	char scr[2];

	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			width = pad = 0;
			if (*format == '\0') break;
			if (*format == '%') 
			{
				__printchar (out, *format);
				++pc;
				continue; 
			}
			if (*format == '-') {
				++format;
				pad = __PAD_RIGHT;
			}
			while (*format == '0') {
				++format;
				pad |= __PAD_ZERO;
			}
			for ( ; *format >= '0' && *format <= '9'; ++format) {
				width *= 10;
				width += *format - '0';
			}
			if( *format == 's' ) {
				register char *s = va_arg( args, char * );
				pc += __prints (out, s?s:"(null)", width, pad);
				continue;
			}
			if( *format == 'd' ) {
				pc += __printi (out, va_arg( args, int ), 10, 1, width, pad, 'a');
				continue;
			}
			if( *format == 'x' ) {
				pc += __printi (out, va_arg( args, int ), 16, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'X' ) {
				pc += __printi (out, va_arg( args, int ), 16, 0, width, pad, 'A');
				continue;
			}
			if( *format == 'u' ) {
				pc += __printi (out, va_arg( args, int ), 10, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'c' ) {
				/* char are converted to int then pushed on the stack */
				scr[0] = (char)va_arg( args, int );
				scr[1] = '\0';
				pc += __prints (out, scr, width, pad);
				continue;
			}
			if( *format == 'f' ) {
				pc += __printf (out, va_arg( args, float ), width, pad);
				continue;
			}
		}
		else {
			__printchar (out, *format);
			++pc;
		}
	}
	if (out) **out = '\0';
	va_end( args );
	return pc;
}

/** @endcond */

/**
 *  @brief Formatted print to stdout
 *
 *  @param format Format string
 *  @param ... Argments to populate the format tokens
 *  @return number of characters printed
 */
int printf(const char *format, ...)
{
        va_list args;
        
        va_start( args, format );
        return __print( 0, format, args );
}


/**
 *  @brief Formatted print to string
 *
 *  @param format Format string
 *  @param ... Argments to populate the format tokens
 *  @return number of characters written
 */
int sprintf(char *out, const char *format, ...)
{
        va_list args;
        
        va_start( args, format );
        return __print( &out, format, args );
}

#endif

