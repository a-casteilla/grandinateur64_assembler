/**
 * \file sym.h
 * \brief API for the functions made to process symbols inside an input file
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 22th may 2022
 *
 */

#ifndef SYMCAT_H

#define SYMCAT_H

#include "common.h"

struct symbol * symcat (struct symbol * dest, const struct symbol * src) ;
size_t symlen (const struct symbol * sym) ;
bool symtonum (uint64_t * out, const char * in, const struct scope * scope,
        const struct symbol * sym) ;

#endif
