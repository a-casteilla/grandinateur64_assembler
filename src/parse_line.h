#ifndef PARSE_LINE_H
#define PARSE_LINE_H

#include "common.h"

#define remove_preceeding_whitespaces(str) \
    while(*(str) == ' ' || *(str) == '\t') (str)++ ;

#define remove_trailing_whitespaces(str) \
    for (char * j = (str) + strlen(str) - 1; *j == ' '; j--) *j = 0;

/* Purpose: parse a line into separated tokens
 *          split the input on spaces, then on commas
 *          detect the label of the line and the comment (if there is any)
 * Return:  error code (0 when everything is fine)
 * Modified input: current_line
 *
 * current_line: a pointer to the last fetched line
 */
int parse_line (struct line * current_line) ;

#endif
