/*************************************************************************
 * (c) 2023 Tikhonov Yaroslav (aka UjeNeTORT)
 *
 * email: tikhonovty@gmail.com
 * telegram: https://t.me/netortofficial
 * GitHub:   https://github.com/UjeNeTORT
 * repo:     https://github.com/UjeNeTORT/Tree
 *************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
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

int AkinatorSubtreeGuess (TreeNode * node, TreeNode * previous, FILE * user_stream)
{
    assert(user_stream);

    int tree_changed = 0;

    if (!node)
    {
        fprintf(stdout, "Oops! No such thing in my database! What was it?\n>> ");
        char user_answ[MAX_WORD] = "";

        fgets(user_answ, MAX_WORD, user_stream);

        if (!previous->left)
        {
            previous->left = TreeNodeCtor(user_answ);
        }
        else if (!previous->right)
        {
            previous->right = TreeNodeCtor(user_answ);
        }

        tree_changed = 1;

        return tree_changed;
    }

    if (node->left || node->right)
    {
        fprintf(stdout, "Does it have property \"%s\"?\n>> ", node->data);

        char user_answ[MAX_YES_NO] = "";
        fscanf(user_stream, "%s", user_answ);
        fgetc(user_stream); // hanging \n

        if (streq(user_answ, "yes") || streq(user_answ, "y"))
        {
            tree_changed = AkinatorSubtreeGuess(node->right, node, user_stream);
        }
        else if (streq(user_answ, "no") || streq(user_answ, "n"))
        {
            tree_changed = AkinatorSubtreeGuess(node->left, node, user_stream);
        }
        else if (streq(user_answ, "q"))
        {
            // todo quit actions
            return tree_changed = 2; // quit while loop
        }
    }
    else
    {
        fprintf(stdout, "Is that %s?\n>> ", node->data);

        char user_answ[MAX_YES_NO] = "";

        fscanf(user_stream, "%s", user_answ);
        fgetc(user_stream); // hanging \n

        if (streq(user_answ, "yes") || streq(user_answ, "y"))
        {
            fprintf(stdout, "Hooray!\n");

            tree_changed = 0; // 0 - not changed
        }
        else if (streq(user_answ, "no") || streq(user_answ, "n"))
        {
            char * new_data = (char *) calloc (MAX_WORD, sizeof(char));
            fprintf(stdout, "Ohhh NO! What was it?\n>> ");
            fgets(new_data, MAX_WORD, user_stream);
            new_data[strcspn(new_data, "\r\n")] = 0;

            char * difference = (char *) calloc (MAX_WORD, sizeof(char));
            fprintf(stdout, "What is the difference between \"%s\" and \"%s\"?\n>> ", new_data, node->data);
            fgets(difference, MAX_WORD, user_stream);
            difference[strcspn(difference, "\r\n")] = 0;

            TreeNode * difference_node = TreeNodeCtor(difference);
            TreeNode * new_node        = TreeNodeCtor(new_data);

            if (node == previous->left) // if we are in left subtree of previous
            {
                previous->left = difference_node;
            }
            else if (node == previous->right)
            {
                previous->right = difference_node;
            }

            difference_node->left  = node;
            difference_node->right = new_node;

            tree_changed = 1; // changed

            fprintf(stdout, "Okay, now i know...\n");
        }
    }

    return tree_changed;
}

int AkinatorTreeGuess (Tree * tree, FILE * user_stream)
{
    assert(tree);
    assert(user_stream);

    return AkinatorSubtreeGuess(tree->root, NULL, user_stream);
}

int AkinatorSubtreeDefine (TreeNode * node, char * term)
{
    assert(node);
    assert(term);

    TreeNode * dst_node = SubtreeFind(node, term);
    if (!dst_node)
    {
        fprintf(stdout, "No such term in tree (%s not found)\n", term);

        return 1; // not found
    }
    stack * path = CtorStack(MAX_TREE_PATH);
    SubtreeNodePath(node, dst_node, path);
    stack * back_path = CtorStack(path->size); //? seems like crutch
    while (path->size > 0)
    {
        PushStack(back_path, PopStack(path));
    }

    TreeNode * curr_node = node;

    while(back_path->size > 0)
    {
        if (PopStack(back_path) == 0)
        {
            fprintf(stdout, "\tnot %s\n", curr_node->data);
            curr_node = curr_node->left;
        }
        else
        {
            fprintf(stdout, "\t%s\n", curr_node->data);
            curr_node = curr_node->right;
        }
    }

    DtorStack(back_path);
    DtorStack(path);

    return 0;
}

int AkinatorTreeDefine (Tree * tree, char * term)
{
    assert(tree);
    assert(term);

    if (!TreeFind(tree, term))
    {
        return 1;
    }

    fprintf(stdout, "%s has following properties:\n", term);

    AkinatorSubtreeDefine(tree->root, term);

    return 0; // found
}
