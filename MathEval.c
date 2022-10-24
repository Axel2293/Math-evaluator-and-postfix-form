#include "MathEval.h"
#include "Contenedores/containers.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char *exp={"2+(3*4))"};
    printf("%s\n", exp);

    if(parenthesisBalance(exp)==true)
    {
        printf("Parentesis balanceados\n");
    }
    else
    {
        printf("Parentesis no balanceados\n");
    }





}


int strLen(EXP expresion)
{
    int i=0;
    while (expresion[i]!='\0')
    {
        i++;
    }
    return i;
}


//Returns true if balace is correct
bool parenthesisBalance(EXP expresion)
{
    Stack stk=stack_create();

    int i=0;
    while(expresion[i]!='\0')
    {
        if(expresion[i]=='(' || expresion[i]=='[')
        {
            stack_push(stk, (EXP) expresion[i]);
        }
        else if(expresion[i]==')' || expresion[i]==']')
        {
            if (stack_pop(stk) == NULL)
            {
                i=-1;
                break;
            }
        }
        i++;
    }
    if(i==-1)
    {
        return false;
    }
    else
    {
        return true;
    }

}

//Returns true if no invalid characters are found
bool invalidCharacters(EXP expresion)
{
    int i=0;
    while (expresion[i]!='\0')
    {
        if(expresion[i]>=65 && expresion[i]<=122)
        {
            printf("Caracter no soportado;[%c] recuerda no usar variables(x,y,z,....)\n", expresion[i]);
            i=-1;
            return false;
        }
        i++;
    }
    if(i!=-1)
    {
        return true;
    }
    
}
bool operandsBalance(EXP expresion)
{
    printf("HELLO");
}





//Conversion de Infijo a Postfijo
void infToPost(EXP expresion){
    Stack stk = stack_create();

    //Algoritmo para la conversion

}