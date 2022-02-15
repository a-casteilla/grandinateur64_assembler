#include <stdio.h>
#include <stdlib.h>
#include "align.h"

int main () {
    uint64_t address, boundary;
    while (!feof(stdin)) {
        scanf("%lx %lu", &address, &boundary);
        if (!feof(stdin)) {
            if (is_a_power_of_two(boundary)) {
                printf("%lx %lx\n", align_backward(address, boundary), align(address, boundary));
            } else {
                printf("%lu is not a power of two\n", boundary);
            }
        }
    }
    exit(EXIT_SUCCESS);
}
