
/* This function associates the mnemonic of a line with its mnemonic number */
/* Return an error code :
 * 0 means no error
 * 1 means an error occured
 * */
int find_mnemo (struct line * current_line) {
    char * mnemonic;
    bool match;
    size_t i;
    current_line->prefix_nb = 0;
    if (!current_line->mnemo) {
        current_line->mnemo_nb = 0;
        return 0;
    }
    if (strchr(current_line->mnemo, '.')) {
        /* This block is executed if the instruction is prefixed */
        mnemonic = strchr(current_line->mnemo, '.') + 1;
        * strchr(current_line->mnemo, '.') = 0;
        match = false;
        for (i = 0; i < sizeof(prefix)/sizeof(prefix[0]) && !match; i++)
            match = !strcasecmp(current_line->mnemo, prefix[i].prefix);
        i--;
        if (match) {
            current_line->prefix_nb = i;
        } else {
            display_error("Unknown prefix", current_line);
            return 1;
        }
    } else {
        mnemonic = current_line->mnemo;
    }
    match = false;
    for (i = 1; i < sizeof(mnemo)/sizeof(mnemo[0]) && !match; i++)
        match = !strcasecmp(mnemonic, mnemo[i].mnemo);
    i--;
    if (match) {
        current_line->mnemo_nb = i;
    } else {
        display_error("Unknown mnemonic or directive", current_line);
        return 1;
    }
    return 0;
}

