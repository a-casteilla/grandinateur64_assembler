#include "scopes.h"
#include "find_labels.h"

/* Purpose: each line is read to know if there is a label.
 *          If a label is found, then the label is stored in a table.
 *          The address and the scope where the label is valid is stored too
 * Return:  a pointer to the symbol table. NULL can only be returned if the
 *          program runs out of memory.
 *
 * lines: the lines of the input file, where the label should be searched
 */
struct symbol * find_labels (struct line * lines) {
    size_t symbols_size = BUFSIZ;
    struct symbol * symbols = malloc(symbols_size);
    unsigned int nb_of_symbols = 0;

    for (struct line * l = lines; l->number; l++) {
        if (l->label != NULL) {
            /* Firstly, fetch the scope of the label */
            (symbols+nb_of_symbols)->scope = l->scope;
            /* Check if the label is global */
            if (*(l->label) == '+') {
                (l->label)++;
                (symbols+nb_of_symbols)->scope
                    = root_scope((symbols+nb_of_symbols)->scope);
            }
            /* Check if the label belongs to the parent scope */
            while (*(l->label) == '&') {
                (l->label)++;
                (symbols+nb_of_symbols)->scope
                    = parent_scope((symbols+nb_of_symbols)->scope);
            }
            (symbols+nb_of_symbols)->name = l->label;
            (symbols+nb_of_symbols)->value = l->address;
            (symbols+nb_of_symbols)->is_label = true;
            nb_of_symbols++;
            /* Alloc more space if necessary */
            if ((nb_of_symbols + 1) * sizeof(struct symbol) > symbols_size) {
                symbols_size += BUFSIZ;
                symbols = realloc(symbols, symbols_size);
            }
        }
    }
    /* To mark the end of the symbols */
    (symbols+nb_of_symbols)->name = NULL;
    return symbols;
}
