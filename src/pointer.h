#ifndef POINTER_H

#define POINTER_H

#include <stdint.h>

/* Purpose: Tell if a pointer is in a list of pointer
 * Return:  The position of the pointer in the list as a pointer
 *          NULL if nothing was found
 *
 * test: the pointer to test if it is in the list.
 * list: the list of pointer
 * pointercount: the size of the list
 */
const void ** mempointer (const void ** list, const void * test, size_t pointercount) ;

/* Purpose: Tells the size of a string of pointers NULL terminated
 * Return:  The number of pointer in the string excluding the terminator
 *
 * list: The string of pointers
 */
size_t pointerlen (const void ** list) ;

#endif
