/**
 * \file import_symbols.h
 * \brief API for the function made to import symbols
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 14th may 2022
 *
 */

#ifndef IMPORT_SYMBOLS_H

#define IMPORT_SYMBOLS_H

#include "common.h"

struct symbol * import_symbols (const char * filename, uint64_t offset,
        const struct scope * scope) ;

#endif
