/**
 * \file def_statement.c
 * \brief Functions related to the "DEF" directive
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 19th april 2022
 *
 */

#include "mnemonic.h"
#include "def_statement.h"

/**
 * \brief Counts the number of def directives in the file.
 * \return The number of def directives
 *
 * \param lines the lines of the input file, where def directives have to be counted.
 */
unsigned int
count_def(const struct line * lines)
{
    unsigned int nb_def = 0;
    for (const struct line * l = lines; l->number; l++) {
        if (mnemo[l->mnemo_nb].family == def_directive) {
            nb_def++;
        }
    }
    return nb_def;
}

