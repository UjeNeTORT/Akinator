#ifndef TREE_DUMP_H
#define TREE_DUMP_H

#include <stdio.h>
#include "./tree.h"

const char * DOT_FILE_PATH   = "tree_dump/dumps/dot_files/";
const char * GRAPH_PNGS_PATH = "tree_dump/dumps/png/";
const char * HTML_DUMPS_PATH = "tree_dump/dumps/dumps/";

const int DOT_CODE_BUF_SIZE = 15000;

const int COMMAND_BUF_SIZE = 150;

int TreeDump (const char * fname, TreeNode * node);

#endif // TREE_DUMP_H
