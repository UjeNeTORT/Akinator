/*************************************************************************
 * (c) 2023 Tikhonov Yaroslav (aka UjeNeTORT)
 *
 * email: tikhonovty@gmail.com
 * telegram: https://t.me/netortofficial
 * GitHub repo: https://github.com/UjeNeTORT
 *************************************************************************/

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "akinator/akinator.h"
#include "colors.h"

const int MAX_PROGMODE_LEN = 15;
const int MAX_TREEPATH_LEN = 100;

#define streq(s1, s2) (!strcmp((s1), (s2)))

int DoGuessMode(Tree * tree, const char * tree_path, FILE * user_stream);
int DoDefineMode(Tree * tree, FILE * user_stream);

int main()
{
    FILE * user_stream = stdin;

    char tree_path[MAX_TREEPATH_LEN] = "";
    fprintf(stdout, "Hello! Specify tree to work with\n>> ");
    fscanf(user_stream, "%s", tree_path);
    // todo check if tree path is correct
    Tree tree = ReadGuessTree(tree_path);

    fprintf(stdout, "What do you want from me? [guess (g) | define (d) | compare (c) | call you a clown ()]\n>> ");

    char prog_mode[MAX_PROGMODE_LEN] = "";
    fscanf(user_stream, "%s", prog_mode);
    fgetc(user_stream); // hanging \n

    if (streq(prog_mode, "g") || streq(prog_mode, "guess"))
    {
        DoGuessMode(&tree, tree_path, user_stream);
    }
    else if (streq(prog_mode, "d") || streq(prog_mode, "define"))
    {
        DoDefineMode(&tree, user_stream);
    }
    else if (streq(prog_mode, "c") || streq(prog_mode, "compare"))
    {
        ;
    }
    else
    {
        fprintf(stdout, "Incorrect input \"%s\" (You ugly *jojo music*)\n", prog_mode);
    }

    DrawGuessTree("dump.html", &tree);

    TreeDtor(&tree);

    fprintf(stdout, "Goodbye!\n");

    return 0;
}

int DoGuessMode(Tree * tree, const char * tree_path, FILE * user_stream)
{
    int tree_changed = 0;
    int ret_val = 0;
    while ((ret_val = AkinatorTreeGuess(tree, user_stream)) != 2)
    {
        tree_changed += ret_val;
    }

    if (!tree_changed)
    {
        return 0;
    }

    char save_tree[4] = "";
    fprintf(stdout, "Save changes? [y|n]\n>> ");
    fscanf(user_stream, "%c", save_tree);

    if (streq(save_tree, "y") || streq(save_tree, "yes"))
    {
        WriteGuessTree((const char *) tree_path, tree);

        fprintf(stdout, "Tree saved at %s\n", tree_path);
    }
    else if (!streq(save_tree, "n") && !streq(save_tree, "no"))
    {
        fprintf(stderr, "SaveTree or not, should be y or n\n");

        return 1;
    }

    return 0;
}

int DoDefineMode(Tree * tree, FILE * user_stream)
{
    char term[MAX_WORD] = "";
    fprintf(stdout, "What to define?\n>> ");
    fgets(term, MAX_WORD, user_stream);
    term[strcspn(term, "\r\n")] = 0;

    return AkinatorTreeDefine(tree, term);
}
