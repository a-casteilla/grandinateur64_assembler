#ifndef CHECK_OVERLAPPING_AREAS_H

#define CHECK_OVERLAPPING_AREAS_H

#include "common.h"

/* Purpose: this function verifies that there aren't two areas of code with
 *          overlapping addresses.
 *          For example this function will detect if there is an area that
 *          goes from $1234 to $1300 and another that goes from $1280 and
 *          $135c. Here, the common area is from $1280 and $1300.
 * Return:  the number of overlapping areas detected (0 means everything is
 *          fine)
 *
 * lines: a pointer to the array of lines of the input. The pointer itself
 *        points to the first line of the input.
 */
int check_overlapping_areas (struct line * lines) ;

#endif
