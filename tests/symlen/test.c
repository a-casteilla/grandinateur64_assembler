#include "sym.h"
#include "import_symbols.h"

/* Suppose that the following function works:
 * import_symbols
 */
int main (int argc, char ** argv) {
    struct symbol * sym_table = NULL;
    struct scope * scopes = NULL;
    if (argc < 2) {
        exit(EXIT_FAILURE);
    }
    char * sym_file = argv[1];
    scopes = malloc(sizeof(struct scope));
    scopes->level = 0;
    sym_table = import_symbols(sym_file, 0x10000000, scopes);

    if (!sym_table) {
        exit(EXIT_FAILURE);
    }

    printf("%ld\n", symlen(sym_table));

    exit(EXIT_SUCCESS);
}
