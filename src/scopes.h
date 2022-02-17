#ifndef SCOPES_H

#define SCOPES_H

#include "common.h"

/* Purpose: this function finds the different scopes of code (where a label is
 *          defined in a program
 * Return:  a pointer to the list of the scopes, NULL is returned if an error
 *          has occured
 *
 * lines: a pointer to the array of lines of the input. The pointer itself
 *        points to the first line of the input.
 */
struct scope * find_scopes (struct line * lines) ;

/* Purpose: This function finds the parent scope of a scope, the scope that
 *          contains the input scope
 * Return:  the address of the parent scope or the address of the input scope
 *          itself if it's the root
 *          
 * child: the address of the input scope for which we need to know the parents
 */
struct scope * parent_scope (struct scope * child) ;

/* Purpose: This function finds the root scope of a scope or the root scope of
 *          list of scopes
 * Return:  the address of the root scope or the address of the input scope
 *          itself if it's the root
 *          
 * child: the address of the input scope or of the list of scopes for which we
 *        need to know the root
 */
struct scope * root_scope (struct scope * child) ;

/* Purpose: This function finds in which scope is a line
 * Return:  the address of the scope that contains the line (the one that is a
 *          child)
 *
 * line: a pointer to the line for which we need to know the containing scope
 * scopes: the list of the scopes
 */
struct scope * scope_of_line (struct line * line, struct scope * scopes) ;

/* Purpose: This function finds in which scopes are all the lines
 * Return:  void
 * Modified input: lines
 *
 * lines: a pointer to the list of line for which we need to know the
 *        containing scopes
 * scopes: the list of the scopes
 */
void scope_of_lines (struct line * lines, struct scope * scopes) ;

#endif
