#include "align.h"

/* Purpose: align the given address on a power of two. 
 * Return:  the next address that is aligned or the same address
 *          if it's already aligned
 *
 * address:  can be any uint64_t number
 * boundary: is supposed to be a power of two.
 *           If not, this function has an undefined behavior
 */
uint64_t align (uint64_t address, uint64_t boundary) {
    if (address & (boundary - 1)) {
        return ((address + boundary) & ~(boundary-1));
    } else {
        return address;
    }
}

/* Purpose: align the given address on a power of two, or check if the code is
 *          aligned.
 * Return:  the amount of byte to subtract to each addresses since
 *          the following align directive.
 *
 * address:  can be any uint64_t number
 * boundary: is supposed to be a power of two.
 *           If not, this function has an undefined behavior
 */
uint64_t align_backward (uint64_t address, uint64_t boundary) {
    return (address & (boundary-1));
}

/* Purpose: tell if a uint64_t is a power of two or not
 * Return:  true is returned if nb is a power of two
 *
 * nb: the uint64_t that will be tested.
 */
bool is_a_power_of_two (uint64_t nb) {
    int number_of_one = 0;
    for (uint64_t mask = 0x1; mask; mask <<= 1)
        if (mask & nb)
            number_of_one++;
    return (number_of_one == 1);
}
    
