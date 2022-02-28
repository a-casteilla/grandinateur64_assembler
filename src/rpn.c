#include <string.h>
#include <stdbool.h>
#include "conv_string.h"
#include "rpn.h"

/* Go to each function if you want to see there purpose. */
static void rpnadd (uint64_t sp) ;
static void rpnsub (uint64_t sp) ;
static void rpnmul (uint64_t sp) ;
static void rpndiv (uint64_t sp) ;
static void rpnlsh (uint64_t sp) ;
static void rpnrsh (uint64_t sp) ;
static void rpnmod (uint64_t sp) ;
static void rpnand (uint64_t sp) ;
static void rpnor  (uint64_t sp) ;
static void rpnxor (uint64_t sp) ;
static void rpninv (uint64_t sp) ;
static void rpnneg (uint64_t sp) ;

/* Purpose: perform a calculation, written with a post-fixed format.
 * Return:  error code (0 = no error, syntax error, unknown symbol,
 *          stack overflow, stack underflow, stack non-void, no operation done)
 *
 * exp: the input expression
 * scope: the scope were the symbols are valid
 * symbols: the table of symbols in input
 * out: a pointer to the uint64_t in the output
 */
int rpneval (char * exp, const struct scope * scope,
        const struct symbol * symbols, uint64_t * out) {

    /* Initialise a stack with a fixed number of elements (253 are enough) */
    /* Note that index 0 and index 254 and 255 are sentinels for respectively
     * stack overflow and stack underflow */
    uint64_t stack[256];

    int error_nb = rpn_error_warning_no_op;

    uint64_t * stack_base = stack + 254;
    uint64_t * stack_pointer = stack_base;

    /* Function pointer to the operation that will be done on the stack */
    /* Returns void */
    void (* operation) (uint64_t *) = NULL;

    strtok(exp, " ");

    do {
        /* Verify if the token is an operator */
        if ((strlen(exp) == 1) && (strcspn(exp, "+-*/<>%&|^~!"))) {
            /* do the operation */
            switch (*exp) {
                case '+':
                    operation = rpnadd;
                    break;
                case '-':
                    operation = rpnsub;
                    break;
                case '*':
                    operation = rpnmul;
                    break;
                case '/':
                    operation = rpndiv;
                    break;
                case '<':
                    operation = rpnlsh;
                    break;
                case '>':
                    operation = rpnrsh;
                    break;
                case '%':
                    operation = rpnmod;
                    break;
                case '&':
                    operation = rpnand;
                    break;
                case '|':
                    operation = rpnor;
                    break;
                case '^':
                    operation = rpnxor;
                    break;
                case '~':
                    operation = rpninv;
                    break;
                case '!':
                    operation = rpnneg;
                    break;
                default:
                    /* unknown error */
                    /* Should not happend, even if the input is erroneous */
                    /* Crashes the program btw on purpose */
                    abort();
                    break;
            }
            operation(stack_pointer);
            error_nb = rpn_error_no_error;
        } else if (strcspn(exp, "0123456789$%+-abcdefABCDEF")) {
            /* push the number */
            *(--sp) = convert_str_num(exp);
        } else {
            /* fetches the label and push it to the stack */
            /* TODO: because the conversion of the labels is missing */
            *(--sp) = convert_str_num(exp);
        }

        /* Check that the stack doesn't underflow nor overflow */
        if (stack_pointer <= stack) {
            /* Case of a stack overflow */
            error_nb = rpn_error_stack_overflow;
        } else if ((stack_pointer > stack_base)) {
            /* Case of a stack underflow */
            error_nb = rpn_error_stack_underflow;
        }
    } while (
            strtok(exp, " ") != NULL
            && error_nb != rpn_error_stack_overflow
            && error_nb != rpn_error_stack_underflow
            && error_nb != rpn_error_unknown_symbol
            && error_nb != rpn_error_syntax_error
            ) ;
    
    if (
}

/* Purpose: adds two numbers on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpnadd (uint64_t sp) {
    *(sp++) = *sp + *(sp+1);
}

/* Purpose: subtracts two numbers on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpnsub (uint64_t sp) {
    *(sp++) = *sp - *(sp+1);
}

/* Purpose: multiplies two numbers on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpnmul (uint64_t sp) {
    *(sp++) = *sp * *(sp+1);
}

/* Purpose: divides two numbers on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpndiv (uint64_t sp) {
    *(sp++) = *sp / *(sp+1);
}

/* Purpose: left shifts two numbers on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpnlsh (uint64_t sp) {
    *(sp++) = *sp << *(sp+1);
}

/* Purpose: right shifts two numbers on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpnrsh (uint64_t sp) {
    *(sp++) = *sp >> *(sp+1);

/* Purpose: does the modulo of two numbers on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpnmod (uint64_t sp) {
    *(sp++) = *sp % *(sp+1);
}

/* Purpose: ands two numbers on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpnand (uint64_t sp) {
    *(sp++) = *sp & *(sp+1);
}

/* Purpose: ors two numbers on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpnor (uint64_t sp) {
    *(sp++) = *sp | *(sp+1);
}

/* Purpose: does the exclusive-or of two numbers on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpnxor (uint64_t sp) {
    *(sp++) = *sp ^ *(sp+1);
}

/* Purpose: find the first complement of a number on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpninv (uint64_t sp) {
    *sp = ~(*sp);
}

/* Purpose: negates one number on the stack
 * Return: void
 *
 * sp: pointer to the stack
 */
static void rpnneg (uint64_t sp) {
    *sp = -(*sp);
}
