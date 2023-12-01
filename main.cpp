/*************************************************************************
 * (c) 2023 Tikhonov Yaroslav (aka UjeNeTORT)
 *
 * email: tikhonovty@gmail.com
 * telegram: https://t.me/netortofficial
 * GitHub:   https://github.com/UjeNeTORT
 * repo:     https://github.com/UjeNeTORT/Tree
 *************************************************************************/

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "akinator/akinator.h"
#include "colors.h"

const int MAX_PROGMODE_LEN = 15;
const int MAX_TREEPATH_LEN = 100;

const char * TREE_DATABASE = "akinator/database/";

#define streq(s1, s2) (!strcmp((s1), (s2)))

int DoGuessMode(Tree * tree, const char * tree_path, FILE * user_stream);
int DoDefineMode(Tree * tree, FILE * user_stream);
int DoCompareMode(Tree * tree, FILE * user_stream);

stack * BuildDefinitionStack (Tree * tree, char * term);

static int DelExtraBlanks (char * string);

int main()
{
    fprintf(stdout, "\n"
                    "# Akinator by UjeNeTort\n"
                    "# TIKHONOV YAROSLAV 2023\n\n");

    FILE * user_stream = stdin;

    char tree_path[MAX_TREEPATH_LEN] = "";
    fprintf(stdout, "Hello! Specify tree to work with\n>> ");
    fscanf(user_stream, "%s", tree_path);
    // todo check if tree path is correct
    Tree tree = ReadGuessTree(tree_path);

    char prog_mode[MAX_PROGMODE_LEN] = "";

    while (true)
    {
        fprintf(stdout, "What do you want from me? [guess (g) | define (d) | compare (c) | show (s) | quit (q) | call you a clown ()]\n>> ");
        fscanf(user_stream, "%s", prog_mode);
        fgetc(user_stream); // hanging \n

        if (streq(prog_mode, "g") || streq(prog_mode, "guess"))
        {
            fprintf(stdout, "ATTENTION! To quit type in \"q\" instead of killing terminal\n"
                            "Enjoy!\n");
            DoGuessMode(&tree, tree_path, user_stream);
        }
        else if (streq(prog_mode, "d") || streq(prog_mode, "define"))
        {
            DoDefineMode(&tree, user_stream);
        }
        else if (streq(prog_mode, "c") || streq(prog_mode, "compare"))
        {
            DoCompareMode(&tree, user_stream);
        }
        else if (streq(prog_mode, "s") || streq(prog_mode, "show"))
        {
            DrawGuessTree("dump.html", &tree);
        }
        else if (streq(prog_mode, "q") || streq(prog_mode, "quit"))
        {
            fprintf(stdout, "Quitting...\n");

            break;
        }
        else
        {
            fprintf(stdout, "Incorrect input \"%s\" (You ugly *jojo music*)\n", prog_mode);
        }
    }
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

int DoCompareMode(Tree * tree, FILE * user_stream)
{
    assert(tree);
    assert(user_stream);

    char first[MAX_WORD] = "";
    fprintf(stdout, "First term?\n>> ");
    fgets(first, MAX_WORD, user_stream);
    first[strcspn(first, "\r\n")] = 0;
    DelExtraBlanks(first);

    char second[MAX_WORD] = "";
    fprintf(stdout, "Second term?\n>> ");
    fgets(second, MAX_WORD, user_stream);
    second[strcspn(second, "\r\n")] = 0;
    DelExtraBlanks(second);

    stack * first_path  = BuildDefinitionStack (tree, first);
    stack * second_path = BuildDefinitionStack (tree, second);

    int turn = 0;

    char ** similarities = (char **) calloc (MAX_TREE_PATH, sizeof(char *));
    char ** similarities_init = similarities;

    TreeNode * difference = tree->root;

    fprintf(stdout, "Both %s and %s have properties:\n", first, second);
    while ((turn = PopStack(first_path)) == PopStack(second_path))
    {
        *similarities++ = difference->data;

        if (turn == 0)
        {
            fprintf(stdout, "\tnot %s\n", difference->data);
            difference = difference->left;
        }
        else
        {
            fprintf(stdout, "\t%s\n", difference->data);
            difference = difference->right;
        }
    }

    similarities = similarities_init;

    while (*similarities)
    {
        similarities++;
    }

    fprintf(stdout, "But %s has following properties:\n", first);
    AkinatorSubtreeDefine(difference, first);

    fprintf(stdout, "Whereas %s has following properties:\n", second);
    AkinatorSubtreeDefine(difference, second);

    free(similarities_init);

    DtorStack(first_path);
    DtorStack(second_path);

    return 0;
}

stack * BuildDefinitionStack (Tree * tree, char * term)
{
    TreeNode * dst_node = TreeFind(tree, term);
    if (!dst_node)
    {
        fprintf(stdout, "No such term in tree (%s not found)\n", term);

        return NULL; // not found
    }

    stack * path = TreeNodePath(tree, dst_node);
    stack * back_path = CtorStack(path->size); //? seems like crutch
    while (path->size > 0)
    {
        PushStack(back_path, PopStack(path));
    }

    DtorStack(path);

    return back_path;
}

// delete extra spaces in the end
static int DelExtraBlanks (char * string)
{
    assert(string);
    assert(*string);

    // also assume that in the beginning of the string there are no extra blanks
    while (*string) string++;
    int deleted = 0;
    string--;

    while (isblank(*string))
    {
        *string = 0;
        string--;
        deleted++;
    }

    return deleted;
}
