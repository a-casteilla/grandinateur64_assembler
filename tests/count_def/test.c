#include "parse_line.h"
#include "find_mnemo.h"
#include "conv_string.h"
#include "common.h"
#include "def_statement.h"

/* This test suppose that the following functions work : 
 *     parse_line
 *     find_mnemo
 *     convert_literal
 */
int
main ()
{
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
    } else {
      current_line->number = 1;
    }
    current_line++;
    number++;
  }
  printf("%d\n", count_def(lines));
  exit(EXIT_SUCCESS);
}
