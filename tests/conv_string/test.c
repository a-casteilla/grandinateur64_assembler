#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../src/conv_string.h"

/*
 * Test of the functions :
 * convert_str_num
 * convert_literal
 * 
 * On the odd lines, escape sequences are converted.
 * On the even lines, strings are converted to number.
 * (I assume the line number begins with line 1)
 */
int main () {
    char * line = (char *)malloc(BUFSIZ);
    uint64_t value;
    while (!feof(stdin)) {
        fgets(line, BUFSIZ, stdin);
        if (!feof(stdin)) {
            printf("Original: \n");
            puts(line);
            convert_literal(&line);
            printf("Converted: \n");
            puts(line);
        }
        fgets(line, BUFSIZ, stdin);
        if (!feof(stdin)) {
            printf("Original: \n");
            puts(line);
            value = convert_str_num(line);
            printf("Numeric value: \n");
            printf("%lx\n", value);
        }
    }
    exit(EXIT_SUCCESS);
}
