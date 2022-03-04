#include <stdbool.h>
#include <stddef.h>
#include "pointer.h"

/* Didn't find something like that in the glibc btw */
/* Well, actually just for strings */
/* Purpose: Tell if a pointer is in a list of pointer
 * Return:  The position of the pointer in the list as a pointer
 *          NULL if nothing was found
 *
 * test: the pointer to test if it is in the list.
 * list: the list of pointer
 * pointercount: the size of the list
 */
const void ** mempointer (const void ** list, const void * test, size_t pointercount) {

    size_t i;           /* Size of the array of pointers */
    bool match = false; /* Becomes true, when the corresponding pointer is
                           found */

    /* Loops until a match or the end of the list */
    for (i = 0; (i < pointercount) && (!match); i++) {
        if (*(list + i) == test) {
            match = true;
        }
    }
    i--;

    /* Returns the position of the match, or NULL */
    /* Use the ternary operator, to keep only one return */
    return match ? list + i : NULL;
}

/* Purpose: Tells the size of a string of pointers NULL terminated
 * Return:  The number of pointer in the string excluding the terminator
 *
 * list: The string of pointers
 */
size_t pointerlen (const void ** list) {
    size_t len = 0;
    
    for (const void ** pos = list; *pos != NULL; pos++) {
        len++;
    }

    return len;
}
