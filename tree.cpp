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

int TreeAddNodeAfter (Tree * tree, TreeNode * node, TreeNode * new_node, NodeCmp_t Comparator)
{
    assert(tree);
    assert(new_node);

    int ret_val = 0;

    if (!node && !tree->root && tree->size == 0) // new node is tree root then
    {
        tree->root = new_node;

        tree->size++;

        return ret_val;
    }

    int cmp_res = Comparator(new_node, node);

    if (cmp_res <= 0)
    {
        if (node->left)
        {
            ret_val = TreeAddNodeAfter(tree, node->left, new_node, Comparator);
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
            ret_val = TreeAddNodeAfter(tree, node->right, new_node, Comparator);
        }
        else
        {
            node->right = new_node;
        }
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

    // assert(node->tree == tree);

    int ret_val = 0;

    if (traverse_order == PREORDER)
    {
        ret_val = NodeAction(node); // did not test what it does
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
    }
    else if (traverse_order == INORDER)
    {
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        ret_val = NodeAction(node); // did not test what it does
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
    }
    else if (traverse_order == POSTORDER)
    {
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
        ret_val = NodeAction(node); // did not test what it does
    }
    else
    {
        return 1;
    }

    return ret_val;
}

int PrintfNode (Tree * tree, TreeNode * node)
{
    assert(tree);
    assert(node);

    int ret_val = 0;

    if (node->left || node->right)
    {
        ret_val = fprintf(stdout, "CONDITION NODE: %d\n", node->data);
    }
    else
    {
        ret_val = fprintf(stdout, "LEAF NODE: %d\n", node->data);
    }

    return ret_val;
}

int PrintfTree (Tree * tree)
{
    assert(tree);


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
