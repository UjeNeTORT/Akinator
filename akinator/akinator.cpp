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

#include "akinator.h"

#define streq(s1, s2) (!strcmp((s1), (s2)))

Tree ReadGuessTree (const char * tree_path)
{
    assert (tree_path && "tree path not given (null pointer)");

    FILE * tree_file = fopen (tree_path, "rb");

    Tree tree = ReadTree (tree_file);

    fclose (tree_file);

    return tree;
}

int WriteGuessTree (const char * tree_path, const Tree * tree)
{
    assert (tree_path && "tree path not given (null pointer)");
    assert (tree && "tree null pointer");

    FILE * tree_file = fopen (tree_path, "wb");

    WriteTree (tree_file, tree, PREORDER);

    fclose (tree_file);

    return 0;
}

int DrawGuessTree (const char * fname, const Tree * tree)
{
    assert(fname);
    assert(tree);

    fprintf(stdout, "AkinatorTree dump saved at Tree/tree_dump/dumps/dumps/%s\n", fname);

    return TreeDump (fname, tree);
}

int AkinatorGuess (TreeNode * node, FILE * user_stream)
{

    if (!node)
    {
        fprintf(stdout, "Oops! No such thing in my database! What is the difference between"); !!!
    }
    int guess_res = NULL;

    //!

    fprintf(stdout, "Does it have property \"%s\"?", node->data);

    char * user_answ = NULL;

    fscanf(user_stream, "%s", user_answ);

    if (streq(user_answ, "yes"))
    {
        guess_res = AkinatorGuess(node->right, user_stream);
    }
    else if (streq(user_answ, "no"))
    {
        guess_res = AkinatorGuess(node->left, user_stream);
    }
    else if (streq(user_answ, "q"))
    {
        // todo quit actions
        return guess_res;
    }

    //!

    return guess_res;
}
