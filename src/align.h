/**
 * \file align.h
 * \brief API for the align functions
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 19th april 2022
 *
 * The function here are used to align addresses forward, backward and test if
 * an address is aligned.
 *
 */
#include <stdint.h>
#include <stdbool.h>

#ifndef ALIGN_H

#define ALIGN_H

uint64_t align (uint64_t address, uint64_t boundary) ;
uint64_t align_backward (uint64_t address, uint64_t boundary) ;
bool is_a_power_of_two (uint64_t nb) ;

#endif // ALIGN_H
