#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tree_dump.h"

int TreeDump(const char * fname, Tree * tree)
{
    assert(fname);

    char * command = (char *) calloc(COMMAND_BUF_SIZE, sizeof(char));

    int dump_id = rand();

    sprintf(command, "dot -Tpng %s%s -o %sgraph_dump_%d.png", DOT_FILE_PATH, fname, GRAPH_PNGS_PATH, dump_id);
    system(command);

    return 0;
}

char * CreateTreeGraph (const char * dot_fname, Tree * tree)
{
    assert(dot_fname);

    char * dot_code = (char *) calloc(DOT_CODE_BUF_SIZE, sizeof(char));



    return dot_code;
}

int WriteHTML (const char * HTML_fname, int dump_id, size_t err_vec)
{
    assert(HTML_fname);

    time_t t = time(NULL);

    tm * loc_time = localtime(&t);

    FILE * HTML_file = fopen(HTML_fname, "ab");

    fprintf(HTML_file, "<p style=\"font-family:monospace; font-size: 20px\">[%s]\nTREE DUMP of \"\%s\" called from \%s (\%d) from \%s</p>", asctime(loc_time));

    fprintf(HTML_file, "<img src=\"./%sgraph_dump_%d.png\">\n", GRAPH_PNGS_PATH, dump_id);

    fprintf(HTML_file, "<hr>\n", dump_id);
    fprintf(HTML_file, "<hr>\n", dump_id);

    fclose(HTML_file);

    return 0;
}
