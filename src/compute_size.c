#include <string.h>
#include <sys/stat.h>
#include "compute_size.h"
#include "conv_string.h"
#include "mnemonic.h"

/* Purpose: This function compute the size in byte of a line of the input once
 *          assembled.
 * Return:  error code (0 when everything is fine)
 * Modified input: current_line
 *
 * current_line: a pointer to the last fetched line (the line where we have to
 *               compute the size)
 */
/* Note: a warning will still return 0. */
int compute_size (struct line * current_line) {
    int size = 0;
    switch (mnemo[current_line->mnemo_nb].family) {
        case dd_directive :    /* Data double-word */
            if (current_line->args) {
                for (int i = 0; *(current_line->args+i); i++) {
                    size += 8;
                }
            } else {
                display_error("Ignored directive : missing arguments", current_line);
            }
            break;
        case dw_directive :    /* Data word */
            if (current_line->args) {
                for (int i = 0; *(current_line->args+i); i++) {
                    size += 4;
                }
            } else {
                display_error("Ignored directive : missing arguments", current_line);
            }
            break;
        case dh_directive :    /* Data half-word */
            if (current_line->args) {
                for (int i = 0; *(current_line->args+i); i++) {
                    size += 2;
                }
            } else {
                display_error("Ignored directive : missing arguments", current_line);
            }
            break;
        case db_directive :    /* Data byte */
            if (current_line->args) {
                for (int i = 0; *(current_line->args+i); i++) {
                    size += 1;
                }
            } else {
                display_error("Ignored directive : missing arguments", current_line);
            }
            break;
        case ascii_directive : /* ascii string */
            if (current_line->args) {
                for (int i = 0; *(current_line->args+i); i++) {
                    convert_literal(current_line->args+i);
                    size += strlen(*(current_line->args+i));
                }
            } else {
                display_error("Ignored directive : missing arguments", current_line);
            }
            break;
        case asciz_directive : /* ascii string */
            if (current_line->args) {
                for (int i = 0; *(current_line->args+i); i++) {
                    convert_literal(current_line->args+i);
                    size += strlen(*(current_line->args+i)) + 1;
                }
            } else {
                display_error("Ignored directive : missing arguments", current_line);
            }
            break;
        case align_directive : /* align */
        case ad_directive :    /* align on double-word */
        case aw_directive :    /* align on word */
        case ah_directive :    /* align on half-word */
        case pc_directive :    /* set the PC */
        case def_directive :   /* constant definition */
        case no_mnemonic:
        case open_scope_directive:
        case close_scope_directive:
        case import_directive:
        case export_directive:
        case npc_directive:
            break;
        case bin_directive :   /* insertion of binary file */
            if (current_line->args) {
                struct stat stat_of_file;
                if (strchr(*current_line->args, '"'))
                    convert_literal(current_line->args);
                if (stat(*current_line->args, &stat_of_file)) {
                    display_error("File error", current_line);
                    return 1;
                } else {
                    size += stat_of_file.st_size;
                }
            } else {
                display_error("Ignored directive : missing arguments", current_line);
            }
            break;
        default:
            size += 4;
            break;
    }
    current_line->binsiz = size;
    return 0;
}

