#include "parse_line.h"
#include "find_mnemo.h"
#include "conv_string.h"
#include "compute_size.h"
#include "common.h"

/* This test suppose that the following functions work : 
 *     parse_line
 *     find_mnemo
 *     convert_literal
 */
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
            compute_size(&a_line);
            printf("Size of line : %ld\n", a_line.binsiz);
        }
        free(a_line.args);
        free(a_line.alloc_space);
        a_line.args = NULL;
        a_line.alloc_space = NULL;
        
        number++;
    }
    exit(EXIT_SUCCESS);
}
