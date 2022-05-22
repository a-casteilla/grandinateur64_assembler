/**
 * \file conv_string.c
 * \brief Functions made to convert strings escape sequences and numeric value
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 19th april 2022
 *
 */

#include <stdlib.h>
#include <string.h>
#include "conv_string.h"

/**
 * \brief convert a string to a number. 
 * \return true if an error happend.
 *
 * \param input a string
 * \param out the value once converted
 * 
 * 
 * Additionnal notes:
 * I have added this function because strtoull lacks some features in term of
 * base recognition. I want to have a '$' as a valid prefix for a hex value and
 * "%" to be a valid binary prefix.
 * For negative numbers, there is no need to handle them, as long as strtoull
 * handles them correctly. (It's explained in the man page section 3 of
 * strtoull)
 */
bool
convert_str_num
(const char * input,
 uint64_t * out)
{
    switch (*input) {
        case '0':
            if (strspn(input+1, "01234567")
                    != strlen(input + 1)) {
                if ((*(input+1) == 'x'
                            || *(input+1) == 'X')
                        && (strspn(input+2, "0123456789abcdefABCDEF")
                            != strlen(input + 2))) {
                    return true;
                } else if (*(input+1) != 'x' && *(input+1) != 'X') {
                    return true;
                }
            }
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '+':
        case '-':
            if (strspn(input+1, "0123456789")
                    != strlen(input + 1)) {
                return true;
            }
            break;
        case '$':
            if ((strspn(input+1, "0123456789abcdefABCDEF")
                        != strlen(input + 1))) {
                return true;
            }
            break;
        case '%':
            if ((strspn(input+1, "01")
                        != strlen(input + 1))) {
                return true;
            }
            break;
        default:
            /* It's not a number */
            return true;
            break;
    }
    if (*input == '$') {
        *out = strtoull(input+1, NULL, 16);
    } else if (*input == '%') {
        *out = strtoull(input+1, NULL, 2);
    } else {
        *out = strtoull(input, NULL, 0);
    }
    return false;
}

/**
 * \brief substitute the escape sequences to the raw characters and delete the quotes
 * \return void
 *
 * \param string_to_convert a pointer to the string to convert
 *
 * This function converts a string to its final form. The escape sequences are
 * substituted to their binary form. The following escape sequences are
 * recognized: \n, \a, \b, \e, \f, \r, \", \\, \v, \t
 */
void
convert_literal (char ** string_to_convert)
{
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
                case 'b':
                    *p2 = '\b';
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
                    break;
            }
        } else {
            *p2 = *p1;
            p1++;
            p2++;
        }
    }
    *p2 = 0;

}

