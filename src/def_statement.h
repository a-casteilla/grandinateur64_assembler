/**
 * \file def_statement.h
 * \brief API for the functions related to the "DEF" directive
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 19th april 2022
 *
 */

#ifndef DEF_STATEMENT_H

#define DEF_STATEMENT_H

#include "common.h"

unsigned int count_def(const struct line * lines) ;
struct symbol * eval_def_once (struct line * lines, struct symbol * symbols) ;
struct symbol * eval_all_def (struct line * lines,
    struct symbol * known_symbols);

#endif
