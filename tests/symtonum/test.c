#include "parse_line.h"
#include "find_mnemo.h"
#include "compute_size.h"
#include "compute_addresses.h"
#include "scopes.h"
#include "find_labels.h"
#include "sym.h"

/* This test suppose that the following functions work : 
 *     parse_line
 *     find_mnemo
 *     convert_literal
 *     compute_size
 *     convert_str_num
 *     compute_addresses
 *     find_scopes
 *     scope_of_lines
 *     find_labels
 */
int
main (int     argc,
      char ** argv)
{
  unsigned int number = 1;
  struct line * lines = malloc(10*BUFSIZ);
  struct line * current_line = lines;
  struct scope * scopes = NULL;
  struct symbol * symbols = NULL;
  uint64_t sym_value;

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
    scope_of_lines(lines, scopes);
    symbols = find_labels(lines);
    for (struct symbol * s = symbols; s->name != NULL; s++) {
      printf("Label \"%s\" is at address $%.16lx\n", s->name, s->value);
      printf("Is within scope with a level of %u\n", (s->scope)->level);
      printf("That starts at line no.%u\n", ((s->scope)->first_line)->number);
      printf("and ends at line no.%u\n\n", ((s->scope)->last_line)->number);
    }
    for (struct line * l = lines; l->number; l++) {
      if (l->comm != NULL ? *(l->comm) == ':' : false) {
        if ((*((l->comm) + 1) != '\0') || (*((l->comm) + 1) != ' ')) {
          if (symtonum(&sym_value, (l->comm) + 1, l->scope,
                symbols)) {
            printf("At line no.%u, symbol \"%s\" has a value of $%.16lx\n"
                , l->number, (l->comm)+1, sym_value);
          } else {
            printf("At line no.%u, symbol \"%s\" is not defined\n"
                , l->number, (l->comm)+1);
          }
        }  
        /* Else: Skip the line if there is just a colon */
      }
      /* Else: Skip if no label in the comments */
    }
  }

  exit(EXIT_SUCCESS);
}
