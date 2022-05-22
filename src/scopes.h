/**
 * \file scopes.h
 * \brief API for the functions made to process scopes inside an input file
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 22th may 2022
 *
 */

#ifndef SCOPES_H

#define SCOPES_H

#include "common.h"

struct scope * find_scopes (const struct line * lines) ;
const struct scope * parent_scope (const struct scope * child) ;
const struct scope * root_scope (const struct scope * child) ;
const struct scope * scope_of_line (const struct line * line, const struct scope * scopes) ;
void scope_of_lines (struct line * lines, const struct scope * scopes) ;

#endif
