#ifndef TREE_H
#define TREE_H

#include <stdio.h>

const int POISON   = 0xD00D1E;
const int MAX_WORD  = 100; // maximum length of a word allowed
const int MAX_WORDS = 100; // maximum words allowed to get stored in data

#define PRINTF_DEBUG(format, ...) \
    PrintfDebug (__PRETTY_FUNCTION__, __LINE__, __FILE__, format __VA_OPT__(,) __VA_ARGS__)

typedef enum
{
    PREORDER  = -1,
    INORDER   = 0,
    POSTORDER = 1,
} TraverseOrder;

typedef enum
{
    LEFT    = -1,
    REPLACE = 0,
    RIGHT   = 1,
} NodeLocation;

typedef char * elem_t;

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
int       TreeNodeDtor (TreeNode * node);

Tree      TreeCtor     (TreeNode * root);
int       TreeDtor     (Tree * tree);

int       TreeHangLeafSorted (Tree * tree, TreeNode * node, TreeNode * new_node, NodeCmp_t comparator);

int       TreeHangNode (Tree * tree, TreeNode * node, TreeNode * new_node, NodeLocation new_node_location, NodeLocation subtree_location);

int       DeleteSubtree (Tree * tree, TreeNode * node);

int       TraverseTree     (Tree * tree, NodeAction_t NodeAction, TraverseOrder traverse_order);
int       TraverseTreeFrom (Tree * tree, TreeNode * node, NodeAction_t NodeAction, TraverseOrder traverse_order);

int WriteTree    (FILE * stream, Tree * tree, TraverseOrder traverse_order);
int WriteSubtree (FILE * stream, TreeNode * node, TraverseOrder traverse_order);
int NewWriteSubtree (FILE * stream, TreeNode * node, TraverseOrder traverse_order);

TreeNode* ReadSubtree  (FILE * stream);
char*     ReadNodeData (FILE * stream);
Tree      ReadTree     (FILE * stream);

int       PrintfDebug (const char * funcname, int line, const char * filename, const char * format, ...) __attribute__( (format(printf, 4, 5)) );

#endif // TREE_H
