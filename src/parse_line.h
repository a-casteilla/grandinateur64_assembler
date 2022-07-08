/**
 * \file parse_line.h
 * \brief API for the function made to parse the input line in separated tokens
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 22th may 2022
 *
 */

#ifndef PARSE_LINE_H
#define PARSE_LINE_H

#include <string.h>
#include "common.h"

/**
 * \def remove_preceeding_whitespaces(str)
 * \brief Macro to made to remove spaces and tabs at the beginning of a line
 */
#define remove_preceeding_whitespaces(str) \
  while(*(str) == ' ' || *(str) == '\t') (str)++ ;

/**
 * \def remove_trailing_whitespaces(str)
 * \brief Macro to made to remove spaces and tabs at the end of a line
 */
#define remove_trailing_whitespaces(str) \
  for (char * j = (str) + strlen(str) - 1; *j == ' ' || *j == '\t'; j--) *j = 0;

int parse_line (struct line * current_line) ;

#endif
