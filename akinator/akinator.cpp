/*************************************************************************
 * (c) 2023 Tikhonov Yaroslav (aka UjeNeTORT)
 *
 * email: tikhonovty@gmail.com
 * telegram: https://t.me/netortofficial
 * GitHub repo: https://github.com/UjeNeTORT
 *************************************************************************/

#include <assert.h>
#include <stdio.h>

#include "akinator.h"

Tree ReadGuessTree (const char * tree_path)
{
    assert (tree_path && "tree path not given (null pointer)");

    FILE * tree_file = fopen (tree_path, "rb");

    Tree tree = ReadTree (tree_file);

    fclose (tree_file);

    return tree;
}

int WriteGuessTree (const char * tree_path, Tree * tree)
{
    assert (tree_path && "tree path not given (null pointer)");
    assert (tree && "tree null pointer");

    FILE * tree_file = fopen (tree_path, "wb");

    WriteTree (tree_file, tree, PREORDER);

    fclose (tree_file);

    return 0;
}

char * AkinatorGuess (TreeNode * start_node)
{
    char * guess_res = "";


    return guess_res;
}
