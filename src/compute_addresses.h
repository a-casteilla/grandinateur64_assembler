#ifndef COMPUTE_ADDRESSES_H

#define COMPUTE_ADDRESSES_H

#include "common.h"

/* Purpose: This function compute the address of each line
 * Return:  error code (0 when everything is fine)
 * Modified input: lines
 *
 * lines: a pointer to the array of lines of the input. The pointer itself
 *        points to the first line of the input.
 */
int compute_addresses (struct line * lines) ;

#endif
