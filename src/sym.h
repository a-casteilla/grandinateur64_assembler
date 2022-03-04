#ifndef SYMCAT_H

#define SYMCAT_H

#include "common.h"

/* Purpose: concatenate symbol tables
 * Return: the src table concatenated to the end of the dest table
 *
 * dest: the destination table
 * src: the source symbol table
 *
 * Note: dest may be moved
 */
struct symbol * symcat (struct symbol * dest, const struct symbol * src) ;

/* Purpose: get the length of a symbol table excluding the terminating symbol
 * Return:  the length of the table in number of elements
 *
 * sym: the input symbol table
 */
size_t symlen (const struct symbol * sym) ;

/* Purpose: convert a symbol back to its numerical value
 * Return:  boolean (true if a value has been found in the current scope)
 * Modified input: out
 *
 * out: a pointer to the output number
 * in: a string that contains the symbol's name
 * scope: a pointer to the scope where the conversion is
 * sym: the symbol table
 */
bool symtonum (uint64_t * out, const char * in, const struct scope * scope,
        const struct symbol * sym) ;

#endif
