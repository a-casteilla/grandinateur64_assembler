#include "mnemonic.h"
#include "def_statement.h"

/* Purpose: count the number of def directives. This way, the program knows if
 *          all statements can be defined.
 * Return:  the number of def directives
 *
 * lines: the lines of the input file, where def directives have to be counted.
 */
unsigned int count_def(const struct line * lines) {
    unsigned int nb_def = 0;
    for (const struct line * l = lines; l->number; l++) {
        if (mnemo[l->mnemo_nb].family == def_directive) {
            nb_def++;
        }
    }
    return nb_def;
}

