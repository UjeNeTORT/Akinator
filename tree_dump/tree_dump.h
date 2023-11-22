/*************************************************************************
 * (c) 2023 Tikhonov Yaroslav (aka UjeNeTORT)
 *
 * email: tikhonovty@gmail.com
 * telegram: https://t.me/netortofficial
 * GitHub repo: https://github.com/UjeNeTORT
 *************************************************************************/

#ifndef TREE_DUMP_H
#define TREE_DUMP_H

#include <stdio.h>

#include "../tree/tree.h"

const char DOT_FILE_PATH[]   = "tree_dump/dumps/dot_files/";
const char GRAPH_PNGS_PATH[] = "tree_dump/dumps/png/";
const char HTML_DUMPS_PATH[] = "tree_dump/dumps/dumps/";

const int DOT_CODE_BUF_SIZE = 15000;

const int COMMAND_BUF_SIZE = 150;

const char GRAPH_BACKGROUND[] = "#006D77";
const char GRAPH_TEXTCLR[]    = "#EDF6F9";
const char GRAPH_CONDCLR[]    = "#83C5BE";
const char GRAPH_ANSWCLR[]    = "#E29578";

int TreeDump        (const char * fname, const Tree * tree);
int DotTreePrint    (const char * dot_fname, const Tree * tree);
int WriteHTML       (const char * HTML_fname, int dump_id, size_t err_vec);
int DotSubtreePrint (FILE * stream, const TreeNode * node);

#endif // TREE_DUMP_H
