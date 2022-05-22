/**
 * \file pointer.h
 * \brief API for the functions made to manipulate "strings" of pointers NULL terminated
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 22th may 2022
 *
 */

#ifndef POINTER_H

#define POINTER_H

#include <stdint.h>

void * mempointer (void * list, const void * test, size_t pointercount) ;
size_t pointerlen (void * list) ;

#endif
