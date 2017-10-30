/** @file
 * 
 *  @brief Standard string library
 *
 *  See https://www.mankier.com/0p/string.h
 *  C string and memory manipulation functions
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>

/**
 *  @brief Get length of string
 *
 *  @param s Pointer to the string
 *  @return number of characters in the string
 */
size_t strlen(const char *s)
{
	size_t i=0;
	while( *s++ )
		i++;
	return i;
}


/**
 *  @brief Copy string
 *
 *  @param dest Pointer to destination string buffer
 *  @param src Pointer to source string buffer
 *  @return Pointer to destination string buffer
 */
char *strcpy(char *dest, const char *src)
{
	char *dp = dest;
	while( *src ) 
		*dp++ = *src++;
	*dp++ = (char)0;
	return dest;
}


/**
 *  @brief Copy string
 *
 *  @param dest Pointer to destination string buffer
 *  @param src Pointer to source string buffer
 *  @param n Number of characters to copy
 *  @return Pointer to destination string buffer 
 */
char *strncpy(char *dest, const char *src, size_t n)
{
	char *dp = dest;
    int i;
	for( i=0; i<n && *src; i++ )     
		*dp++ = *src++;
	return dest;
}


/**
 *  @brief Concatenate string
 *
 *  @param dest Pointer to target string buffer
 *  @param src Pointer to source string buffer
 *  @return Pointer to target string buffer
 */
char *strcat(char *dest, const char *src)
{
	size_t dl = strlen(dest);
	strcpy( dest+dl, src );
	return dest;
}


/**
 *  @brief Concatenate string
 *
 *  @param dest Pointer to target string buffer
 *  @param src Pointer to source string buffer
 *  @param n Number of characters to copy
 *  @return Pointer to target string buffer (always null-terminated)
 */
char *strncat(char *dest, const char *src, size_t n)
{
	size_t dl = strlen(dest);
	strncpy( dest+dl, src, n );
	dest[dl+n] = 0;
	return dest;
}


/**
 *  @brief Compare strings
 *
 *  @param s1 Pointer to first string
 *  @param s2 Pointer to second string
 *  @return Comparison value: negative when s1<s2, zero when s1==s2 and positive when s1>s2
 */
int strcmp(const char *s1, const char *s2)
{
	while( *s1 && *s2 )
	{
		if( *s1 != *s2 ) 
			return *s1 - *s2;
		s1++;
		s2++;
	}
	// Whichever ended first reads '\0', which is smaller than other characters
	return *s1 - *s2;
}


/**
 *  @brief Compare sub-strings, upto n characters
 *
 *  @param s1 Pointer to first string
 *  @param s2 Pointer to second string
 *  @param n Maximum number of charaqcters to compare
 *  @return Comparison value: negative when s1<s2, zero when s1==s2 and positive when s1>s2
 */
int strncmp(const char *s1, const char *s2, int n)
{
	int i;
	for( i=0; i<n && *s1 && *s2; i++ )
	{
		if( *s1 != *s2 ) 
			return *s1 - *s2;
		s1++;
		s2++;
	}
	// Whichever ended first reads '\0', which is smaller than other characters
	if( i<n )
		return *s1 - *s2;
	else
		return 0; // ran out of characters so call them the same
}


/**
 *  @brief Search for a character in a string
 *
 *  @param s Pointer to first byte of string
 *  @param c Byte value to search for
 *  @return Pointer to found character or NULL if not found
 */
char *strchr(const char *s, int c)
{
	while( *s )
	{
		if( *s==c )
			return s;
		s++;
	}
	return NULL;
}


/**
 *  @brief Reverse search for a character in a string
 *
 *  @param s Pointer to first byte of string
 *  @param c Byte value to search for
 *  @return Pointer to found character or NULL if not found
 */
char *strrchr(const char *s, int c)
{
	// One-pass algorithm
	char *pos = NULL;
	while( *s )
	{
		if( *s==c )
			pos = s;
		s++;
	}
	return pos;
}


/**
 *  @brief Search for one of a set of characters in a string
 *
 *  @param s Pointer to first byte of string
 *  @param accept String containing the set of characters
 *  @return Pointer to found character or NULL if not found
 */
char *strpbrk(const char *s, const char *accept)
{
	while( *s )
	{
		if( strchr(accept, *s) )
			return s;
		s++;
	}
	return NULL;
}


/**
 *  @brief Count the number of contiguous characters at the beginning of a string in the accept set
 *
 *  @param s Pointer to first byte of string
 *  @param accept String containing the set of characters to accept
 *  @return Number of initial characters not in set
 */
size_t strspn(const char *s, const char *accept)
{
	const char *d = s;
	while( *d && strchr(accept, *d) )
	{
		d++; // check the next char		
	} 
	return d-s;
}


