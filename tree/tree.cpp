/*************************************************************************
 * (c) 2023 Tikhonov Yaroslav (aka UjeNeTORT)
 *
 * email: tikhonovty@gmail.com
 * telegram: https://t.me/netortofficial
 * GitHub repo: https://github.com/UjeNeTORT
 *************************************************************************/

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "../colors.h"
#include "tree.h"

TreeNode* TreeNodeCtor (elem_t val)
{
    TreeNode * new_node = (TreeNode *) calloc(1, sizeof(TreeNode));

    new_node->data   = val;
    new_node->left  = NULL;
    new_node->right = NULL;

    return new_node;
}

int TreeNodeDtor (TreeNode * node)
{
    if (!node)
    {
        return 0;
    }

    free((void *) node->data);

    free(node);

    return 0;
}

Tree TreeCtor (TreeNode * root)
{
    Tree tree = { root, 0 };

    return tree;
}

int TreeDtor (Tree * tree)
{
    assert(tree);

    // traverse the tree and free each node
    TraverseTree(tree, TreeNodeDtor, POSTORDER);

    return 0;
}

int TreeHangLeafSorted (Tree * tree, TreeNode * node, TreeNode * new_node, NodeCmp_t Comparator)
{
    assert(tree);
    assert(new_node);

    int ret_val = 0;

    if (!node && !tree->root)
    {
        if (tree->size == 0) // new node is tree root then
        {
            tree->root = new_node;

            tree->size++;

            return ret_val;
        }
        else
        {
            ret_val = -1; // error code

            return ret_val;
        }
    }

    int cmp_res = Comparator(new_node, node);

    if (cmp_res <= 0)
    {
        if (node->left)
        {
            ret_val = TreeHangLeafSorted (tree, node->left, new_node, Comparator);
        }
        else
        {
            node->left = new_node;
        }
    }
    else
    {
        if (node->right)
        {
            ret_val = TreeHangLeafSorted (tree, node->right, new_node, Comparator);
        }
        else
        {
            node->right = new_node;
        }
    }

    tree->size++;

    return ret_val;
}

int TreeHangNode (Tree * tree, TreeNode * node, TreeNode * new_node, NodeLocation new_node_location, NodeLocation subtree_location)
{
    assert(tree);

    int ret_val = 0;

    if (!node && !tree->root)
    {
        if (tree->size == 0) // new node is tree root then
        {
            tree->root = new_node;

            tree->size++;

            return ret_val;
        }
        else
        {
            ret_val = -1; // error code

            return ret_val;
        }
    }

    TreeNode * subtree_ptr = NULL;

    if (new_node_location == LEFT)
    {
        subtree_ptr = node->left;
        node->left  = new_node;
    }
    else if (new_node_location == RIGHT)
    {
        subtree_ptr = node->right;
        node->right = new_node;
    }
    else if (new_node_location == REPLACE)
    {
        subtree_ptr = node->left;
        new_node->left = node->left;
        new_node->right = node->right;

        *node = *new_node;
    }

    if (new_node_location == REPLACE)
    {
        // do nothing
    }
    else if (subtree_location == LEFT)
    {
        new_node->left = subtree_ptr;
    }
    else if (subtree_location == RIGHT)
    {
        new_node->right = subtree_ptr;
    }
    else if (subtree_location == REPLACE) // we forbid such fucntionality
    {
        fprintf(stderr, "Forbidden to hang subtree onto intself. Choose LEFT or RIGHT\n");

        ret_val = 1;
    }

    tree->size++;

    return ret_val;
}

int TraverseTreeFrom (Tree * tree, TreeNode * node, NodeAction_t NodeAction, TraverseOrder traverse_order)
{
    assert(tree);

    if (!node)
    {
        return 0;
    }

    int ret_val = 0;

    if (traverse_order == PREORDER)
    {
        ret_val = NodeAction(node);
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
    }
    else if (traverse_order == INORDER)
    {
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        ret_val = NodeAction(node);
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
    }
    else if (traverse_order == POSTORDER)
    {
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
        ret_val = NodeAction(node);
    }
    else
    {
        fprintf(stderr, "Wrong traversal order: %d\n", traverse_order);

        return 1;
    }

    return ret_val;
}

