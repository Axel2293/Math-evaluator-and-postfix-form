#include "MathEval.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main()
{
    system("cls");

    EXP postfix=postFix();
    
    if (postfix!=NULL)
    {
        printf("\tPostfijo [%s]\n", postfix);
        EVAL result=postfixEval(postfix);
        printf("\tEvaluacion: [%f]\n", *result);
    }

    return 0;
}