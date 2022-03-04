#include <stdlib.h>
#include "check_overlapping_areas.h"

/* Area of code : used to detect intersecting regions */
struct area {
    /* There isn't a terminating area : the number of area has to be kept */
    const struct line * first_line; /* first line in the area */
    const struct line * last_line;  /* last one */
    uint64_t first_address;   /* first address in the area */
    uint64_t last_address;    /* last one */
};

/* Purpose: this function is used by the function from the standart library qsort
 * Return:  An integer which indicate if the address of the first area is
 *          greater than the last address of the second area.
 *
 * area1: a pointer to the first area to compare
 * area2: a pointer to the sercond area to compare
 */
static int compare_first_address_of_area (const void * area1, const void * area2) {
    return (int)(((struct area *)area1)->first_address
            - ((struct area *)area2)->last_address);
}

/* Purpose: this function verifies that there aren't two areas of code with
 *          overlapping addresses.
 *          For example this function will detect if there is an area that
 *          goes from $1234 to $1300 and another that goes from $1280 and
 *          $135c. Here, the common area is from $1280 and $1300.
 * Return:  the number of overlapping areas detected (0 means everything is
 *          fine)
 *
 * lines: a pointer to the array of lines of the input. The pointer itself
 *        points to the first line of the input.
 */
int check_overlapping_areas (const struct line * lines) {
    size_t alloc_space_areas = BUFSIZ;
    size_t alloc_space_overareas = BUFSIZ;

    /* areas where code is assembled */
    struct area * areas = malloc(alloc_space_areas);
    /* areas where code is overlapping */
    struct area * overareas = malloc(alloc_space_overareas);

    unsigned int areas_nb = 0;     /* number of area of code */
    unsigned int overareas_nb = 0; /* number of intersections of area of code */

    for (const struct line * l = lines; l->number; l++) {
        if (l->binsiz != 0) {
            if (areas_nb == 0) {
                (areas + areas_nb)->first_line     = l;
                (areas + areas_nb)->last_line      = l;
                (areas + areas_nb)->first_address  = l->address;
                (areas + areas_nb++)->last_address = l->address + l->binsiz - 1;
            } else {
                /* Check if the address of the line is after the last area */
                if ((areas + areas_nb - 1)->last_address + 1 == l->address) {
                    (areas + areas_nb - 1)->last_line    = l;
                    (areas + areas_nb - 1)->last_address = l->address + l->binsiz - 1;
                } else {
                    /* Create a new area */
                    if (areas_nb >= alloc_space_areas / sizeof(* areas)) {
                        alloc_space_areas += BUFSIZ;
                        areas = realloc(areas, alloc_space_areas);
                    }
                    (areas + areas_nb)->first_line     = l;
                    (areas + areas_nb)->last_line      = l;
                    (areas + areas_nb)->first_address  = l->address;
                    (areas + areas_nb++)->last_address = l->address + l->binsiz - 1;
                }
            }
        }
    }
#ifdef test
    for (unsigned int a = 0; a < areas_nb; a++) {
        printf("Area no.%d : \n", a + 1);
        printf("first line : %d \n", ((areas + a)->first_line)->number);
        printf("last line  : %d \n", ((areas + a)->last_line)->number);
        printf("first address : $ %.16lx \n", (areas + a)->first_address);
        printf("last address  : $ %.16lx \n", (areas + a)->last_address);
    }
#endif

    qsort(areas, areas_nb, sizeof(struct area), compare_first_address_of_area);
    
#ifdef test
    for (unsigned int a = 0; a < areas_nb; a++) {
        printf("Area no.%d : \n", a + 1);
        printf("first line : %d \n", ((areas + a)->first_line)->number);
        printf("last line  : %d \n", ((areas + a)->last_line)->number);
        printf("first address : $ %.16lx \n", (areas + a)->first_address);
        printf("last address  : $ %.16lx \n", (areas + a)->last_address);
    }
#endif

    for (unsigned int a = 0; a < areas_nb - 1; a++) {
#ifdef test
        printf("Checking area %u with area %u\n", a + 1, a + 2);
#endif
        if ((areas + a)->last_address >= (areas + a + 1)->first_address) {
            /* Create a new area */
            if (overareas_nb + 1 >= alloc_space_overareas / sizeof(* overareas)) {
                alloc_space_overareas += BUFSIZ;
                overareas = realloc(overareas, alloc_space_overareas);
            }

            /* Initialize the pointers to NULL */
            (overareas + overareas_nb)->first_line = NULL;
            (overareas + overareas_nb)->last_line = NULL;

            /* Searches the first line of the first region that has an address
             * less than the first address of the second region */
            for (const struct line * l = (areas + a)->last_line;
                    (l >= (areas + a)->first_line)
                    &&
                    ((areas + a + 1)->first_address < (l->address + l->binsiz - 1));
                    l--) {
                (overareas + overareas_nb)->first_line = l;
            }
            if ((overareas + overareas_nb)->first_line == NULL) {
                 (overareas + overareas_nb)->first_line = (areas+a)->first_line;
            }
            /* Searches the last line of the first region that has an address
             * greater than the last address of the second region */
            (overareas + overareas_nb)->last_line = (areas + a)->last_line;
            for (const struct line * l = (areas + a)->last_line;
                    (l >= (areas + a)->first_line)
                    &&
                    ((areas + a + 1)->last_address < l->address);
                    l--) {
                (overareas + overareas_nb)->last_line = l;
            }
            (overareas + overareas_nb)->first_address  = (areas + a + 1)->first_address;
            (overareas + overareas_nb++)->last_address = (areas + a)->last_address;
            /* Searches the last line of the second region that has an address
             * greater than the last address of the first region */
            for (const struct line * l = (areas + a + 1)->first_line;
                    (l <= (areas + a + 1)->last_line)
                    &&
                    ((areas + a)->last_address >= l->address);
                    l++) {
                (overareas + overareas_nb)->last_line = l;
            }
            (overareas + overareas_nb)->first_line     = (areas + a + 1)->first_line;
            (overareas + overareas_nb)->first_address  = (areas + a)->first_address;
            (overareas + overareas_nb++)->last_address = (areas + a)->last_address;
        }
    }
#ifdef test
    printf("Done\n");
#endif

    if (overareas_nb != 0) {
        for (unsigned int i = 0; i < overareas_nb; i += 2) {
            fprintf(stderr, "Lines from %d to %d ",
                    ((overareas + i)->first_line)->number,
                    ((overareas + i)->last_line)->number);
            fprintf(stderr, "and lines from %d to %d ",
                    ((overareas + i + 1)->first_line)->number,
                    ((overareas + i + 1)->last_line)->number);
            fprintf(stderr, "are resolved to the same address range ");
            fprintf(stderr, "(from $%.16lx to $%.16lx)\n",
                    (overareas + i)->first_address, (overareas + i)->last_address);
        }
    }

    safe_free(overareas);
    safe_free(areas);
    return overareas_nb;
}
