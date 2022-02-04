#ifndef FIND_MNEMO_H

#define FIND_MNEMO_H

#include <string.h>
#include "common.h"

/* Purpose: This function associates the mnemonic (or directive) of a line with
 *          its mnemonic number
 * Return:  error code (0 when everything is fine)
 * Modified input: current_line
 *
 * current_line: a pointer to the last fetched line (the line where we have to
 *               find the mnemo)
 */
int find_mnemo (struct line * current_line) ;

#endif
