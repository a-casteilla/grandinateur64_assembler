
/* This fonctions finds the different scopes of code */
/* Returns a pointer to the list of the scopes :
 * If NULL is returned an error has occured
 * */
struct scope * find_scopes (struct line * lines) {
    struct scope * scopes;
    size_t alloc_space_scopes = BUFSIZ;
    struct scope * scope_stack_base = malloc(256 * sizeof(struct scope));
    struct scope * scope_stack_top = scope_stack_base + 256;
    struct scope * scope_stack_pointer = scope_stack_base + 256;
    struct scope * scopes_pointer;
    struct scope temp_scope;
    struct line * l;
    unsigned int scopes_nb = 0;
    unsigned int level = 1;

    scopes = malloc(alloc_space_scopes);
    scopes_pointer = scopes;

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
                    free(scope_stack_base);
                    return NULL;
                }
                level++;
                break;
            case close_scope_directive:
                if (alloc_space_scopes <= scopes_nb * sizeof(struct scope) + 1) {
                    alloc_space_scopes += BUFSIZ;
                    scopes = realloc(scopes, alloc_space_scopes);
                }
                if (scope_stack_pointer >= scope_stack_top) {
                    display_error("Closing an inexistant scope", l);
                    free(scope_stack_base);
                    return NULL;
                }
                /* Close the scope */
                scope_stack_pointer->last_line = l;
                /* pull the scope from the stack and put it in the list */
                *(scopes_pointer++) = *(scope_stack_pointer++);
                level--;
                break;
            default:
                break;
        }
    }

    /* Throw an error if the stack is non-void */
    if (scope_stack_pointer != scope_stack_top) {
        fprintf(stderr, "Opened scope not closed (detected at the end of the file)\n\n");
        free(scope_stack_base);
        return NULL;
    }

    /* Add the scope that cover the entire file */
    temp_scope.first_line = lines;
    temp_scope.last_line = l;
    temp_scope.level = 0;
    *(scopes_pointer) = temp_scope;

    free(scope_stack_base);
    return scopes;
}

/* This function finds the parent scope of a scope */
/* Returns the address of the parent scope */
/* Returns the scope itself if it's the scope of level 0 */
/* Note : the function here is simpler than what we could expect.
 * Let's suppose we have a child with the level n. The parent has a level of n-1.
 * The list of scopes are ordered with the first scope closed first. This way,
 * we know that the parent scope has to be closed after the child. Otherwise,
 * the parent scope would not have been opened. The second scope and the scopes
 * after with a level of n-1 can't be the parent scope, because it means that
 * they must have been opened after the first scope with a n-1 level has been
 * closed. So they can't contain the child scope. The only possibility is the
 * first scope with a n-1 level that has been closed after the child */
struct scope * parent_scope (struct scope * child) {
    struct scope * parent = child;
    if (child->level) {
        while (parent->level != child->level - 1)
            parent++;
        return parent;
    } else {
        return child;
    }
}

/* This function finds the root scope of a scope or the root scope of list of
 * scopes */
struct scope * root_scope (struct scope * child) {
    struct scope * root = child;
    while (root->level) root++;
    return root;
}

/* This function finds in which scope is the line */
/* Can probably be optimised */
struct scope * scope_of_line (struct line * line, struct scope * scopes) {
    /* This for loop is exited when a scope that contains the line is found */
    for (struct scope * s = scopes; ; s++) {
        if (s->first_line <= line && s->last_line >= line) {
            return s;
        }
    }
}

void scope_of_lines (struct line * lines, struct scope * scopes) {
    for (struct line * l = lines; l->number; l++) {
        l->scope = scope_of_line(l, scopes);
    }
}

