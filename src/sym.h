#ifndef SYMCAT_H

#define SYMCAT_H

#include "common.h"

/* Purpose: concatenate symbol tables
 * Return: the concatenated tables
 *
 * sym1: the first symbol table
 * sym2: the second one
 */
struct symbol * symcat (struct symbol * sym1, struct symbol * sym2) ;

/* Purpose: get the length of a symbol table excluding the terminating symbol
 * Return:  the length of the table in number of elements
 *
 * sym: the input symbol table
 */
size_t symlen (struct symbol * sym) ;

#endif
