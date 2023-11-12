#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "tree.h"

TreeNode* TreeNodeCtor (Tree * tree, elem_t val)
{
    assert(tree);

    TreeNode * new_node = (TreeNode *) calloc(1, sizeof(TreeNode));

    // new_node->tree  = tree;
    new_node->val   = val;
    new_node->left  = NULL;
    new_node->right = NULL;

    return new_node;
}

elem_t TreeNodeDtor (Tree * tree, TreeNode * node)
{
    assert(tree);
    assert(node);
    // assert(node->tree == tree);

    elem_t val = node->val;

    node->val   = NULL;
    node->left  = NULL;
    node->right = NULL;
    // node->tree  = NULL;

    free(node);

    return val;
}

Tree* TreeCtor ()
{
    Tree * tree = (Tree *) calloc(1, sizeof(Tree));

    TreeNode * root = TreeNodeCtor(tree, NULL);

    tree->height = 1;
    tree->size   = 1;

    return tree;
}

//! not finished
int TreeDtor (Tree * tree)
{
    assert(tree);

    // traverse through the tree and free each node

    return 0;
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
        ret_val = *NodeAction(node); // not tested what it does
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
    }
    else if (traverse_order == INORDER)
    {
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        ret_val = *NodeAction(node); // not tested what it does
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
    }
    else if (traverse_order == POSTORDER)
    {
        TraverseTreeFrom(tree, node->left, NodeAction, traverse_order);
        TraverseTreeFrom(tree, node->right, NodeAction, traverse_order);
        ret_val = *NodeAction(node); // not tested what it does
    }
    else
    {
        return 1;
    }

    return ret_val;
}

int PrintfDebug (const char * funcname, int line, const char * filename, const char * format, ...)
{
    assert(format);

    fprintf(stderr, "[DEBUG MESSAGE %s %d %s]\n", funcname, line, filename);

    va_list ptr;

    va_start(ptr, format);

    int res = vfprintf(stderr, format, ptr);

    va_end(ptr);

    return res;
}
