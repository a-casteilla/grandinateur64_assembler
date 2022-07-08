#include "import_symbols.h"
#include "rpn.h"

int
main ()
{
  struct symbol * sym_table = NULL;
  struct scope * scopes = NULL;
  struct line fake_line[2] = 
  {
    {
      .number = 1,
      .text = "",
      .alloc_space = NULL,
      .label = NULL,
      .mnemo = NULL,
      .args = NULL,
      .comm = NULL,
      .bin = NULL,
      .binsiz = 0,
      .address = 0,
    },
    {
      .number = 0,
      .text = "",
      .alloc_space = NULL,
      .label = NULL,
      .mnemo = NULL,
      .args = NULL,
      .comm = NULL,
      .bin = NULL,
      .binsiz = 0,
      .address = 0,
    }
  };

  char exp[BUFSIZ];
  uint64_t value;

  scopes = malloc(sizeof(struct scope));
  scopes->level = 0;
  scopes->first_line = fake_line;
  scopes->last_line = fake_line + 1;
  sym_table = import_symbols("input.sym", 0x10000000, scopes);

  if (!sym_table) {
    exit(EXIT_FAILURE);
  }

  while (!feof(stdin)) {
    fgets(exp, BUFSIZ, stdin);
    if (!feof(stdin)) {
      for (char * s = exp; *(s - 1) != '\0' || s == exp ; s++) {
        if (*s == '\n') {
          *s = '\0';
        }
      }

      printf("%s\n", exp);
      if (!feof(stdin)) {
        switch (rpneval(exp, scopes, sym_table, &value)) {
          case rpn_error_no_error:
            printf("Result: %ld\n", value);
            break;
          case rpn_error_syntax_error:
            printf("Error: syntax error\n");
            break;
          case rpn_error_unknown_symbol:
            printf("Error: symbol can't be resolved\n");
            break;
          case rpn_error_stack_overflow:
            printf("Error: stack overflow\n");
            break;
          case rpn_error_stack_underflow:
            printf("Error: stack underflow\n");
            break;
          case rpn_error_warning_non_empty:
            printf("Result: %ld warning: non-empty stack\n", value);
            break;
          case rpn_error_warning_no_op:
            printf("Result: %ld warning: no operation done\n", value);
            break;
          default:
            printf("Error: unknown error\n");
            break;
        }
      }
    }
  }
  exit(EXIT_SUCCESS);
}
