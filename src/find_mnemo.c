#include <string.h>
#include <strings.h>
#include "mnemonic.h"
#include "find_mnemo.h"

/* Purpose: This function associates the mnemonic (or directive) of a line with
 *          its mnemonic number
 * Return:  error code (0 when everything is fine)
 * Modified input: current_line
 *
 * current_line: a pointer to the last fetched line (the line where we have to
 *               find the mnemo)
 */
int find_mnemo (struct line * current_line) {
    char * mnemonic; /* */
    bool match;      /* becomes true whenever a valid keyword is found */
    size_t i;        /* loop counter, and index of the valid keyword */

    current_line->prefix_nb = 0;

    if (!current_line->mnemo) {
        /* If there is no mnemonic in the line */
        current_line->mnemo_nb = 0;
        return 0;
    }

    if (strchr(current_line->mnemo, '.')) {
        /* The purpose of strchr here is to test the presence of the '.' char */
        /* This block is executed if the instruction is prefixed */
        mnemonic = strchr(current_line->mnemo, '.') + 1;
        * strchr(current_line->mnemo, '.') = 0;
        match = false;
        for (i = 0; i < sizeof(prefix)/sizeof(prefix[0]) && !match; i++) {
            match = !strcasecmp(current_line->mnemo, prefix[i].prefix);
        }
        i--;

        if (match) {
            current_line->prefix_nb = i;
        } else {
            /* when it doesn't match */
            safe_free(current_line->alloc_space);
            safe_free(current_line->args);
            display_error("Unknown prefix", current_line);
            return 1;
        }

    } else {
        mnemonic = current_line->mnemo;
    }

    match = false;
    for (i = 1; i < sizeof(mnemo)/sizeof(mnemo[0]) && !match; i++) {
        match = !strcasecmp(mnemonic, mnemo[i].mnemo);
    }
    i--;

    if (match) {
        current_line->mnemo_nb = i;
    } else {
        /* when it doesn't match */
        safe_free(current_line->alloc_space);
        safe_free(current_line->args);
        display_error("Unknown mnemonic or directive", current_line);
        return 1;
    }
    return 0;
}
