#include "import_symbols.h"

int
main ()
{
  struct symbol * sym_table = NULL;
  struct scope * scopes = NULL;
  scopes = malloc(sizeof(struct scope));
  scopes->level = 0;
  sym_table = import_symbols("input.sym", 0x10000000, scopes);

  if (!sym_table) {
    exit(EXIT_FAILURE);
  }

  for (struct symbol * sym = sym_table; sym->name; sym++) {
    printf("Symbol %s has the value $%.16lx\n", sym->name, sym->value);
  }

  exit(EXIT_SUCCESS);
}
