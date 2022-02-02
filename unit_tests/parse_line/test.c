#include <stdio.h>
#include <stdlib.h>
#include "../../src/parse_line.h"
#include "../../src/common.h"

int main () {
    unsigned int number = 1;
    struct line a_line;
    a_line.text = malloc(BUFSIZ);
    while (!feof(stdin)) {
        a_line.number = number;
        fgets(a_line.text, BUFSIZ, stdin);
        if (!feof(stdin)) {
            parse_line(&a_line);
            printf("Line no.%d\n", a_line.number);
            if (a_line.label != NULL)
                printf("Label : \"%s\"\n", a_line.label);
            else
                printf("No label\n");
            if (a_line.mnemo != NULL)
                printf("Mnemonic : \"%s\"\n", a_line.mnemo);
            else
                printf("No mnemonic\n");
            if (a_line.args != NULL) {
                for (unsigned int i = 0; *(a_line.args+i) != NULL; i++) {
                    printf("Argument no.%d : \"%s\"\n", i, *(a_line.args+i));
                }
            } else {
                printf("No argument\n");
            }
            if (a_line.comm != NULL)
                printf("Comment : \"%s\"\n", a_line.comm);
            else
                printf("No comment \n");
        }
        free(a_line.args);
        free(a_line.alloc_space);
        a_line.args = NULL;
        a_line.alloc_space = NULL;
        
        number++;
    }
    exit(EXIT_SUCCESS);
}
