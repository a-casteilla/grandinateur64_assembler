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

#endif
