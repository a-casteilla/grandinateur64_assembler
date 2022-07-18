/**
 * \file def_statement.c
 * \brief Functions related to the "DEF" directive
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 19th april 2022
 *
 */

#include <string.h>
#include <strings.h>
#include "mnemonic.h"
#include "def_statement.h"
#include "common.h"
#include "rpn.h"
#include "sym.h"
#include "conv_string.h"

/**
 * \brief Counts the number of def directives in the file.
 * \return The number of def directives
 *
 * \param lines the lines of the input file, where def directives have to be counted.
 */
unsigned int
count_def (const struct line * lines)
{
  unsigned int nb_def = 0;
  for (const struct line * l = lines; l->number; l++) {
    if (mnemo[l->mnemo_nb].family == def_directive) {
      nb_def++;
    }
  }
  return nb_def;
}

/**
 * \brief Evaluates the DEF directives that can directly be evaluated
 * \return the table of evaluated symbols
 *
 * \param lines the lines of the input file
 * \param symbols the symbols that are already known
 *
 * All DEF directives that can be directly evaluated are evaluated with this
 * function. On the next run, the new directives are evaluated. Note that a
 * NULL pointer is returned if an error occured, and a pointer to a terminating
 * symbol is returned if no DEF directive were evaluated.
 */
/* Of course, I do everything in order to entertain mister God !!! */
struct symbol *
eval_def_once (struct line *   lines,
               struct symbol * known_symbols)
{
  size_t symbols_size = BUFSIZ;
  struct symbol * symbols = malloc(symbols_size);
  unsigned int nb_of_symbols = 0;
  bool error_happend = false;

  for (struct line * l = lines; l->number != 0; l++) {
    if (mnemo[l->mnemo_nb].family == def_directive) {

      /* Checks for the right count of argument */
      if (l->args == NULL) {
        display_error("Too few arguments for the DEF directive (name "
            "and value required)", l);
        error_happend = true;
      } else if (*(l->args) == NULL) {
        display_error("Too few arguments for the DEF directive (name "
            "and value required)", l);
        error_happend = true;
      } else if (*(l->args+1) == NULL) {
        display_error("Too few arguments for the DEF directive (name "
            "and value required)", l);
        error_happend = true;
      } else if (*(l->args+2) != NULL) {
        display_error("Too many arguments for the DEF directive (name "
            "and value required)", l);
        error_happend = true;
      }

      /* Now, adds the constant to the freshly created table */

#ifdef DO_NOT_COMPILE /* Will maybe be implemented later */
      /* Easy to implement, but I really wonder if this feature is really
       * necessary */
      /* Check if the constant is global */
      if (**((l->args)+1) == '+') {
        (*(l->args+1))++;
        (symbols+nb_of_symbols)->scope
          = root_scope(l->scope);
      }
      /* Check if the constant belongs to the parent scope */
      while (**((l->args)+1) == '&') {
        (*(l->args+1))++;
        (symbols+nb_of_symbols)->scope
          = parent_scope((symbols+nb_of_symbols)->scope);
      }
#endif
      if (l->args != NULL) {
        (symbols+nb_of_symbols)->name = *(l->args);
      } else {
        (symbols+nb_of_symbols)->name = NULL;
      }
      (symbols+nb_of_symbols)->scope = l->scope;

      /* Verifies if it's just a number */
      if (l->args != NULL ? *((l->args)+1) != NULL : false) {
        if (strspn(*((l->args)+1), "0123456789$%+-")) {
          if (convert_str_num(*((l->args)+1),
                &((symbols+nb_of_symbols)->value))) {
            display_error("Bad number format", l);
            error_happend = true;
          } else {
            (symbols+nb_of_symbols)->is_label = false;
            nb_of_symbols++;
            l->mnemo_nb = 0;
          }
          /* Then, verifies if the constant starts with "rpn(" */
        } else if (strncasecmp("rpn(", *((l->args)+1), 4) == 0) {
          char * chrepl = strchr(*((l->args)+1), ')');

          if (chrepl == NULL) {
            /* Throws an error */
            display_error("Unclosed rpn expression", l);
            error_happend = true;
          } else {
            *chrepl = 0;
            *((l->args)+1) += 4;
            switch(rpneval(*((l->args)+1), l->scope, known_symbols,
                  &((symbols+nb_of_symbols)->value)))
            {
              case rpn_error_no_error:
                /* nothing to do */
                (symbols+nb_of_symbols)->is_label = false;
                nb_of_symbols++;
                l->mnemo_nb = 0;
                break;
              case rpn_error_syntax_error:
                display_error("Syntax error", l);
                break;
              case rpn_error_unknown_symbol:
                /* revert the changes to the arguments */
                *chrepl = ')';
                *((l->args)+1) -= 4;
                break;
              case rpn_error_stack_overflow:
                display_error("Stack overflow", l);
                break;
              case rpn_error_stack_underflow:
                display_error("Stack underflow", l);
                break;
              case rpn_error_warning_non_empty:
                display_error("Warning: non-empty stack", l);
                (symbols+nb_of_symbols)->is_label = false;
                nb_of_symbols++;
                l->mnemo_nb = 0;
                /* nothing to do */
                break;
              case rpn_error_warning_no_op:
                display_error("Warning: no operation done", l);
                (symbols+nb_of_symbols)->is_label = false;
                nb_of_symbols++;
                l->mnemo_nb = 0;
                break;
              default: /* Should not be executed */
                display_error("Unknown error", l);
            }
          }
          /* Last case : convert from a known symbol */
        } else {
          if (symtonum(&((symbols+nb_of_symbols)->value),
                *((l->args)+1), l->scope, known_symbols)) {
            (symbols+nb_of_symbols)->is_label = false;
            nb_of_symbols++;
            l->mnemo_nb = 0;
          }
        }
      }

      /* Alloc more space if necessary */
      if ((nb_of_symbols + 1) * sizeof(struct symbol)
          > symbols_size) {
        symbols_size += BUFSIZ;
        symbols = realloc(symbols, symbols_size);
      }
    }
  }

