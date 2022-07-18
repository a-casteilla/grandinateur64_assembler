/**
 * \file rpn.h
 * \brief API for the functions made to process RPN expressions
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 22th may 2022
 *
 */

#ifndef RPN_H

#define RPN_H

#include "common.h"

/**
 * \enum rpn_error
 * \brief error codes returned by the rpneval function
 */
enum rpn_error {
  rpn_error_no_error = 0,      /*!< Everything's fine */
  rpn_error_syntax_error,      /*!< If a syntax error happend */
  rpn_error_unknown_symbol,    /*!< If a symbol can't be computed */
  rpn_error_stack_overflow,    /*!< If too many items were pushed */
  rpn_error_stack_underflow,   /*!< If an operation can't be done because there isn't enough items */
  rpn_error_warning_non_empty, /*!< If the stack isn't empty after the last pull to get the result */
  rpn_error_warning_no_op      /*!< If no operation were done */
};

enum rpn_error rpneval (const char * exp, const struct scope * scope,
        const struct symbol * symbols, uint64_t * out) ;

#endif
