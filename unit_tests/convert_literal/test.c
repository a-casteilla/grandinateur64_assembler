#include <stdio.h>
#include <stdlib.h>
#include "../../src/conv_string.h"

int main () {
    char * line = (char *)malloc(BUFSIZ);
    while (!feof(stdin)) {
        fgets(line, BUFSIZ, stdin);
        if (!feof(stdin)) {
            printf("\"%s\"\n", line);
            convert_literal(&line);
            printf("\"%s\"\n", line);
        }
    }
    exit(EXIT_SUCCESS);
}
