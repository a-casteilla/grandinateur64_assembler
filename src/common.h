#ifndef COMMON_H

#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define display_error(t, l) \
    fprintf(stderr, t); \
    fprintf(stderr, " at line %u :\n", (l)->number); \
    fprintf(stderr, "%s\n", (l)->text);

#define safe_free(p) \
    if (p) { \
        free(p); \
        (p) = NULL; \
    }


struct line {
    /* The terminating line (after the last line fetched) is the line with
     * number=0 */
    unsigned int number;    /* The line number */
    char * text;            /* The original line */
    void * alloc_space;     /* Pointer used only for malloc */
    char * label;           /* The label (if any) */
    char * mnemo;           /* The mnemonic of the line (if any)*/
    char ** args;           /* The arguments of the line (if any)*/
                            /* The terminating argument is a NULL pointer */
    char * comm;            /* The comments */
    void * bin;             /* The binary output */
    size_t binsiz;          /* The size of the binary output */
    uint64_t address;       /* The address where it belongs in memory */
    unsigned int prefix_nb; /* The mnemonic prefix number */
    unsigned int mnemo_nb;  /* The mnemonic number */
    struct scope * scope;   /* The scope that contains the line */
};

/* A symbol is either a label or a constant */
struct symbol {
    /* The terminating symbol is a symbol with name=NULL */
    char * name;
    struct scope * scope;
    uint64_t value;
    bool is_label;          /* Used by the 'EXPORT' directive */
};

struct scope {
    /* The terminating scope is the root scope and has a level of 0 */
    struct line * first_line; /* First line of the scope */
    struct line * last_line;  /* Last line of the scope */
    unsigned int level;       /* Level of the scope : a scope with the level n
                                 is nested in the scope with the level (n-1) */
};

#endif // COMMON_H
