/**
 * \file align.c
 * \brief Useful function to align addresses forward and backward
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 19th april 2022
 *
 * The function here are used to align addresses forward, backward and test if
 * an address is aligned.
 *
 */

#include "align.h"

/**
 * \brief Aligns forward the given address on a power of two. 
 * \return The next address that is aligned or the same address if it's already aligned
 *
 * \param address can be any uint64_t number
 * \param boundary Is supposed to be a power of two. If not, this function has an undefined behavior
 */
uint64_t
align
(uint64_t address,
 uint64_t boundary)
{
    if ((address & (boundary - 1)) != 0) {
        return ((address + boundary) & ~(boundary-1));
    } else {
        return address;
    }
}

/**
 * \brief align the given address on a power of two, or check if the code is
 *          aligned.
 * \return the amount of byte to subtract to each addresses since the following align directive. Or returns 0 if the code is aligned.
 *
 * \param address Can be any uint64_t number
 * \param boundary Is supposed to be a power of two. If not, this function has an undefined behavior
 */
uint64_t
align_backward
(uint64_t address,
 uint64_t boundary)
{
    return (address & (boundary-1));
}

/**
 * \brief tell if a uint64_t is a power of two or not
 * \return true is returned if nb is a power of two
 *
 * \param nb the uint64_t that will be tested.
 */
bool
is_a_power_of_two (uint64_t nb)
{
    int number_of_one = 0;
    for (uint64_t mask = 0x1; mask; mask <<= 1) {
        if (mask & nb) {
            number_of_one++;
        }
    }
    return (number_of_one == 1);
}
