/**
 * \file sym.c
 * \brief Functions made to process symbols inside an input file
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 22th may 2022
 *
 */

#include <sys/types.h>
#include <string.h>
#include "pointer.h"
#include "scopes.h"
#include "sym.h"

/**
 * \brief concatenate symbol tables
 * \return the src table concatenated to the end of the dest table
 *
 * \param dest the destination table
 * \param src the source symbol table
 *
 * Note: dest may be moved via realloc
 */
struct symbol *
symcat (struct symbol *       dest,
        const struct symbol * src)
{

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

/**
 * \brief get the length of a symbol table excluding the terminating symbol
 * \return the length of the table in number of elements
 *
 * \param sym the input symbol table
 */
size_t
symlen (const struct symbol * sym)
{
  size_t sym_count = 0;
  for (const struct symbol * s = sym; s->name!=NULL; s++) {
    sym_count++;
  }
  return sym_count;
}

/**
 * \brief convert a symbol back to its numerical value
 * \return boolean (true if a value has been found in the current scope)
 *
 * \param out a pointer to the output number
 * \param in a string that contains the symbol's name
 * \param scope a pointer to the scope where the conversion is
 * \param sym the symbol table
 */
bool
symtonum (uint64_t *            out,
          const char *          in,
          const struct scope *  scope,
          const struct symbol * sym)
{
  ssize_t last_match = -1; /* -1 means no match */
  ssize_t len_of_sym = symlen(sym);

  const struct scope * valid_scopes[256]; /* list of the scopes where the
                                             symbol is valid */
  size_t len_of_valid_scopes;

  /* find the list of scopes where the symbol is valid */
  {   /* Well, actually it was also weird with a for loop */
    const struct scope * s = scope;
    /* Below, it's a pointer to an array of constant struct scope */
    const struct scope ** vs = valid_scopes;
    *(vs++) = scope;

    while (s->level != 0) {
      s = parent_scope(s);
      *(vs++) = s;
    }
    *vs = NULL;
  }

  len_of_valid_scopes = pointerlen(valid_scopes);

  for (ssize_t i = 0; i < len_of_sym; i++) {
    /* actually searches the correspondance */
    if (strcmp((sym + i)->name, in) == 0
        && mempointer(valid_scopes, (sym + i)->scope,
          len_of_valid_scopes) != NULL) {
      last_match = i;
    }
  }

  *out = (sym + last_match)->value;

  return last_match != -1;
}
