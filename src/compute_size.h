#ifndef COMPUTE_SIZE_H

#define COMPUTE_SIZE_H

#include "common.h"

/* Purpose: This function compute the size in byte of a line of the input once
 *          assembled.
 * Return:  error code (0 when everything is fine)
 * Modified input: current_line
 *
 * current_line: a pointer to the last fetched line (the line where we have to
 *               compute the size)
 */
/* Note: a warning will still return 0. */
int compute_size (struct line * current_line) ;

#endif
