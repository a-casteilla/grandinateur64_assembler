#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "conv_string.h"

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
            if (*(line + strlen(line) - 1) == '\n') {
                *(line + strlen(line) - 1) = '\0';
            }
            if (convert_str_num(line, &value)) {
                printf("Bad format\n");
            } else {
                printf("Numeric value: \n");
                printf("%lx\n", value);
            }
        }
    }
    exit(EXIT_SUCCESS);
}
