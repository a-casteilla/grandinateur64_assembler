#ifndef IMPORT_SYMBOLS_H

#define IMPORT_SYMBOLS_H

#include "common.h"

/* Purpose: This function imports symbols from a file
 * Return:  a pointer to the imported symbols, or NULL if an error occured
 * 
 * filename: the name of the file to import
 * offset: the offset added to the labels
 * scope: the scope where the directive is declared
 */
struct symbol * import_symbols (char * filename, uint64_t offset,
        struct scope * scope) ;

#endif
