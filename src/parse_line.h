#ifndef PARSE_LINE_H
#define PARSE_LINE_H

#define remove_preceeding_whitespaces(str) \
    while(*(str) == ' ' || *(str) == '\t') (str)++ ;

#define remove_trailing_whitespaces(str) \
    for (char * j = (str) + strlen(str) - 1; *j == ' '; j--) *j = 0;

int parse_line (struct line * current_line) ;

#endif
