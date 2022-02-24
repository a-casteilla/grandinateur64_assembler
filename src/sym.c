#include <string.h>
#include "sym.h"

/* Purpose: concatenate symbol tables
 * Return: the src table concatenated to the end of the dest table
 *
 * dest: the destination table
 * src: the source symbol table
 *
 * Note: dest may be moved
 */
struct symbol * symcat (struct symbol * dest, const struct symbol * src) {

    size_t len_src, len_dest, len_out;

    len_src = symlen(src);
    len_dest = symlen(dest);
    len_out = len_src + len_dest;

    /* Allocate the memory for the output 
     * +1 is necessary because of the terminating null symbol */
    dest = realloc(dest, (sizeof(struct symbol) * len_out) + 1);

    /* Copy the src at the end of dest */
    memcpy(dest + len_dest, src, (sizeof(struct symbol) * len_src) + 1);

    return dest;
}

/* Purpose: get the length of a symbol table excluding the terminating symbol
 * Return:  the length of the table in number of elements
 *
 * sym: the input symbol table
 */
size_t symlen (const struct symbol * sym) {
    size_t sym_count = 0;
    for (const struct symbol * s = sym; s->name!=NULL; s++) {
        sym_count++;
    }
    return sym_count;
}
