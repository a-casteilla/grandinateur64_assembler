
/* align the given address on a power of two. 
 * This functions supposes that boundary is a power of two 
 * If not, this function has an undefined behavior
 * This function returns the next address that is aligned or the same address
 * if it's already aligned */
uint64_t align (uint64_t address, uint64_t boundary) {
    if (address & (boundary - 1)) {
        return ((address + boundary) & ~(boundary-1));
    } else {
        return address;
    }
}

/* align the given address on a power of two. 
 * This functions supposes that boundary is a power of two 
 * If not, this function has an undefined behavior
 * This function returns the amount of byte to subtract to each addresses since
 * the following align directive
 * Can be use to check if the code is aligned */
uint64_t align_backward (uint64_t address, uint64_t boundary) {
    return (address & (boundary-1));
}

/* Returns true if nb is a power of two */
bool is_a_power_of_two (uint64_t nb) {
    int number_of_one = 0;
    for (uint64_t mask = 0x1; mask; mask <<= 1)
        if (mask & nb)
            number_of_one++;
    return (number_of_one == 1);
}
    
