/**
 * \file rpn.c
 * \brief Functions made to process RPN expressions
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 22th may 2022
 *
 */

#include <string.h>
#include <stdbool.h>
#include "conv_string.h"
#include "rpn.h"
#include "sym.h"

static void rpnadd (uint64_t ** sp) ;
static void rpnsub (uint64_t ** sp) ;
static void rpnmul (uint64_t ** sp) ;
static void rpndiv (uint64_t ** sp) ;
static void rpnlsh (uint64_t ** sp) ;
static void rpnrsh (uint64_t ** sp) ;
static void rpnmod (uint64_t ** sp) ;
static void rpnand (uint64_t ** sp) ;
static void rpnor  (uint64_t ** sp) ;
static void rpnxor (uint64_t ** sp) ;
static void rpninv (uint64_t ** sp) ;
static void rpnneg (uint64_t ** sp) ;
static void rpndivsign (uint64_t ** sp) ;
static void rpnrshsign (uint64_t ** sp) ;
static void rpnmodsign (uint64_t ** sp) ;

/**
 * \brief perform a calculation, written with a post-fixed format.
 * \return error code
 *
 * \param exp the input expression
 * \param scope the scope were the symbols are valid
 * \param symbols the table of symbols in input
 * \param out a pointer to the uint64_t in the output
 */
/* No const for exp, because it is passed as an argument to strtok */
enum rpn_error
rpneval
(char * exp,
 const struct scope * scope,
 const struct symbol * symbols,
 uint64_t * out)
{

    /* Initialise a stack with a fixed number of elements (253 are enough) */
    /* Note that index 0 and index 254 and 255 are sentinels for respectively
     * stack overflow and stack underflow */
    uint64_t stack[256];

    enum rpn_error error_nb = rpn_error_warning_no_op;

    uint64_t * stack_base = stack + 254;
    uint64_t * stack_pointer = stack_base;

    /* Function pointer to the operation that will be done on the stack */
    void (* operation) (uint64_t **) = NULL;

    char * stack_cmd;

    stack_cmd = strtok(exp, " ");

    do {
        /* Verify if the token is an operator */
        if ((strlen(stack_cmd) == 1) && (strspn(stack_cmd, "+-*/<>%&|^~!"))) {
            /* do the operation */
            switch (*stack_cmd) {
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
            operation(&stack_pointer);
            error_nb = rpn_error_no_error;

        /* Verify if the token is a signed operator */
        } else if ((strlen(stack_cmd) == 2) && (strspn(stack_cmd, "/>%"))
                && (*stack_cmd == *(stack_cmd + 1))) {
            /* do the operation */
            switch (*stack_cmd) {
                case '/':
                    operation = rpndivsign;
                    break;
                case '>':
                    operation = rpnrshsign;
                    break;
                case '%':
                    operation = rpnmodsign;
                    break;
                default:
                    /* unknown error */
                    /* Should not happend, even if the input is erroneous */
                    /* Crashes the program btw on purpose */
                    abort();
                    break;
            }
            operation(&stack_pointer);
            error_nb = rpn_error_no_error;

            /* Verifies if the token is a number */
        } else if (strspn(stack_cmd, "0123456789$%+-")) {
            /* push the number */
            --stack_pointer;
            if (convert_str_num(stack_cmd, stack_pointer)) {
                error_nb = rpn_error_syntax_error;
            }

            /* Check for a syntax error */
        } else if (strspn(stack_cmd, "*/<>&|^~!")) {
            error_nb = rpn_error_syntax_error;
        } else {
            /* fetches the label and push it to the stack */
            if (!symtonum(--stack_pointer, stack_cmd, scope, symbols)) {
                error_nb = rpn_error_unknown_symbol;
            }
        }

        /* Check that the stack doesn't underflow nor overflow */
        if (stack_pointer <= stack) {
            /* Case of a stack overflow */
            error_nb = rpn_error_stack_overflow;
        } else if ((stack_pointer >= stack_base) &&
                (operation != rpninv)
                && (operation != rpnneg)
                && (operation != NULL)
                ) {
            /* Case of a stack underflow */
            error_nb = rpn_error_stack_underflow;
        }
        
        /* The next operation is parsed */
        stack_cmd = strtok(NULL, " ");
        
    } while (
            stack_cmd != NULL
            && error_nb != rpn_error_stack_overflow
            && error_nb != rpn_error_stack_underflow
            && error_nb != rpn_error_unknown_symbol
            && error_nb != rpn_error_syntax_error
            ) ;

    /* set the output */
    *out = *(stack_pointer++);
    /* test the stack non-empty condition */
    if (
            stack_pointer != stack_base
            && error_nb != rpn_error_stack_overflow
            && error_nb != rpn_error_stack_underflow
            && error_nb != rpn_error_unknown_symbol
            && error_nb != rpn_error_syntax_error
       ) {
        error_nb = rpn_error_warning_non_empty;
    }

    return error_nb;
}

/**
 * \brief adds two numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnadd (uint64_t ** sp)
{
    *((*sp)+1) += **sp;
    (*sp)++;
}

/**
 * \brief subtracts two numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnsub (uint64_t ** sp)
{
    *((*sp)+1) -= **sp;
    (*sp)++;
}

/**
 * \brief multiplies two numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnmul (uint64_t ** sp)
{
    *((*sp)+1) *= **sp;
    (*sp)++;
}

/**
 * \brief divides two numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpndiv (uint64_t ** sp)
{
    *((*sp)+1) /= **sp;
    (*sp)++;
}

/**
 * \brief left shifts two numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnlsh (uint64_t ** sp)
{
    *((*sp)+1) <<= **sp;
    (*sp)++;
}

/**
 * \brief right shifts two numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnrsh (uint64_t ** sp)
{
    *((*sp)+1) >>= **sp;
    (*sp)++;
}

/**
 * \brief does the modulo of two numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnmod (uint64_t ** sp)
{
    *((*sp)+1) %= **sp;
    (*sp)++;
}

/**
 * \brief ands two numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnand (uint64_t ** sp)
{
    *((*sp)+1) &= **sp;
    (*sp)++;
}

/**
 * \brief ors two numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnor (uint64_t ** sp)
{
    *((*sp)+1) |= **sp;
    (*sp)++;
}

/**
 * \brief does the exclusive-or of two numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnxor (uint64_t ** sp)
{
    *((*sp)+1) ^= **sp;
    (*sp)++;
}

/**
 * \brief find the first complement of a number on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpninv (uint64_t ** sp)
{
    **sp = ~(**sp);
}

/**
 * \brief negates one number on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnneg (uint64_t ** sp)
{
    **sp = -(**sp);
}

/**
 * \brief divides two signed numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpndivsign (uint64_t ** sp)
{
    *((*sp)+1) = (uint64_t)((int64_t)(*((*sp)+1)) / (int64_t)(**sp));
    (*sp)++;
}

/**
 * \brief right shifts two signed numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnrshsign (uint64_t ** sp)
{
    *((*sp)+1) = (uint64_t)((int64_t)(*((*sp)+1)) >> (int64_t)(**sp));
    (*sp)++;
}

/**
 * \brief does the modulo of two signed numbers on the stack
 * \return void
 *
 * \param sp pointer to the stack
 */
static void
rpnmodsign (uint64_t ** sp)
{
    *((*sp)+1) = (uint64_t)((int64_t)(*((*sp)+1)) % (int64_t)(**sp));
    (*sp)++;
}
