#include "parse_line.h"
#include "find_mnemo.h"
#include "compute_size.h"
#include "compute_addresses.h"
#include "scopes.h"
#include "find_labels.h"

/* This test suppose that the following functions work : 
 *     parse_line
 *     find_mnemo
 *     convert_literal
 *     compute_size
 *     convert_str_num
 *     compute_addresses
 *     find_scopes
 *     scope_of_lines
 */
int
main ()
{
  unsigned int number = 1;
  struct line * lines = malloc(10*BUFSIZ);
  struct line * current_line = lines;
  struct scope * scopes = NULL;
  struct symbol * symbols = NULL;
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
    for (struct line * l = lines; l->number; l++) {
      printf("Line no.%d\n", l->number);
      printf("%s", l->text);
      printf("Address of line : $%.16lx\n", l->address);
      printf("Is within scope with a level of %u\n", (l->scope)->level);
      printf("That starts at line no.%u\n", ((l->scope)->first_line)->number);
      printf("and ends at line no.%u\n\n", ((l->scope)->last_line)->number);
    }
    symbols = find_labels(lines);
    for (struct symbol * s = symbols; s->name; s++) {
      printf("Label \"%s\" is at address $%.16lx\n", s->name, s->value);
      printf("Is within scope with a level of %u\n", (s->scope)->level);
      printf("That starts at line no.%u\n", ((s->scope)->first_line)->number);
      printf("and ends at line no.%u\n\n", ((s->scope)->last_line)->number);
    }
  }

  exit(EXIT_SUCCESS);
}
