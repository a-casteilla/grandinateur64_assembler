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
int compute_addresses (struct line * lines) {
    /* First of all, find the first PC directive
     * If there are none, throws an error */
    int return_value = 0;                   /* return value of the program */
    struct line * line_after_pc = NULL;     /* Line just after the last PC
                                               directive discovered */
    struct line * line_with_add_dir = NULL; /* Line containing an align
                                               directive or a PC directive */
    for (struct line * current_line = lines; current_line->number; ) {
        if (mnemo[current_line->mnemo_nb].family != pc_directive) {
            /* Check if the first directive is npc */
            if (mnemo[current_line->mnemo_nb].family == npc_directive) {
                current_line++;
            }
            /* goes forward to the next pc or npc directive */
            for (; mnemo[current_line->mnemo_nb].family != pc_directive &&
                    mnemo[current_line->mnemo_nb].family != npc_directive &&
                    current_line->number ; current_line++) {
            }
            if (mnemo[current_line->mnemo_nb].family == npc_directive) {
                /* Traps because it means that : 
                 * There are more than one NPC directive between two PC 
                 * There aren't any PC directive. */
                display_error("Can't resolve address", current_line);
                return 1; /* No need to continue */
            } else if (!current_line->number) {
                fprintf(stderr, "Can't resolve any address : no PC directive in"
                      " file \n\n");
                return 1; /* No need to continue */
            }
            /* current_line contains a PC directive at this stage */
            current_line->address = convert_str_num(*(current_line->args));
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
                            boundary = convert_str_num(*(current_line->args));
                            if (!is_a_power_of_two(boundary)) {
                                display_error("Alignement can only be done on a"
                                        " power of two", current_line);
                                return_value = 1;
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
            current_line->address = convert_str_num(*(current_line->args));
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
                        boundary = convert_str_num(*(current_line->args));
                        if (!is_a_power_of_two(boundary)) {
                            display_error("Alignement can only be done on a"
                                    " power of two", current_line);
                            return_value = 1;
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

