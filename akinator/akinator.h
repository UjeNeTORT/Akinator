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

Tree ReadGuessTree  (const char * tree_filename);
int  WriteGuessTree (const char * tree_path, const Tree * tree);
int  DrawGuessTree  (const char * fname, const Tree * tree);

#endif // AKINATOR_H
