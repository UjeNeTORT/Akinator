#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "tree.h"

TreeNode* TreeNodeCtor (elem_t val)
{
    TreeNode * new_node = (TreeNode *) calloc(1, sizeof(TreeNode));

    new_node->data   = val;
    new_node->left  = NULL;
    new_node->right = NULL;

    return new_node;
}

elem_t TreeNodeDtor (Tree * tree, TreeNode * node)
{
    assert(tree);
    assert(node);

    elem_t val = node->data;

    node->data   = NULL;
    node->left  = NULL;
    node->right = NULL;

    free(node);

    return val;
}

Tree TreeCtor ()
{
    Tree tree = { NULL, 0 };

    return tree;
}

//! not finished
int TreeDtor (Tree * tree)
{
    assert(tree);

    // traverse through the tree and free each node


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
    }
    else
    {
        return -1; // error code
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
    }
    else
    {
        ret_val = -1;

        return ret_val; // error code
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
        PRINTF_DEBUG("Forbidden to hang subtree onto intself. Choose LEFT or RIGHT\n");

        ret_val = 1;
    }

    return ret_val;
}

int TraverseTreeFrom (Tree * tree, TreeNode * node, NodeAction_t NodeAction, TraverseOrder traverse_order)
{
    assert(tree);

    if (node == NULL)
    {
        return 0;
    }

    int ret_val = 0;

    if (traverse_order == PREORDER)
    {
        ret_val = NodeAction(node); // did not test
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
    }
    else if (traverse_order == INORDER)
    {
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        ret_val = NodeAction(node); // did not test
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
    }
    else if (traverse_order == POSTORDER)
    {
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
        ret_val = NodeAction(node); // did not test
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

int FprintfSubtree (FILE * stream, TreeNode * node, TraverseOrder traverse_order) // compatible with NodePrinter_t
{
    if (node == NULL)
    {
        fprintf(stream, "nil ");

        return 0;
    }

    int ret_val = 0;

    fprintf(stream, "( ");

    if (traverse_order == PREORDER)
    {
        ret_val = fprintf(stream, "%d ", node->data); // did not test

        fprintf(stream, ", ");

        FprintfSubtree(stream, node->left, traverse_order);

        fprintf(stream, ", ");

        FprintfSubtree(stream, node->right, traverse_order);
    }
    else if (traverse_order == INORDER)
    {
        FprintfSubtree(stream, node->left, traverse_order);

        fprintf(stream, ", ");

        ret_val = fprintf(stream, "%d ", node->data); // did not test

        fprintf(stream, ", ");

        FprintfSubtree(stream, node->right, traverse_order);
    }
    else if (traverse_order == POSTORDER)
    {
        FprintfSubtree(stream, node->left, traverse_order);

        fprintf(stream, ", ");

        FprintfSubtree(stream, node->right, traverse_order);

        fprintf(stream, ", ");

        ret_val = fprintf(stream, "%d ", node->data); // did not test
    }
    else
    {
        fprintf(stream, "ErrOrdr");

        ret_val = -1;
    }

    fprintf(stream, ") ");

    return ret_val;
}

int FprintfTree (FILE * stream, Tree * tree, TraverseOrder traverse_order)
{
    assert(tree);

    return FprintfSubtree(stream, tree->root, traverse_order);
}

int PrintfDebug (const char * funcname, int line, const char * filename, const char * format, ...)
{
    assert(format);

    fprintf(stderr, "[DEBUG MESSAGE %s %d %s]\n<< ", funcname, line, filename);

    va_list ptr;

    va_start(ptr, format);

    int res = vfprintf(stderr, format, ptr);

    va_end(ptr);

    fprintf(stdout, "\n");

    return res;
}
