/**
 * \file conv_string.h
 * \brief API for the functions made to convert strings escape sequences and numeric value
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 19th april 2022
 *
 */

#ifndef CONV_STRING_H

#define CONV_STRING_H

#include <stdint.h>
#include <stdbool.h>

bool convert_str_num (const char * input, uint64_t * out) ;
void convert_literal (char ** string_to_convert) ;

#endif
