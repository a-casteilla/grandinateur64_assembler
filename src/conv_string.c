#include "conv_string.h"

/* Purpose: convert a string to a number. 
 * Return: the corresponding value if valid.
 *
 * input: a string
 */
/* Additionnal notes:
 * I have added this function because strtoul lacks some features in term of
 * base recognition. I want to have a '$' as a valid prefix for a hex value and
 * "%" to be a valid binary prefix.
 */
uint64_t convert_str_num (char * input) {
    if (*input == '$') {
        return strtoull(input+1, NULL, 16);
    } else if (*input == '%') {
        return strtoull(input+1, NULL, 2);
    } else {
        return strtoull(input, NULL, 0);
    }
}

/* Purpose: substitute the escape sequences to the raw characters and delete
 *          the quotes
 * Return:  void
 *
 * string_to_convert: a pointer to the string to convert
 */
void convert_literal (char ** string_to_convert) {
    /* Firstly, reach the beginning of the string */
    if (**string_to_convert != '"')
        return; /* Exits the function because it's not a string */
    (*string_to_convert)++;
    char * p1 = *string_to_convert;
    char * p2 = *string_to_convert;
    while ((*p1 != '"') && (*p1)) {
        if (*p1 == '\\') {
            switch (*(++p1)) {
                case 'n':
                    *p2 = '\n';
                    p2++;
                    p1++;
                    break;
                case 'a':
                    *p2 = '\a';
                    p2++;
                    p1++;
                    break;
                case 'e':
                    *p2 = 0x1b;
                    p2++;
                    p1++;
                    break;
                case 'f':
                    *p2 = '\f';
                    p2++;
                    p1++;
                    break;
                case 'r':
                    *p2 = '\r';
                    p2++;
                    p1++;
                    break;
                case '"':
                    *p2 = '"';
                    p2++;
                    p1++;
                    break;
                case '\\':
                    *p2 = '\\';
                    p2++;
                    p1++;
                    break;
                case 'v':
                    *p2 = '\v';
                    p2++;
                    p1++;
                    break;
                case 't':
                    *p2 = '\t';
                    p2++;
                    p1++;
                    break;
                default:
                    *p2 = *p1;
                    p1++;
                    p2++;
            }
        } else {
            *p2 = *p1;
            p1++;
            p2++;
        }
    }
    *p2 = 0;

}

