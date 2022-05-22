/**
 * \file compute_addresses.h
 * \brief API for the function made to compute the address of each line
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 19th april 2022
 *
 */

#ifndef COMPUTE_ADDRESSES_H

#define COMPUTE_ADDRESSES_H

#include "common.h"

/**
 * \enum ca_error
 * \brief The error code of the function compute_addresses
 */
enum ca_error {
    ca_error_no_error = 0,  /*!< No error */
    ca_error_undef_address, /*!< If a line can't be resolved to an address (line between two NPC directives) */
    ca_error_no_pc,         /*!< When no PC value was given */
    ca_error_bad_nb,        /*!< If a number is not correctly formatted */
    ca_error_align          /*!< If an alignement can't be done (because the boundary is not a power of two) */
};

enum ca_error compute_addresses (struct line * lines) ;

#endif
