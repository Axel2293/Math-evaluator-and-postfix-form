#include "MathEval.h"
#include "Contenedores/containers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    system("clear");
    char *exp={"2 + 3 * 5 / 2 - 1"};

    //exp=cleanSpaces(exp);
    printf("InFix: %s\n", exp);

    if(parenthesisBalance(exp) && invalidCharacters(exp) && operandsBalance(exp))
    {
        EXP postfix=postFix(exp);
        printf("PostFix: %s\n", postfix);
        double * eval=postfixEval(postfix);
        printf("Evaluation: %f\n", *eval);
    }




}

//Returns the len including the null character and excluding spaces
size_t strLen(EXP expresion)
{
    int i=0;
    size_t len=0;
    while (expresion[i]!='\0')
    {
        if(expresion[i]!=' ')
        {
            len++;
            i++;
        }
        else
        {
            i++;
        }
    }
    return len+1;
}

EXP cleanSpaces(EXP expresion)
{
    
    size_t len=strLen(expresion);
    EXP newEXP=calloc(len, sizeof(char));
    newEXP[len]='\0';
    int i=0, y=0;
    while (expresion[i]!= '\0')
    {
        if(expresion[i]!=' ')
        {
            newEXP[y]=expresion[i];
            i++;
            y++;
        }
        else
        {
            i++;
        }
    }
    return newEXP;
   
    
}

EXP charCreate(char c)
{
    EXP ptr=malloc(sizeof(char));
    *ptr=c;
    return ptr;
}

double *doubleCreate(double d)
{
    double * ptr=malloc(sizeof(double));
    *ptr=d;
    return ptr;
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
            stack_push(stk, (EXP) &expresion[i]);
        }
        else if(expresion[i]==')' || expresion[i]==']')
        {
            if (stack_pop(stk) == NULL)
            {
                return false;
            }
        }
        i++;
    }

    if(stack_isEmpty(stk))
    {
        return true;
    }
    else
    {
        return false;
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
    int i=0;
    while (expresion[i]!='\0')
    {
        // Found +,-,/,*
        if(expresion[i]==43 || expresion[i]==42 || expresion[i]==45 || expresion[i]==47)
        {
            //Check sides
            if(expresion[i-1]=='(' || expresion[i+1] == ')' || expresion[i+1]=='\0' || i==0)
            {
                return false;
            }
        }
        i++;
    }

    return true;
}


EXP postFix(EXP expresion)
{
    Stack stk=stack_create();
    EXP result=calloc(1000, sizeof(char));

    int i=0, newPos=0;
    while(expresion[i]!='\0')
    {
        //printf("\n[%d]\n", i);
        
        //Search for operand (1,2,3,4,5,6,7,8,9) and output it
        if(expresion[i]>='0' && expresion[i]<='9')
        {
            //printf("Operand Found: ");
            //printf("%c",expresion[i]);
            result[newPos]=expresion[i];
            newPos++;
            
        }
        else if(expresion[i]=='(')
        {
            stack_push(stk, (DATA) charCreate(expresion[i]));
        }
        else if(expresion[i]=='+' || expresion[i]=='-')
        {
            //printf("\nOperator found[+,-]\n");
            EXP dt= (EXP) stack_top(stk);
            if(dt!=NULL){
                if(*dt=='*' || *dt=='/')
                {
                    //printf("Found more high opt: \n");
                    dt=stack_pop(stk);
                    //printf("%c", *dt);
                    result[newPos]=*dt;
                    newPos++;
                    while (*dt != '(')
                    {
                        dt= (EXP) stack_top(stk);
                        if(dt!=NULL){
                            if(*dt=='(')
                            {
                                dt=stack_pop(stk);
                                break;
                            }
                            else
                            {
                                dt=stack_pop(stk);
                                //printf("%c", *dt);
                                result[newPos]=*dt;
                                newPos++;

                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                    stack_push(stk, (DATA) charCreate(expresion[i]));
                    
                }
                else
                {
                    //printf("Adding opt to stack [%c]", expresion[i]);
                    stack_push(stk, (DATA) charCreate(expresion[i]));
                }
            }
            else
            {
                //printf("Adding opt to stack [%c]", expresion[i]);
                stack_push(stk, (DATA) charCreate(expresion[i]));
            }
        }
        else if(expresion[i]=='*' || expresion[i]=='/')
        {
            //printf("\nOperator found[/,*]\n");
            EXP dt=(EXP) stack_top(stk);
            if(dt!=NULL){
                if (*dt=='*' || *dt=='/')
                {
                    //printf("Same level opt found, swaping\n");
                    stack_pop(stk);
                    result[newPos]=*dt;
                    newPos++;
                    stack_push(stk, charCreate(expresion[i]));
                }
                else
                {
                    //printf("Adding opt to stack [%c]\n", expresion[i]);
                    stack_push(stk, (DATA) charCreate(expresion[i]));
                }
            }
            else
            {
                //printf("Adding opt to stack [%c]\n", expresion[i]);
                stack_push(stk, (DATA) charCreate(expresion[i]));
                //print_stack(stk);
            }
        }
        else if (expresion[i]==')')
        {
            EXP dt=(EXP) stack_top(stk);
            while (!stack_isEmpty(stk))
            {
                dt= (EXP)stack_top(stk);
                if(*dt == '(')
                {
                    dt=stack_pop(stk);
                    //print_stack(stk);
                    break;
                }
                else
                {
                    dt=(EXP) stack_pop(stk);
                    //printf("%c\n", *dt);
                    result[newPos]=*dt;
                    newPos++;
                    //print_stack(stk);
                }
            }
            
        }
        else
        {
            EXP c=charCreate(expresion[i]);
            result[newPos]=*c;
            newPos++;
        }
        i++;
    }

    EXP res=NULL;
    while (stack_isEmpty(stk)==false)
    {
        res=stack_pop(stk);
        if(*res!='(')
        {
            //printf("%c", *res);
            result[newPos]=*res;
            newPos++;
        }
    }
    newPos++;
    result[newPos]='\0';
    
    return result;
    
}

EVAL postfixEval(EXP postfix)
{
    int i=0;
    Stack stk=stack_create();
    //Gracias a GeeksForGeeks, estabamos perdidisimos en esto y su explicacion nos ayudo a entender el como crear el numero de mas de un digito
    while (postfix[i]!='\0')
    {

        if(isdigit(postfix[i]))
        {
            double number=0;
            while (isdigit(postfix[i]))
            {
                //Esto no se nos hubiera ocurrido la verdad :p
                number = number*10 + (double)(postfix[i]- '0');
                i++;
            }
            i--;
            stack_push(stk, doubleCreate(number));
        }
        else if(postfix[i]== '+' || postfix[i]== '-' || postfix[i]== '*' || postfix[i]== '/')
        {
            double *val1= (double *)stack_pop(stk);
            double *val2= (double *)stack_pop(stk);

            switch (postfix[i])
            {
            case '+':
                stack_push(stk, doubleCreate((*val2 + *val1)));
                break;
            case '-':
                stack_push(stk, doubleCreate((*val2 - *val1)));
                break;
            case '*':
                stack_push(stk, doubleCreate((*val2 * *val1)));
                break;
            case '/':
                stack_push(stk, doubleCreate((*val2 / *val1)));
                break;
            default:
                break;
            }
        }
        i++;
    }
    return (double *)stack_pop(stk);
}
