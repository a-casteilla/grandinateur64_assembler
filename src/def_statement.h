#ifndef DEF_STATEMENT_H

#define DEF_STATEMENT_H

#include "common.h"

/* Purpose: count the number of def directives. This way, the program knows if
 *          all statements can be defined.
 * Return:  the number of def directives
 *
 * lines: the lines of the input file, where def directives have to be counted.
 */
unsigned int count_def(const struct line * lines) ;

#endif
