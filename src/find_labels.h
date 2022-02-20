#ifndef FIND_LABELS_H

#define FIND_LABELS_H

#include "common.h"

/* Purpose: each line is read to know if there is a label.
 *          If a label is found, then the label is stored in a table.
 *          The address and the scope where the label is valid is stored too
 * Return:  a pointer to the symbol table. NULL can only be returned if the
 *          program runs out of memory.
 *
 * lines: the lines of the input file, where the label should be searched
 */
struct symbol * find_labels (struct line * lines) ;

#endif
