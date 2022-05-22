/**
 * \file common.h
 * \brief Definitions of types and macro used in a lot of functions
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 19th april 2022
 *
 */

#ifndef COMMON_H

#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * \def display_error(t, l)
 * \brief The way to display errors in the entire assembler
 * \param t The textual error
 * \param l The line where the error has occurred
 */
#define display_error(t, l) \
    fprintf(stderr, t); \
    fprintf(stderr, " at line %u :\n", (l)->number); \
    fprintf(stderr, "%s\n", (l)->text);

/**
 * \def safe_free(p)
 * \brief A macro made to avoid freeing 2 times the same pointer.
 * \param p The input pointer
 */
#define safe_free(p) \
    if (p) { \
        free(p); \
        (p) = NULL; \
    }


/**
 * \struct line
 * \brief The line fetched in the input file and the processing info associated
 *
 * A line is the textual line from the input file, but also all information
 * associated to it like its number, the location and the binary code
 * generated. Processing information like the parsing information is also
 * included.
 * The terminating line (after the last line fetched) is the line with number=0
 *
 */
struct line {
    unsigned int number;    /*!< The line number */
    char * text;            /*!< The original line */
    void * alloc_space;     /*!< Pointer used only for malloc */
    char * label;           /*!< The label (if any) */
    char * mnemo;           /*!< The mnemonic of the line (if any)*/
    char ** args;           /*!< The arguments of the line (if any). The terminating argument is a NULL pointer */
    char * comm;            /*!< The comments */
    void * bin;             /*!< The binary output */
    size_t binsiz;          /*!< The size of the binary output */
    uint64_t address;       /*!< The address where it belongs in memory */
    unsigned int prefix_nb; /*!< The mnemonic prefix number */
    unsigned int mnemo_nb;  /*!< The mnemonic number */
    const struct scope * scope;   /*!< The scope that contains the line */
};

/**
 * \struct symbol
 * \brief A symbol is either a label or a constant
 * 
 * A symbol is a name for a value or for a line. A symbol is associated with a
 * scope of definition and with a value (this value is an address if it's a
 * label).
 * The terminating symbol is a symbol with name=NULL
 */
struct symbol {
    char * name;                /*!< The name of the symbol */
    const struct scope * scope; /*!< The scope where the symbol is defined */
    uint64_t value;             /*!< The value or the label associated */
    bool is_label;              /*!< Used by the 'EXPORT' directive */
};

/**
 * \struct scope
 * \brief A scope delimits where a symbol is defined.
 *
 * A scope is a block of contiguous lines delimited by '{' and '}' and affects
 * where a symbol is visible.
 * The terminating scope is the root scope and has a level of 0
 */
struct scope {
    const struct line * first_line; /*!< First line of the scope */
    const struct line * last_line;  /*!< Last line of the scope */
    unsigned int level; /*!< Level of the scope : a scope with the level n is nested in the scope with the level (n-1) */
};

#endif // COMMON_H
