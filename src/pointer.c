/**
 * \file pointer.c
 * \brief Functions made to manipulate "strings" of pointers NULL terminated
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 22th may 2022
 *
 */

#include <stdbool.h>
#include <stddef.h>
#include "pointer.h"

/* Didn't find something like that in the glibc btw */
/* Well, actually just for strings */
/**
 * \brief Tell if a pointer is in a list of pointer
 * \return The position of the pointer in the list as a pointer NULL if nothing was found
 *
 * \param test the pointer to test if it is in the list.
 * \param list the list of pointer
 * \param pointercount the size of the list
 */
void *
mempointer
(void * list,
 const void * test,
 size_t pointercount)
{

    size_t i;           /* Size of the array of pointers */
    bool match = false; /* Becomes true, when the corresponding pointer is
                           found */

    /* Loops until a match or the end of the list */
    for (i = 0; (i < pointercount) && (!match); i++) {
        if (*((const void **)list + i) == test) {
            match = true;
        }
    }
    i--;

    /* Returns the position of the match, or NULL */
    /* Use the ternary operator, to keep only one return */
    return match ? (const void **)list + i : NULL;
}

/**
 * \brief Tells the size of a string of pointers NULL terminated
 * \return The number of pointer in the string excluding the terminator
 *
 * \param list The string of pointers
 */
size_t
pointerlen (void * list)
{
    size_t len = 0;
    
    for (const void ** pos = list; *pos != NULL; pos++) {
        len++;
    }

    return len;
}
