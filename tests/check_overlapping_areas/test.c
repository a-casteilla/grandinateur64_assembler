#include <stdio.h>
#include "parse_line.h"
#include "find_mnemo.h"
#include "compute_size.h"
#include "compute_addresses.h"

/* This test suppose that the following functions work : 
 *     parse_line
 *     find_mnemo
 *     convert_literal
 *     compute_size
 *     convert_str_num
 *     compute_addresses
 */
int main () {
    unsigned int number = 1;
    struct line * lines = malloc(10*BUFSIZ);
    struct line * current_line = lines;
    while (!feof(stdin)) {
        current_line->text = malloc(BUFSIZ);
        current_line->number = number;
        fgets(current_line->text, BUFSIZ, stdin);
        if (!feof(stdin)) {
            parse_line(current_line);
            find_mnemo(current_line);
            compute_size(current_line);
        } else {
            current_line->number = 0;
        }
        current_line++;
        number++;
    }
    compute_addresses(lines);
    check_overlapping_areas(lines);
    
    exit(EXIT_SUCCESS);
}
