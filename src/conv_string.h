#ifndef CONV_STRING_H

#define CONV_STRING_H

#include <stdint.h>
#include <stdbool.h>

/* Purpose: convert a string to a number. 
 * Return: true if an error happend.
 * Modified input: out
 *
 * input: a string
 * out: the value once converted
 */
/* Additionnal notes:
 * I have added this function because strtoul lacks some features in term of
 * base recognition. I want to have a '$' as a valid prefix for a hex value and
 * "%" to be a valid binary prefix.
 * For negative numbers, there is no need to handle them, as long as strtoull
 * handles them correctly. (It's explained in the man page section 3 of
 * strtoull)
 */
bool convert_str_num (const char * input, uint64_t * out) ;

/* Purpose: substitute the escape sequences to the raw characters and delete
 *          the quotes
 * Return:  void
 *
 * string_to_convert: a pointer to the string to convert
 */
void convert_literal (char ** string_to_convert) ;

#endif
