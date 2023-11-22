/*************************************************************************
 * (c) 2023 Tikhonov Yaroslav (aka UjeNeTORT)
 *
 * email: tikhonovty@gmail.com
 * telegram: https://t.me/netortofficial
 * GitHub repo: https://github.com/UjeNeTORT
 *************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "tree_dump.h"

const char * GRAPH_BACKGROUND = "#006D77";
const char * GRAPH_TEXTCLR    = "#EDF6F9";
const char * GRAPH_CONDCLR    = "#83C5BE";
const char * GRAPH_ANSWCLR    = "#E29578";

int TreeDump (const char * fname, const Tree * tree)
{
    assert (fname);

    char * command = (char *) calloc (COMMAND_BUF_SIZE, sizeof(char));

    int dump_id = rand();

    DotTreePrint (fname, tree);

    sprintf (command, "dot -Tpng %s%s -o %sgraph_dump_%d.png", DOT_FILE_PATH, fname, GRAPH_PNGS_PATH, dump_id);
    system (command);

    free(command);

    WriteHTML("dump.html", dump_id, 0);

    return dump_id;
}

int DotTreePrint (const char * dot_fname, const Tree * tree)
{
    assert (dot_fname);

    chdir("tree_dump/dumps/dot_files");

    FILE * dot_file = fopen (dot_fname, "wb");

    fprintf (dot_file, "digraph TREE {\n"
                        "bgcolor =\"%s\"", GRAPH_BACKGROUND);

    DotSubtreePrint (dot_file, tree->root);

    fprintf (dot_file, "}\n");

    fclose (dot_file);

    chdir("../../../");

    return 0;
}

int WriteHTML (const char * HTML_fname, int dump_id, size_t err_vec)
{
    assert (HTML_fname);

    time_t t = time (NULL);

    tm * loc_time = localtime (&t);

    chdir("tree_dump/dumps/dumps");

    FILE * HTML_file = fopen (HTML_fname, "wb"); // ! attention, deletion of old dumps
    fprintf(HTML_file, "<div graph_%d style=\"background-color: %s; color: %s;\">\n", dump_id, GRAPH_BACKGROUND, GRAPH_TEXTCLR);

    fprintf (HTML_file, "<p style=\"color: %s; font-family:monospace; font-size: 20px\">[%s]\nTREE DUMP of \"s\" called from s (d) from s</p>", GRAPH_TEXTCLR, asctime(loc_time));

    fprintf (HTML_file, "<img src=\"../../../%sgraph_dump_%d.png\">\n", GRAPH_PNGS_PATH, dump_id);

    fprintf(HTML_file, "</div>\n");

    fprintf (HTML_file, "<hr> <!-- ============================================================================================================================ --> <hr>\n");
    fprintf (HTML_file, "\n");

    fclose (HTML_file);

    chdir("../../../");

    return 0;
}

int DotSubtreePrint (FILE * stream, const TreeNode * node)
{
    assert (stream);

    if (!node)
    {

        return 0;
    }

    int node_id = rand ();

    // todo function
    const char * shape = "";
    const char * color = "";

    if (node->left || node->right)
    {
        shape = "diamond";
        color = GRAPH_CONDCLR;
    }
    else
    {
        shape = "box";
        color = GRAPH_ANSWCLR;
    }

    fprintf (stream, "   node_%d [style = filled, shape = %s, label = \"%s\", fillcolor = \"%s\"]\n", node_id, shape, node->data, color);

    if (int left_subtree_id = DotSubtreePrint (stream, node->left))
        fprintf (stream, "   node_%d -> node_%d\n", node_id, left_subtree_id);

    if (int right_subtree_id = DotSubtreePrint (stream, node->right))
        fprintf (stream, "   node_%d -> node_%d\n", node_id, right_subtree_id);

    return node_id;
}
