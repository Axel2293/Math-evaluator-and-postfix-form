#include "MathEval.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("clear");

    EXP postfix=postFix();
    
    if (postfix!=NULL)
    {
        printf("\tPostfijo [%s]\n", postfix);
        EVAL result=postfixEval(postfix);
        printf("\tEvaluación: [%f]\n", *result);
    }

    return 0;
}