int TraverseTree (Tree * tree, NodeAction_t NodeAction, TraverseOrder traverse_order)
{
    assert(tree);

    return TraverseTreeFrom(tree, tree->root, NodeAction, traverse_order);
}

int WriteSubtree (FILE * stream, const TreeNode * node, TraverseOrder traverse_order) // compatible with NodePrinter_t
{
    if (node == NULL)
    {
        fprintf(stream, "* "); // todo nil

        return 0;
    }

    int ret_val = 0;

    fprintf(stream, "( ");

    if (traverse_order == PREORDER)
    {
        ret_val = fprintf(stream, "\"%s\" ", node->data); // did not test
        WriteSubtree(stream, node->left, traverse_order);
        WriteSubtree(stream, node->right, traverse_order);
    }
    else if (traverse_order == INORDER)
    {
        WriteSubtree(stream, node->left, traverse_order);
        ret_val = fprintf(stream, "\"%s\" ", node->data); // did not test
        WriteSubtree(stream, node->right, traverse_order);
    }
    else if (traverse_order == POSTORDER)
    {
        WriteSubtree(stream, node->left, traverse_order);
        WriteSubtree(stream, node->right, traverse_order);
        ret_val = fprintf(stream, "\"%s\" ", node->data); // did not test
    }
    else
    {
        fprintf(stream, "ErrOrdr");

        ret_val = -1;
    }

    fprintf(stream, ") ");

    return ret_val;
}

int WriteTree (FILE * stream, const Tree * tree, TraverseOrder traverse_order)
{
    assert(tree);

    int ret_val = WriteSubtree(stream, tree->root, traverse_order);

    fprintf(stream, "\n");

    return ret_val;
}

TreeNode * ReadSubtree (FILE * stream)
{
    assert(stream);

    int symb = 0;

    while (isspace(symb = fgetc(stream)))
    {
        ;
    }

    if (symb == '*')
    {
        return NULL;
    }
    else if (symb != '(')
    {
        fprintf(stderr, "ReadSubtree: unknown action symbol %c (%d)\n", symb, symb);

        abort();
    }

    // symb = (

    TreeNode * node = TreeNodeCtor(ReadNodeData(stream));

    // stream - right after closing "node_data"

    node->left  = ReadSubtree(stream);
    node->right = ReadSubtree(stream);

    while ((symb = fgetc(stream)) != ')')
    {
        ;
    }

    return node;
}

char * ReadNodeData(FILE * stream)
{
    assert(stream);

    char symb = 0;

    while (isspace(symb = fgetc(stream)))
    {
        ;
    }

    if (symb != '"')
    {
        fprintf(stderr, "ReadNodeData: data has wrong format (missing quotation mark)\n");

        abort();
    }

    char * node_data = (char *) calloc (MAX_WORDS, MAX_WORD * sizeof(char));

    symb = fgetc(stream);

    while (symb != '"')
    {
        strcat(node_data, &symb); // ? crutch?

        symb = fgetc(stream);
    }

    if (symb != '"')
    {
        fprintf(stderr, "ReadNodeData: missing closing quotation mark\n");

        //? abort?
    }

    return node_data;
}

Tree ReadTree (FILE * stream)
{
    assert(stream);

    return TreeCtor(ReadSubtree(stream));
}

int PrintfDebug (const char * funcname, int line, const char * filename, const char * format, ...)
{
    assert(format);

    fprintf(stderr, BLACK_CLR "[DEBUG MESSAGE %s %d %s]\n<< ", funcname, line, filename);

    va_list ptr;

    va_start(ptr, format);

    int res = vfprintf(stderr, format, ptr);

    va_end(ptr);

    fprintf(stdout, "\n " RST_CLR);

    return res;
}
