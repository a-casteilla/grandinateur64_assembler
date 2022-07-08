/**
 * \file parse_line.c
 * \brief Function made to parse the input line in separated tokens
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 22th may 2022
 *
 */

#include "common.h"
#include "parse_line.h"

/**
 * \brief parse a line into separated tokens
 * \return error code (0 when everything is fine)
 *
 * \param current_line a pointer to the last fetched line
 *
 * The input line is splitted on spaces, then on commas
 * The label of the line and the comment (if there is any) are also detected
 * May be malloced: current_line->alloc_space, current_line->args
 */
int
parse_line (struct line * current_line)
{
  size_t size_of_line = strlen(current_line->text);
  /* Size of the actual textual line */
  char * next_token;

  /* Initialize the record */
  current_line->label = NULL;
  current_line->mnemo = NULL;
  current_line->args = NULL;
  current_line->comm = NULL;
  current_line->bin = NULL;
  current_line->binsiz = 0;
  current_line->alloc_space = malloc(size_of_line+1);

  strncpy(current_line->alloc_space, current_line->text, size_of_line);
  current_line->label = current_line->alloc_space;

  /* Removes the first spaces in the line */
  remove_preceeding_whitespaces(current_line->label);

  /* If the line is blank, there is nothing to do */
  if (*(current_line->label) == '\0') {
    current_line->label = NULL;
    safe_free(current_line->alloc_space);
    return 0;
  }

  /* I don't use strtok because I need to know the delimiting character */
  /* Gives the next token */
  next_token = current_line->label + strcspn(current_line->label, " ;,\t\n");

  if (*next_token == ';') {
    /* Detects if the next_token is a comment */
    current_line->comm = next_token + 1;
    *next_token = 0;
    next_token = NULL; /* To mean that is the end of the line */
  } else if (*next_token == ',') {
    /* Detects if there is a comma after the label or the mnemonic */
    display_error("Invalid syntax", current_line);
    safe_free(current_line->alloc_space);
    return 1;
  } else if (*next_token == '\n') {
    /* Detects if there is a comma after the label or the mnemonic */
    *next_token = 0;
    next_token = NULL; /* To mean that is the end of the line */
  }

  /* Change the ';' or the '\n' to a null char to terminate the current token */
  if (next_token != NULL)
    *(next_token++) = 0;

  /* If the token does not end with ':' then it's not a label, but a mnemonic */
  /* Else if the label is ":", then the label is invalid */
  /* Else if the label is valid, and there is a second token, then the second
   * token is the mnemonic */
  /* The only case when these conditions aren't executed, is when there is a
   * valid label and no mnemonic */
  if (*(current_line->label + strlen(current_line->label) - 1) != ':') {
    /* So the first field is the mnemonic and not the label */
    current_line->mnemo = current_line->label;
    current_line->label = NULL;

  } else if (strlen(current_line->label) == 1) {
    /* It's the case where the label field is ":" */
    display_error("Label name can't be void", current_line);
    safe_free(current_line->alloc_space);
    return 1;

  } else if (next_token != NULL) {
    /* If the first field is a label and there is a second field */
    current_line->mnemo = next_token;
    /* Removes the spaces before the mnemonic word */
    remove_preceeding_whitespaces(current_line->mnemo);
    next_token = current_line->mnemo + strcspn(current_line->mnemo, " ;,\t\n");

    if (*next_token == ';') {
      /* Detects if the next_token is a comment */
      current_line->comm = next_token + 1;
      *next_token = 0;
      next_token = NULL;
    } else if (*next_token == ',') {
      /* Detects if there is a comma after the mnemonic which is incorrect */
      display_error("Invalid syntax", current_line);
      safe_free(current_line->alloc_space);
      return 1;
    } else if (*next_token == '\n') {
      /* Detects if it's the end of the line */
      *next_token = 0;
      next_token = NULL;
    }
    if (next_token != NULL) {
      /* The case when there are arguments after */
      *(next_token++) = 0;
    }
  }

  /*
   * At the end of these branches, the following field have been processed:
   * + the label
   * + the mnemonic
   */

  /* The mnemonic field is tested:
   * if the pointer is not NULL, but points to a null char
   * then the mnemonic is made NULL */
  if (current_line->mnemo != NULL) {
    /* If there is a mnemonic */
    if (*(current_line->mnemo) == '\0') {
      /* If the mnemonic field is void */
      current_line->mnemo = NULL;
    }
  }

  /* Parse the arguments if there is any */
  if (next_token != NULL) {
    /* allows up to 32 arguments per line which is more than enough */
    current_line->args = malloc(32*sizeof(void *));
    for (size_t i = 0; next_token != NULL && i < 32; i++) {
      *(current_line->args + i) = next_token;

      /* Removes the spaces before the argument */
      remove_preceeding_whitespaces(*(current_line->args+i));

      /* Ends the current token */
      next_token = *(current_line->args+i) + strcspn(*(current_line->args+i), ";,\"\n");

      if (*next_token == ';') {
        /* The next token is a comment */
        current_line->comm = next_token + 1;
        *next_token = 0;
        next_token = NULL;
      } else if (*next_token == '"') {
        /* The next token is a string */
        /* The loop is exited if the */
        do {
          /* Increment pointer next_token, because it's probably
           * pointing to a '"' */
          next_token++;

          /* Find the end of the string, or an escape sequence */
          next_token += strcspn(next_token, "\\\"\n");

          /* At this point, next_token is pointing to a '\\', a '"',
           * a '\n' or a '\0'. It can't be pointing to anything else
           */
          while (*next_token == '\\') {
            /* Does not permit to have multiline strings */
            if (*(next_token+1) == '\n') {
              display_error("Invalid string", current_line);
              safe_free(current_line->args);
              safe_free(current_line->alloc_space);
              return 1;
            }
            /* ignore the character after the backslash */
            next_token += 2;
            /* go to the next token */
            next_token += strcspn(next_token, "\\\"\n");
          }
          /* Does not permit to have multiline strings */
          if (*next_token == '\n') {
            display_error("Invalid string", current_line);
            safe_free(current_line->args);
            safe_free(current_line->alloc_space);
            return 1;
          }
          next_token++;
          next_token += strcspn(next_token, ";,\"\n");
          if (*next_token == ';') {
            current_line->comm = next_token + 1;
            *next_token = 0;
            next_token = NULL;
          } else if (*next_token == '\n') {
            *next_token = 0;
            next_token = NULL;
          }
        } while (next_token != NULL ? *next_token == '"' : false) ;
        /* The condition above is equivalent to
         * (next_token != NULL && *next_token == '"')
         * However, when next_token is NULL, *next_token will do a
         * segmentation fault, that's why the syntax of this line is
         * very odd. */
        /* So the loop is exited if *next_token is not a '"' */

      } else if (*next_token == '\n') {
        /* ends the line, it's the last token */
        *next_token = 0;
        next_token = NULL;
      }
      if (next_token != NULL) {
        /* replace the end of the token with the terminating null char
        */
        *(next_token++) = 0;
      } else {
        /* It's the end of the line, so the args are terminated */
        *(current_line->args+i+1) = NULL;
      }

      /* Remove the last spaces in the argument */
      remove_trailing_whitespaces(*(current_line->args+i));
    }
  }

  /* If there is a comment, the trailing newline is deleted */
  if (current_line->comm != NULL) {
    strtok(current_line->comm, "\n");
  }

  /* If there is a label, the ':' is replaced with the null char */
  if (current_line->label != NULL) {
    *(current_line->label+strlen(current_line->label)-1) = 0;
  }

  return 0;
}
