#ifndef TREE_H
#define TREE_H

#include <stdio.h>

#define PRINTF_DEBUG(format, ...) \
    PrintfDebug (__PRETTY_FUNCTION__, __LINE__, __FILE__, format, __VA_ARGS__)

typedef int elem_t;

typedef enum
{
    PREORDER  = -1,
    INORDER   = 0,
    POSTORDER = 1,
} TraverseOrder;

struct TreeNode
{
    elem_t val;

    TreeNode * left;
    TreeNode * right;
};

struct Tree
{
    TreeNode * root;

    int height;
    int size;
};

typedef int (* NodeAction_t(TreeNode * node));

TreeNode* TreeNodeCtor (Tree * tree, elem_t val);
elem_t    TreeNodeDtor (Tree * tree, TreeNode * node);

Tree*     TreeCtor     ();
int       TreeDtor     (Tree * tree);

int       TraverseTree     (Tree * tree, NodeAction_t NodeAction, TraverseOrder traverse_order);
int       TraverseTreeFrom (Tree * tree, TreeNode * node, NodeAction_t NodeAction, TraverseOrder traverse_order);

int       PrintfDebug (const char * funcname, int line, const char * filename, const char * format, ...) __attribute__( (format(printf, 4, 5)) );

#endif // TREE_H
