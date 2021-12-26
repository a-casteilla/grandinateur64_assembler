#ifndef ALIGN_H

#define ALIGN_H

/* align the given address on a power of two. 
 * This functions supposes that boundary is a power of two 
 * If not, this function has an undefined behavior
 * This function returns the next address that is aligned or the same address
 * if it's already aligned */
uint64_t align (uint64_t address, uint64_t boundary) ;

/* align the given address on a power of two. 
 * This functions supposes that boundary is a power of two 
 * If not, this function has an undefined behavior
 * This function returns the amount of byte to subtract to each addresses since
 * the following align directive
 * Can be use to check if the code is aligned */
uint64_t align_backward (uint64_t address, uint64_t boundary) ;

/* Returns true if nb is a power of two */
bool is_a_power_of_two (uint64_t nb) ;

#endif // ALIGN_H
