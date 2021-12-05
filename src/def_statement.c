
/* This function counts the number of def directives */
/* The return value is (of course) the number of def directives in the file */
unsigned int count_def(struct line * lines) {
    nb_def = 0;
    for (struct line * l = lines; l->number; l++)
        if (mnemo[l->mnemo_nb].family == def_directive)
            nb_def++;
    return nb_def;
}