/**
 *  @brief Count the number of contiguous characters at the beginning of a string not in the reject set
 *
 *  @param s Pointer to first byte of string
 *  @param reject String containing the set of characters to reject
 *  @return Number of initial characters not in set
 */
size_t strcspn(const char *s, const char *reject)
{
	const char *p = strpbrk(s, reject);
	
	if( p )
		return p-s;
	else
		return strlen(s);
}


/**
 *  @brief Divide a sting into tokens; re-entrant version
 *
 *  @param str Pointer to string to be scanned or NULL to continue scan.
 *  @param delim String containing the set of characters
 *  @param saveptr Algorithm state variable - maintain across a scan operation
 *  @return Found token or NULL if none.
 * 
 * Note: declare saveptr as char *; no initialisation required; pass in &saveptr.
 * Call repeatedly. Pass in the string to parse on first call then NULL on
 * successive calls to continue parsing the same string. NULL is returned 
 * when there are no remainin tokens.
 */
char *strtok_r(char *str, const char *delim, char **saveptr)
{
	if( str )
		*saveptr = str; // startup
	else if( !*saveptr )
		return NULL;   // shutdown
	
	char *d = strpbrk(*saveptr, delim);
	
	if( d )
	{
		*d = 0; // NULL-terminate
		
		do 
		{
			d++; // check the next char		
			if( *d==0 )
			{
				d = NULL;
				break;
			}
		} while( strchr(delim, *d) );
	}
	
	str = *saveptr;
	*saveptr = d;		
	return str;
}


/**
 *  @brief Divide a sting into tokens; unsafe version
 *
 *  @param str Pointer to string to be scanned or NULL to continue scan.
 *  @param delim String containing the set of characters
 *  @return Found token or NULL if none.
 * 
 * Note: Not thread- or coroutine-safe. Cannot nest parsing loops.
 */
char *strtok(char *str, const char *delim)
{
	static char *saveptr;
	return strtok_r(str, delim, saveptr);
}


/**
 *  @brief Find a string within another
 *
 *  @param haystack Pointer to string to be searched.
 *  @param needle Pointer to sub-string to search for
 *  @return Start of found substring or NULL if not found.
 * 
 * Note: Not thread- or coroutine-safe. Cannot nest parsing loops.
 */
char *strstr(const char *haystack, const char *needle)
{
	int i;
	int ofs = strlen(needle);
	if( ofs==0 )
		return haystack; // 0-length substring is found immediately (empty AND-rule == true)
	if( strlen(haystack) < ofs )
		return NULL;
	while( *(haystack+ofs-1) )
	{
		if( strncmp(haystack, needle, ofs) == 0 )
			return haystack;
		haystack++;
	}
	return NULL;	
}


/**
 *  @brief Copy memory
 *
 *  @param dest Pointer to destination string buffer
 *  @param src Pointer to source string buffer
 *  @return Pointer to destination string buffer
 */
char *memcpy(char *dest, const char *src, size_t n)
{
	char *dp = dest;
    int i;
	for( i=0; i<n; i++ )     
		*dp++ = *src++;
	return dest;
}


/**
 *  @brief Move memory (src and dest buffers may overlap)
 *
 *  @param dest Pointer to destination string buffer
 *  @param src Pointer to source string buffer
 *  @return Pointer to destination string buffer
 */
char *memmove(char *dest, const char *src, size_t n)
{
	if( dest < src )
		return memcpy(dest, src, n);
	
	char *dp = dest+n-1;
	src = src+n-1;
    int i;
	for( i=0; i<n; i++ )     
		*dp-- = *src--;	
	
	return dest;
}


/**
 *  @brief Fill a block of memory with a single character
 *
 *  @param s Pointer to destination memory block
 *  @param c Character to write
 *  @param n Size of destination memory block
 *  @return Pointer to destination memory block
 */
char *memset(char *s, int c, size_t n)
{
	int i;
	for(i=0; i<n; i++)
		*s++ = c;
	return s;
}


/**
 *  @brief Search for a character in memory
 *
 *  @param s Pointer to first byte of memory area
 *  @param c Byte value to search for
 *  @param n Size of area
 *  @return Pointer to found character or NULL if not found
 */
char *memchr(const char *s, int c, size_t n)
{
	int i;
	for( i=0; i<n; i++ )
	{
		if( *s==c )
			return s;
		s++;
	}
	return NULL;
}


/**
 *  @brief Compare memory areas
 *
 *  @param s1 Pointer to first area
 *  @param s2 Pointer to second area
 *  @param n Size of areas
 *  @return Comparison value: negative when s1<s2, zero when s1==s2 and positive when s1>s2
 */
int memcmp(const char *s1, const char *s2, size_t n)
{
	int i;
	for( i=0; i<n; i++ )
	{
		if( *s1 != *s2 ) 
			return *s1 - *s2;
		s1++;
		s2++;
	}
	return 0;
}

#endif
