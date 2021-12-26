#include "common.h"
#include "mnemonic.h"

/* This fonction parses a line into separted tokens */
/* Return an error code :
 * 0 means no error
 * 1 means an error occured
 * */
int parse_line (struct line * current_line) {
    size_t size_of_line = strlen(current_line->text); /* Size of the actual textual line */
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
    for (; *(current_line->label) == ' '; (current_line->label)++) { }

    if (!*(current_line->label)) {
        free(current_line->alloc_space);
        current_line->alloc_space = NULL;
        return 0;
    }

    /* I don't use strtok because I need to know the delimiting character */
    next_token = current_line->label + strcspn(current_line->label, " ;,\n");

    if (*next_token == ';') {
        current_line->comm = next_token + 1;
        *next_token = 0;
        next_token = NULL; /* To mean that is the end of the line */
    } else if (*next_token == ',') {
        display_error("Invalid syntax", current_line);
        return 1;
    } else if (*next_token == '\n') {
        *next_token = 0;
        next_token = NULL; /* To mean that is the end of the line */
    }

    if (next_token != NULL)
        *(next_token++) = 0;

    /* If the token does not end with ':' then it's not a label */
    if (*(current_line->label + strlen(current_line->label) -1) != ':') {
        /* So the first field is the mnemonic and not the label */
        current_line->mnemo = current_line->label;
        current_line->label = NULL;
    } else if (strlen(current_line->label) == 1) {
        display_error("Label name can't be void", current_line);
        return 1;
    } else if (next_token != NULL) { /* If the first field is a label and there
                                        is a second field */
        current_line->mnemo = next_token;
        /* Removes the spaces before the mnemonic word */
        for (; *(current_line->mnemo) == ' '; (current_line->mnemo)++) { }
        next_token = current_line->mnemo + strcspn(current_line->mnemo, " ;,\n");

        if (*next_token == ';') {
            current_line->comm = next_token + 1;
            *next_token = 0;
            next_token = NULL;
        } else if (*next_token == ',') {
            display_error("Invalid syntax", current_line);
            return 1;
        } else if (*next_token == '\n') {
            *next_token = 0;
            next_token = NULL;
        }
        if (next_token != NULL)
            *(next_token++) = 0;
    }

    if (current_line->mnemo != NULL)
        if (!*(current_line->mnemo))
            current_line->mnemo = NULL;
    
    /* Parse the arguments if there is any */
    if (next_token != NULL) {
        current_line->args = malloc(128); /* allows up to 32 arguments per
                                              line which is more than enough */
        for (size_t i = 0; next_token != NULL && i < 32; i++) {
            *(current_line->args + i) = next_token;

            /* Removes the spaces before the argument */
            for (; **(current_line->args+i) == ' '; *(current_line->args+i) =
                    *(current_line->args+i) + 1) { }
            next_token = *(current_line->args+i) + strcspn(*(current_line->args+i), ";,\"\n");

            if (*next_token == ';') {
                current_line->comm = next_token + 1;
                *next_token = 0;
                next_token = NULL;
            } else if (*next_token == '"') {
                do {
                    next_token++;
                    next_token += strcspn(next_token, "\\\"\n");
                    while (*next_token == '\\') {
                        if (*(next_token+1) == '\n') {
                            display_error("Invalid string", current_line);
                            return 1;
                        }
                        next_token += 2;
                        next_token += strcspn(next_token, "\\\"\n");
                    }
                    if (*next_token == '\n') {
                        display_error("Invalid string", current_line);
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

            } else if (*next_token == '\n') {
                *next_token = 0;
                next_token = NULL;
            }
            if (next_token != NULL)
                *(next_token++) = 0;
            else
                *(current_line->args+i+1) = NULL;

            /* Remove the last spaces in the argument */
            for (char * j = *(current_line->args+i) +
                    strlen(*(current_line->args+i)) - 1; *j == ' '; j--)
                *j = 0;
        }
    }     

    if (current_line->comm != NULL)
        strtok(current_line->comm, "\n");

    if (current_line->label != NULL)
        *(current_line->label+strlen(current_line->label)-1) = 0;

    return 0;
}

