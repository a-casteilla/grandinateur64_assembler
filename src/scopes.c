#include "mnemonic.h"
#include "scopes.h"

/* Purpose: this function finds the different scopes of code (where a label is
 *          defined in a program
 * Return:  a pointer to the list of the scopes, NULL is returned if an error
 *          has occured
 *
 * lines: a pointer to the array of lines of the input. The pointer itself
 *        points to the first line of the input.
 */
struct scope * find_scopes (const struct line * lines) {
    struct scope * scopes;
    size_t alloc_space_scopes = BUFSIZ;
    /* I won't resize the stack : 256 levels are more than enough */
    /* That's why I do a static allocation */
    struct scope scope_stack_base[256];
    struct scope * scope_stack_top = scope_stack_base + 256;
    struct scope * scope_stack_pointer = scope_stack_base + 256;
    struct scope temp_scope;
    const struct line * l;
    unsigned int scopes_nb = 0;
    unsigned int level = 1;

    scopes = malloc(alloc_space_scopes);

    for (l = lines; l->number; l++) {
        switch (mnemo[l->mnemo_nb].family) {
            case open_scope_directive:
                /* create and push the scope */
                temp_scope.first_line = l;
                temp_scope.last_line = l;
                temp_scope.level = level;
                *(--scope_stack_pointer) = temp_scope;
                /* check for a stack overflow */
                /* I won't resize the stack : 256 levels are more than enough */
                if (scope_stack_pointer <= scope_stack_base) {
                    display_error("Too many nested scopes (256 maximum)", l);
                    safe_free(scopes);
                    return NULL;
                }
                level++;
                break;
            case close_scope_directive:
                if (alloc_space_scopes <= (scopes_nb + 1) * sizeof(struct scope)) {
                    alloc_space_scopes += BUFSIZ;
                    scopes = realloc(scopes, alloc_space_scopes);
                }
                if (scope_stack_pointer >= scope_stack_top) {
                    display_error("Closing an inexistant scope", l);
                    safe_free(scopes);
                    return NULL;
                }
                /* Close the scope */
                scope_stack_pointer->last_line = l;
                /* pull the scope from the stack and put it in the list */
                *(scopes + (scopes_nb++)) = *(scope_stack_pointer++);
                level--;
                break;
            default:
                break;
        }
    }

    /* Throw an error if the stack is non-void */
    if (scope_stack_pointer != scope_stack_top) {
        fprintf(stderr, "Opened scope not closed (detected at the end of the file)\n\n");
        safe_free(scopes);
        return NULL;
    }

    /* Add the scope that cover the entire file */
    temp_scope.first_line = lines;
    temp_scope.last_line = l;
    temp_scope.level = 0;
    *(scopes + scopes_nb) = temp_scope;

    return scopes;
}

/* Purpose: This function finds the parent scope of a scope, the scope that
 *          contains the input scope
 * Return:  the address of the parent scope or the address of the input scope
 *          itself if it's the root
 *          
 * child: the address of the input scope for which we need to know the parents
 */
/* Note : the function here is simpler than what we could expect.
 * Let's suppose we have a child with the level n. The parent has a level of n-1.
 * The list of scopes are ordered with the first scope closed first. This way,
 * we know that the parent scope has to be closed after the child. Otherwise,
 * the parent scope would not have been opened. The second scope and the scopes
 * after with a level of n-1 can't be the parent scope, because it means that
 * they must have been opened after the first scope with a n-1 level has been
 * closed. So they can't contain the child scope. The only possibility is the
 * first scope with a n-1 level that has been closed after the child */
const struct scope * parent_scope (const struct scope * child) {
    const struct scope * parent = child;
    if (child->level) {
        while (parent->level != child->level - 1) {
            parent++;
        }
    }
    return parent;
}

/* Purpose: This function finds the root scope of a scope or the root scope of
 *          list of scopes
 * Return:  the address of the root scope or the address of the input scope
 *          itself if it's the root
 *          
 * child: the address of the input scope or of the list of scopes for which we
 *        need to know the root
 */
const struct scope * root_scope (const struct scope * child) {
    const struct scope * root = child;
    while (root->level) root++;
    return root;
}

/* Purpose: This function finds in which scope is a line
 * Return:  the address of the scope that contains the line (the one that is a
 *          child)
 *
 * line: a pointer to the line for which we need to know the containing scope
 * scopes: the list of the scopes
 */
const struct scope * scope_of_line (const struct line * line, const struct scope * scopes) {
    /* This for loop is exited when a scope that contains the line is found */
    const struct scope * s;
    for (s = scopes;
            !(s->first_line <= line && s->last_line >= line);
            /* true when line not in scope */
            s++) {}
    return s;
}

/* Purpose: This function finds in which scopes are all the lines
 * Return:  void
 * Modified input: lines
 *
 * lines: a pointer to the list of line for which we need to know the
 *        containing scopes
 * scopes: the list of the scopes
 */
void scope_of_lines (struct line * lines, const struct scope * scopes) {
    for (struct line * l = lines; l->number; l++) {
        l->scope = scope_of_line(l, scopes);
    }
}

