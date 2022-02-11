#include "../../src/find_mnemo.h"
#include "../../src/parse_line.h"

/* This test suppose that parse_line works */
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
            if (a_line.mnemo != NULL)
                printf("Mnemonic : \"%s\"\n", a_line.mnemo);
            else
                printf("No mnemonic\n");
            find_mnemo(&a_line);
            printf("Prefix number : %d\n", a_line.prefix_nb);
            printf("Mnemonic number : %d\n", a_line.mnemo_nb);
        }
        free(a_line.args);
        free(a_line.alloc_space);
        a_line.args = NULL;
        a_line.alloc_space = NULL;
        
        number++;
    }
    exit(EXIT_SUCCESS);
}

