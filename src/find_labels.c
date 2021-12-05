
/* This function finds the labels and store them in a table. The address and
 * the scope were the label is valid is stored as well */
/* Returns a pointer to the label table */
struct symbol * find_labels (struct line * lines) {
    size_t symbols_size = BUFSIZ;
    struct symbol * symbols = malloc(symbols_size);
    unsigned int nb_of_symbols = 0;
    for (struct line * l = lines; l->number; l++) {
        if (l->label) {
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
            if (nb_of_symbols > symbols_size / sizeof(struct symbol)) {
                symbols_size += BUFSIZ;
                symbols = realloc(symbols, symbols_size);
            }
        }
    }
    /* To mark the end of the symbols */
    (symbols+nb_of_symbols)->name = NULL;
    return symbols;
}
