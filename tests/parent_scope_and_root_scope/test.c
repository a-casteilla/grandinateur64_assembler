#include "parse_line.h"
#include "find_mnemo.h"
#include "compute_size.h"
#include "compute_addresses.h"
#include "scopes.h"

/* This test suppose that the following functions work : 
 *     parse_line
 *     find_mnemo
 *     convert_literal
 *     compute_size
 *     convert_str_num
 *     compute_addresses
 *     find_scopes
 */
int main () {
    unsigned int number = 1;
    struct line * lines = malloc(10*BUFSIZ);
    struct line * current_line = lines;
    struct scope * scopes = NULL;
    struct scope * s = NULL;
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
    scopes = find_scopes(lines);
    
    if (scopes) {
        s = scopes;
        do {
            printf("Scope of level %u\n", s->level);
            printf("Starts at line no.%u\n", (s->first_line)->number);
            printf("Ends at line no.%u\n", (s->last_line)->number);
            printf("Parent starts at line no.%u\n",
                    (parent_scope(s)->first_line)->number);
            printf("Parent ends at line no.%u\n",
                    (parent_scope(s)->last_line)->number);
            printf("Root starts at line no.%u\n",
                    (root_scope(s)->first_line)->number);
            printf("Root ends at line no.%u\n\n",
                    (root_scope(s)->last_line)->number);
        } while ((s++)->level) ;
    }

    exit(EXIT_SUCCESS);
}
