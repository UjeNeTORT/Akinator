/*************************************************************************
 * (c) 2023 Tikhonov Yaroslav (aka UjeNeTORT)
 *
 * email: tikhonovty@gmail.com
 * telegram: https://t.me/netortofficial
 * GitHub repo: https://github.com/UjeNeTORT
 *************************************************************************/

#ifndef AKINATOR_H
#define AKINATOR_H

#include "../tree/tree.h"
#include "../tree_dump/tree_dump.h"

const int MAX_YES_NO = 4;

Tree ReadGuessTree  (const char * tree_path);
int  WriteGuessTree (const char * tree_path, const Tree * tree);
int  DrawGuessTree  (const char * fname, const Tree * tree);

int AkinatorSubtreeGuess (TreeNode * node, TreeNode * previous, FILE * user_stream);
int AkinatorTreeGuess (Tree * tree, FILE * user_stream);

int AkinatorSubtreeDefine (TreeNode * node, char * term);
int AkinatorTreeDefine (Tree * tree, char * term);


#endif // AKINATOR_H
