#include <stdlib.h>
#include "align.h"
#include "conv_string.h"
#include "compute_addresses.h"
#include "mnemonic.h"

/* Purpose: This function compute the address of each line
 * Return:  error code (0 when everything is fine)
 * Modified input: lines
 *
 * lines: a pointer to the array of lines of the input. The pointer itself
 *        points to the first line of the input.
 */
enum ca_error compute_addresses (struct line * lines) {
    /* First of all, find the first PC directive
     * If there are none, throws an error */
    /* return value of the program */
    enum ca_error return_value = ca_error_no_error;
    /* Line just after the last PC directive discovered */
    struct line * line_after_pc = NULL;
    /* Line containing an align directive or a PC directive */
    struct line * line_with_add_dir = NULL;
    for (struct line * current_line = lines; current_line->number; ) {
        if (mnemo[current_line->mnemo_nb].family != pc_directive) {
            /* Check if the first directive is npc */
            if (mnemo[current_line->mnemo_nb].family == npc_directive) {
                current_line++;
            }

            /* goes forward to the next pc or npc directive or end of file*/
            for ( /* current_line doesn't need to be initialised */;
                    mnemo[current_line->mnemo_nb].family != pc_directive &&
                    mnemo[current_line->mnemo_nb].family != npc_directive &&
                    current_line->number ; current_line++) { }

            /* ERROR HANDLING */
            if (mnemo[current_line->mnemo_nb].family == npc_directive) {
                /* Traps because it means that : 
                 * There are more than one NPC directive between two PC 
                 * There aren't any PC directive. */
                display_error("Can't resolve address", current_line);
                return ca_error_undef_address; /* No need to continue */

            } else if (!current_line->number) {
                fprintf(stderr, "Can't resolve any address : no PC directive in"
                      " file \n\n");
                return ca_error_no_pc; /* No need to continue */
            }

            /* current_line contains a PC directive at this stage */
            if (convert_str_num(*(current_line->args), &(current_line->address))) {
                display_error("Bad number format", current_line);
                return_value = ca_error_bad_nb;
            }

            line_with_add_dir = current_line;
            line_after_pc = current_line + 1;

            /* compute the addresses of each line preceeding the PC directive */
            for (current_line--;
                    mnemo[current_line->mnemo_nb].family != npc_directive &&
                    current_line >= lines; current_line--) {
                current_line->address
                    = (current_line+1)->address - current_line->binsiz;
                /* If the current_line contains an alignement directive, shifts
                 * the whole code between this line and the preceeding
                 * directive */
                if (mnemo[current_line->mnemo_nb].family == ad_directive
                        || mnemo[current_line->mnemo_nb].family == aw_directive
                        || mnemo[current_line->mnemo_nb].family == ah_directive
                        || mnemo[current_line->mnemo_nb].family
                        == align_directive) {
                    uint64_t amount;
                    uint64_t boundary;
                    switch (mnemo[current_line->mnemo_nb].family) {
                        case ad_directive:
                            boundary = 8; break;
                        case aw_directive:
                            boundary = 4; break;
                        case ah_directive:
                            boundary = 2; break;
                        case align_directive:
                            if (convert_str_num(*(current_line->args), &boundary)) {
                                display_error("Bad number format", current_line);
                                return_value = ca_error_bad_nb;
                            }
                            if (!is_a_power_of_two(boundary)) {
                                display_error("Alignement can only be done on a"
                                        " power of two", current_line);
                                return_value = ca_error_align;
                            }
                            break;
                        default: /* Should not be executed */
                            abort();
                    }
                    amount = align_backward(current_line->address, boundary);
                    for (struct line * l = current_line; l != line_with_add_dir; l++) {
                        l->address -= amount;
                    }
                    line_with_add_dir = current_line;
                }
            }
            current_line = line_after_pc;
        } else {
            if (convert_str_num(*(current_line->args), &(current_line->address))) {
                display_error("Bad number format", current_line);
                return_value = ca_error_bad_nb;
            }
            current_line++;
        }
        for (; mnemo[current_line->mnemo_nb].family != pc_directive &&
                mnemo[current_line->mnemo_nb].family != npc_directive &&
                current_line->number ; current_line++) {
            current_line->address
                = (current_line-1)->address + (current_line-1)->binsiz;
            if (mnemo[current_line->mnemo_nb].family == ad_directive
                    || mnemo[current_line->mnemo_nb].family == aw_directive
                    || mnemo[current_line->mnemo_nb].family == ah_directive
                    || mnemo[current_line->mnemo_nb].family
                    == align_directive) {
                uint64_t boundary;
                switch (mnemo[current_line->mnemo_nb].family) {
                    case ad_directive:
                        boundary = 8; break;
                    case aw_directive:
                        boundary = 4; break;
                    case ah_directive:
                        boundary = 2; break;
                    case align_directive:
                        if (convert_str_num(*(current_line->args), &boundary)) {
                            display_error("Bad number format", current_line);
                            return_value = ca_error_bad_nb;
                        }
                        if (!is_a_power_of_two(boundary)) {
                            display_error("Alignement can only be done on a"
                                    " power of two", current_line);
                            return_value = ca_error_align;
                        }
                        break;
                    default: /* Should not be executed */
                        abort();
                }
                current_line->address = align(current_line->address, boundary);
                line_with_add_dir = current_line;
            }
        }
    }
    return return_value;
}

