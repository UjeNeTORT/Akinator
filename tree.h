#ifndef TREE_H
#define TREE_H

#include <stdio.h>

const int POISON = 0xD00D1E;

#define PRINTF_DEBUG(format, ...) \
    PrintfDebug (__PRETTY_FUNCTION__, __LINE__, __FILE__, format __VA_OPT__(,) __VA_ARGS__)


typedef enum
{
    PREORDER  = -1,
    INORDER   = 0,
    POSTORDER = 1,
} TraverseOrder;

typedef int elem_t;

struct TreeNode
{
    elem_t data;

    TreeNode * left;
    TreeNode * right;
};

struct Tree
{
    TreeNode * root;

    int size;
};

typedef int (* NodeAction_t) (TreeNode * node);
typedef int (* NodePrinter_t) (FILE * stream, TreeNode * node, TraverseOrder traverse_order);

typedef int (* NodeCmp_t) (TreeNode * node1, TreeNode * node2);

TreeNode* TreeNodeCtor (elem_t val);
elem_t    TreeNodeDtor (Tree * tree, TreeNode * node);

Tree      TreeCtor     ();
int       TreeDtor     (Tree * tree);

int       TreeHangLeafSorted (Tree * tree, TreeNode * node, TreeNode * new_node, NodeCmp_t comparator);


int       TraverseTree     (Tree * tree, NodeAction_t NodeAction, TraverseOrder traverse_order);
int       TraverseTreeFrom (Tree * tree, TreeNode * node, NodeAction_t NodeAction, TraverseOrder traverse_order);

int FprintfTree    (FILE * stream, Tree * tree, TraverseOrder traverse_order);
int FprintfSubtree (FILE * stream, TreeNode * node, TraverseOrder traverse_order);


elem_t    PrintfDebug (const char * funcname, int line, const char * filename, const char * format, ...) __attribute__( (format(printf, 4, 5)) );

#endif // TREE_H