  /* Alloc more space if necessary */
  if ((nb_of_symbols + 1) * sizeof(struct symbol)
      > symbols_size) {
    symbols_size += BUFSIZ;
    symbols = realloc(symbols, symbols_size);
  }

  if (error_happend) {
    safe_free(symbols);
  } else {
    (symbols+nb_of_symbols)->name = NULL;
  }

  return symbols;
}

/**
 * \brief Evaluates all the DEF directives
 * \return the table of all the symbols
 *
 * \param lines the lines of the input file
 * \param symbols the symbols that are already known
 *
 * All DEF directives that can be directly evaluated are evaluated with this
 * function. On the next run, the new directives are evaluated. Note that a
 * NULL pointer is returned if an error occured, and a pointer to a terminating
 * symbol is returned if no DEF directive were evaluated.
 */
struct symbol *
eval_all_def (struct line *   lines,
              struct symbol * known_symbols)
{
  struct symbol * eval_symbols   = NULL;
  bool            error_happend  = false;
  bool            last_def_reach = false;
  unsigned int    nb_of_def      = count_def(lines);

  if (known_symbols == NULL) {
    return NULL;
  }


  if (nb_of_def != 0) {
    /* The loop is exited if eval_symbols is pointing to a terminating symbol
     * at the last iteration or if an error happend. In any case, the loop
     * won't be executed more than the number of DEF statements */
    for (unsigned int i = 0;
        (i < nb_of_def) && !error_happend && !last_def_reach;
        i++) {
      eval_symbols = eval_def_once(lines, known_symbols);
      if (eval_symbols != NULL) {
        if (eval_symbols->name == NULL) {
          last_def_reach = true;
        } else {
          known_symbols = symcat(known_symbols, eval_symbols);
        }
        safe_free(eval_symbols);
      } else {
        error_happend = true;
      }
    }

    if (count_def(lines) != 0) {
      if (!error_happend) {
        error_happend = true;
        for (struct line * l = lines; l->number != 0; l++) {
          if (mnemo[l->mnemo_nb].family == def_directive) {
            display_error("Can't define constant", l);
          }
        }
      }
    }

    if (error_happend) {
      safe_free(known_symbols);
    }
  }
  return known_symbols;
}
