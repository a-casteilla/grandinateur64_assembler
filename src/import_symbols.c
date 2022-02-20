#include <string.h>
#include "import_symbols.h"
#include "scopes.h"

/* Purpose: This function imports symbols from a file
 * Return:  a pointer to the imported symbols, or NULL if an error occured
 * 
 * filename: the name of the file to import
 * offset: the offset added to the labels
 * scope: the scope where the directive is declared
 */
struct symbol * import_symbols (char * filename, uint64_t offset,
        struct scope * scope) {

    scope = root_scope(scope); /* Find the root scope because all symbols in
                                  the files belongs to the root scope */

    /* do the memory allocation */
    size_t imported_symbols_size = BUFSIZ;
    struct symbol * imported_symbols = malloc(imported_symbols_size);
    char line[BUFSIZ];

    /* Initialisation */
    unsigned int nb_of_symbols = 0;
    char * line_parsed = NULL;
    bool is_label = false;

    /* opens the file */
    FILE * import_file = fopen(filename, "r");

    if (!import_file) {
        fprintf(stderr, "Can't open file \"%s\"\n\n", filename);
        return NULL;
    }

    while (!feof(import_file)) {
        /* By default, the line being fetched contains a constant and not a
         * label */
        is_label = false;
        /* the line is being fetched */
        if (!fgets(line, BUFSIZ, import_file) && !feof(import_file)) {
            fprintf(stderr, "An error occured while reading file \"%s\"\n\n",
                    filename);
            return NULL;
        } else if (!feof(import_file)) {
            /* This is executed if the line has been fetched successfully and
             * if the file is not ended */
            line_parsed = strtok(line, " \n");
            if (line_parsed) {
                /* Get the type of the line (label / constant) */
                /* If the first letter is l then it's a label */
                if (*line_parsed == 'l') {
                    is_label = true;
                }

                line_parsed = strtok(NULL, " \n");

                if (line_parsed) {
                    /* get the offset / value */
                    /* add the numeric of the current line to the table */
                    (imported_symbols + nb_of_symbols)->value
                        = strtoull(line_parsed, NULL, 16);
                    /* add the offset if it's a label */
                    if (is_label)
                        (imported_symbols + nb_of_symbols)->value += offset;

                    line_parsed = strtok(NULL, " \n");

                    if (line_parsed) {
                        /* add the label's name to the table */
                        (imported_symbols + nb_of_symbols)->name
                            = malloc(strlen(line_parsed)+1);
                        strcpy((imported_symbols + nb_of_symbols)->name,
                                line_parsed);
                        (imported_symbols + nb_of_symbols)->scope
                            = scope; /* Reminder: scope is the root scope */
                        (imported_symbols+nb_of_symbols)->is_label = is_label;
                        nb_of_symbols++;
                        /* alloc more space if necessary */
                        if ((nb_of_symbols+1) * sizeof(struct symbol)
                                > imported_symbols_size) {
                            imported_symbols_size += BUFSIZ;
                            imported_symbols = realloc(imported_symbols,
                                    imported_symbols_size);
                        }
                    }
                    /* No else : just skip the line if there isn't more
                     * token (if the line is invalid) */
                }
                /* No else : just skip the line if there isn't more token
                 * (if the line is invalid) */
            }
            /* No else : the line is void */
        }
        /* No else : the end of file has been reached */
    }
    /* The name of the symbol = NULL : end of the symbol list */
    (imported_symbols + nb_of_symbols)->name = NULL;
    nb_of_symbols++;
    /* alloc more space if necessary */
    if ((nb_of_symbols + 1) * sizeof(struct symbol) > imported_symbols_size) {
        imported_symbols_size += BUFSIZ;
        imported_symbols = realloc(imported_symbols, imported_symbols_size);
    }

    return imported_symbols;
}

