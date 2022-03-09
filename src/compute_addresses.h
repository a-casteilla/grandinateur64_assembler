#ifndef COMPUTE_ADDRESSES_H

#define COMPUTE_ADDRESSES_H

#include "common.h"

enum ca_error {
    ca_error_no_error = 0,
    ca_error_undef_address,
    ca_error_no_pc,
    ca_error_bad_nb,
    ca_error_align
};

/* Purpose: This function compute the address of each line
 * Return:  error code (0 when everything is fine)
 * Modified input: lines
 *
 * lines: a pointer to the array of lines of the input. The pointer itself
 *        points to the first line of the input.
 */
enum ca_error compute_addresses (struct line * lines) ;

#endif
