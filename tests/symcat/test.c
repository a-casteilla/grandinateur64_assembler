#include "sym.h"
#include "import_symbols.h"

/* Suppose that the following function works:
 * import_symbols
 */
int
main (int     argc,
      char ** argv)
{
  struct symbol * sym_src = NULL;
  struct symbol * sym_dest = NULL;
  struct scope * scopes = NULL;
  if (argc < 3) {
    exit(EXIT_FAILURE);
  }
  char * sym_file_src = argv[2];
  char * sym_file_dest = argv[1];
  scopes = malloc(sizeof(struct scope));
  scopes->level = 0;
  sym_src = import_symbols(sym_file_src, 0x10000000, scopes);
  sym_dest = import_symbols(sym_file_dest, 0x10000000, scopes);

  if (sym_src == NULL || sym_dest == NULL) {
    exit(EXIT_FAILURE);
  }

  /*
     for (struct symbol * sym = sym_dest; sym->name; sym++) {
     printf("Symbol %s has the value $%.16lx\n", sym->name, sym->value);
     }

     for (struct symbol * sym = sym_src; sym->name; sym++) {
     printf("Symbol %s has the value $%.16lx\n", sym->name, sym->value);
     }
     */

  sym_dest = symcat(sym_dest, sym_src);

  for (struct symbol * sym = sym_dest; sym->name; sym++) {
    printf("Symbol %s has the value $%.16lx\n", sym->name, sym->value);
  }

  exit(EXIT_SUCCESS);
}
