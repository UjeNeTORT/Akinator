/*************************************************************************
 * (c) 2023 Tikhonov Yaroslav (aka UjeNeTORT)
 *
 * email: tikhonovty@gmail.com
 * telegram: https://t.me/netortofficial
 * GitHub repo: https://github.com/UjeNeTORT
 *************************************************************************/

#include <stdio.h>
#include <string.h>

#include "akinator.h"

#define streq(s1, s2) (!strcmp((s1), (s2)))

int main()
{
    fprintf(stdout, "Hello! What do you want from me? [guess (g) | define (d) | compare (c) | call you a clown ()]\n"
                    "BE QUICK OR I LL DESTROY YOUR COMPUTER!\n");

    FILE * user_stream = stdin;
    char * prog_mode   = NULL;
    fscanf(user_stream, "%s", prog_mode);

    if (streq(prog_mode, "g") || streq(prog_mode, "guess"))
    {
        // specify tree to work with
        // guess
        // save or not to save, thats the question
    }
    else if (streq(prog_mode, "d") || streq(prog_mode, "define"))
    {
        ;
    }
    else if (streq(prog_mode, "c") || streq(prog_mode, "compare"))
    {
        ;
    }
    else
    {
        fprintf(stdout, "Incorrect input \"%s\" (You ugly *jojo music*)\n", prog_mode);
    }

    return 0;
}
