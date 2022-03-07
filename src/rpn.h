#ifndef RPN_H

#define RPN_H

#include "common.h"

enum rpn_error {
    rpn_error_no_error = 0,
    rpn_error_syntax_error,
    rpn_error_unknown_symbol,
    rpn_error_stack_overflow,
    rpn_error_stack_underflow,
    rpn_error_warning_non_empty,
    rpn_error_warning_no_op
};

/* Purpose: perform a calculation, written with a post-fixed format.
 * Return:  error code (0 = no error, syntax error, unknown symbol,
 *          stack overflow, stack underflow, stack non-empty, no operation done)
 *
 * exp: the input expression
 * scope: the scope were the symbols are valid
 * symbols: the table of symbols in input
 * out: a pointer to the uint64_t in the output
 */
enum rpn_error rpneval (char * exp, const struct scope * scope,
        const struct symbol * symbols, uint64_t * out) ;

#endif
