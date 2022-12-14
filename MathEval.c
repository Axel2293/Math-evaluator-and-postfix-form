#include "MathEval.h"
#include "Contenedores/containers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>

EXP posfixCreate(Queue);
EXP postFix(EXP);
EVAL postfixEval(EXP);
EXP spacesBalance(EXP);
EXP scanInput();
EXP resizeStr(EXP , int );
bool parenthesisBalance(EXP );
bool invalidCharacters(EXP );
bool operandsBalance(EXP );
bool operatorsBalance(EXP);

EVAL MathEval()
{
    system("cls");
    printf("  __  __       _   _       ______          _             _             \n"
            " |  \\/  |     | | | |     |  ____|        | |           | |\n"            
            " | \\  / | __ _| |_| |__   | |____   ____ _| |_   _  __ _| |_ ___  _ __\n" 
            " | |\\/| |/ _` | __| '_ \\  |  __\\ \\ / / _` | | | | |/ _` | __/ _ \\| '__|\n"
            " | |  | | (_| | |_| | | | | |___\\ V / (_| | | |_| | (_| | || (_) | |\n"
            " |_|  |_|\\__,_|\\__|_| |_| |______\\_/ \\__,_|_|\\__,_|\\__,_|\\__\\___/|_|\n");
    printf("Ten en cuenta:\n\t-Balance de parentesis ('()' o '[]')\n\t-Balance de operadores (+,-,*,/)\n\t-Balance de operandos (Numeros enteros)\n");


    //Clean spaces for initial validations
    EXP exp=scanInput();
    //Verify operators balance before cleaning spaces
    if (!operatorsBalance(exp))
    {
        return NULL;
    }

    //Delete spaces of the user
    EXP new=malloc(sizeof(char));
    int k=0, indx=0;
    while (exp[k]!='\0')
    {
        if (exp[k]!=' ')
        {
            new[indx]=exp[k];
            indx++;
            new =resizeStr(new, indx);
        }
        k++;
    }
    new=resizeStr(new, indx);
    new[indx]='\0';
    exp=new;

    

    // validate invalid expresions (invalid characters, parenthesis balance, operands balance, operators balance)
    if (!parenthesisBalance(exp) || !invalidCharacters(exp) || !operandsBalance(exp) || !operatorsBalance(exp))
    {
        return NULL;
    }
    
    //Add spaces after and before operators so we can separete numbers of more than one digit
    EXP expresion=spacesBalance(exp);


    //COnverto to postfix
    EXP postfix=postFix(expresion);

    //Evaluate
     if (postfix!=NULL)
    {
        printf("\tPostfijo [%s]\n", postfix);
        EVAL result=postfixEval(postfix);
        printf("\tEvaluacion: [%f]\n", *result);
        return result;
    }

    return NULL;

}
//Scans the input of the user as a str
EXP scanInput()
{
    EXP inpt=NULL;
    size_t len=0;
    printf("Ingresa tu expresi??n matem??tica: \n");

    //Scans in blocks of 4 bytes from standard input> stdin
    getline(&inpt, &len, stdin);

    for (size_t i = 0; i <= len; i++)
    {
        if (inpt[i]=='\n')
        {
            //Cambie el espacio por finalizador de cadena
            //Casos como (1+2)* , 3/5+ ya los marca como erroneos
            inpt[i]='\0';
        }
        
    }

    return inpt;
}
//Returns true if balace is correct
bool parenthesisBalance(EXP expresion)
{
    Stack stk=stack_create(sizeof(char));

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
                printf("\nPar??ntesis no balanceados, expresion incorrecta\n");
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
        printf("\nPar??ntesis no balanceados, expresion incorrecta\n");
        return false;
    }

}
//Returns true if no invalid characters are found
bool invalidCharacters(EXP expresion)
{
    int i=0;
    while (expresion[i]!='\0')
    {
        if( (expresion[i]>='A' && expresion[i]<='Z') || (expresion[i]>='a' && expresion[i]<='z'))
        {
            printf("Caracter no soportado;[%c] recuerda no usar variables(x,y,z,....)\n", expresion[i]);
            return false;
        }
        i++;
    }
    return true;
    
}
//Chechs if given char is a valid operator
bool isoperator(char c)
{
    switch (c)
    {
        case '+':
                
        case '-':
                
        case '*':
                
        case '/':
            return true;
            break;
        default:
            return false;
            break;
    }
}
//Checks the balance of numbers on each operator
bool operandsBalance(EXP expresion)
{
    int i=0;
    while (expresion[i]!='\0')
    {
        // Found +,-,/,*
        if(expresion[i]==43 || expresion[i]==42 || expresion[i]==45 || expresion[i]==47)
        {
            //Check sides
            if(expresion[i-1]=='(' || expresion[i-1]=='['|| expresion[i+1] == ')' || expresion[i+1] == ']'|| expresion[i+1]=='\0' || i==0 || expresion[i+1]=='\0')
            {
                printf("Expresi??n no valida (operandos faltantes)\n");
                return false;
            }
            else if (isoperator(expresion[i+1]) == true)
            {
                printf("Expresi??n no valida (dos operadores juntos encontrados)\n");
                return false;
            }
            
            
        }
        

        i++;
    }

    return true;
}
//Checks the balance of operators between numbers
bool operatorsBalance(EXP exp)
{
    int i=0;
    while (exp[i]!='\0')
    {
        if (isdigit(exp[i]))
        {
            while (exp[i]!='\0')
            {
                if(exp[i]==' ')
                {
                    while (exp[i]!='\0')
                    {
                        if (isdigit(exp[i]))
                        {
                            printf("Expresi??n no v??lida (Falta de operador)\n");
                            return false;
                        }
                        i++;
                        
                    } 
                }
                i++;  
            } 
        }
        else
        {
            i++;
        }
    }
    return true;
    
}
//Spaces are fundamental for keeping a track of the numbers as they are digists and not variables
EXP spacesBalance(EXP posfix)
{
    Queue q1=queueCreate(sizeof(char));

    int i=0;
    char space=' ';
    while (posfix[i]!='\0')
    {
        if (posfix[i]== '+' || posfix[i]== '-' || posfix[i]== '*' || posfix[i]== '/' )
        {
            //Add space before operator
            if (posfix[i-1]!=' ')
            {
                enqueue(q1, &space);
            }

            //Add operator to queue
            enqueue(q1, &posfix[i]);

            //Add space after operator
            if (posfix[i+1]!=' ')
            {
                enqueue(q1, &space);
            }
            
            
        }
        else
        {
            enqueue(q1, &posfix[i]);
        }
        i++;
        
    }

    EXP new = posfixCreate(q1);
    return new;
    
}

short operatorDominance(char opt)
{
    switch (opt)
    {
    case '+':
        
    case '-':
        return 1;
    case '*':

    case '/':
        return 2;
    default:
        return 0;
    }
}
//Converts a infix expresion to postfix using Shunting Yard Algorithm, stack and queue
EXP postFix(EXP expresion)
{
    Stack stk=stack_create(sizeof(char));
    Queue qe=queueCreate(sizeof(char)); 
    EXP result=calloc(1000, sizeof(char));
    EXP temp=NULL;

    int i=0, newPos=0;
    while(expresion[i]!='\0')
    {   
        //Search for operand (1,2,3,4,5,6,7,8,9) and output it on the queue
        if(expresion[i]>='0' && expresion[i]<='9')
        {

            enqueue(qe, (DATA) &expresion[i]);
            
        }
        //Add ( to stack
        else if(expresion[i]=='(' || expresion[i]=='[')
        {
            stack_push(stk, (DATA) &expresion[i] );
        }
        //Operators
        else if (isoperator(expresion[i]))
        {
            while (!stack_isEmpty(stk))
            {
                temp= (EXP) stack_top(stk);
                //If '(' break the pops
                if (*temp=='(' || operatorDominance(expresion[i])>operatorDominance(*temp))
                {
                    break;
                }
                //If operator in stack has higher or same dominance, pop and add to queue
                else if (operatorDominance(expresion[i]) <= operatorDominance(*temp)  )
                {
                    temp = stack_pop(stk);
                    enqueue(qe, (DATA) temp);
                }
            }
            //Add operator to stack
            stack_push(stk, &expresion[i]);
            
        }
        //If closing parenthesis pop from stack and enqueue till it finds a closing parenthesis
        else if (expresion[i]==')' || expresion[i]==']')
        {
            EXP dt=(EXP) stack_top(stk);
            while (!stack_isEmpty(stk))
            {
                dt= (EXP)stack_top(stk);
                if(*dt == '(' || *dt == '[')
                {
                    dt=stack_pop(stk);
                    break;
                }
                else
                {
                    dt=(EXP) stack_pop(stk);
                    enqueue(qe, (DATA) dt);
                }
            }
            
        }
        //Add spaces and others that make it posible to track where the numbers end if they have more than one digit
        else
        {
            enqueue(qe, &expresion[i]);
        }
        i++;
    }

    // Add remaining characters in the stack to the queue
    EXP res=NULL;
    while (!stack_isEmpty(stk))
    {
        res= (EXP) stack_pop(stk);
        if(*res!='(')
        {
            enqueue(qe, res);
        }
    }

    //Transform the queue contaier to final expresion str and destroys the queue
    EXP queueres= posfixCreate(qe);
    
    //Destroy stack
    stack_destroy(stk);

    return queueres;
    
}
//Adds an aditional space on the string
EXP resizeStr(EXP old, int size)
{
    //Reserve space with one more space
    EXP new=malloc(sizeof(char)*(size+1));

    memcpy(new, old, size);
    free(old);
    return new;
}
//Evaluates a postfix expresion using stack
EVAL postfixEval(EXP postfix)
{
    int i=0;
    Stack stk=stack_create(sizeof(double));
    while (postfix[i]!='\0')
    {
        if(isdigit(postfix[i]))
        {
            
            //Construct the numbers with more than one digit, spaces are really important
            double number=0; 
            int index=0;

            char *temp=malloc(sizeof(char));

            while (isdigit(postfix[i]))
            {
                temp[index]=postfix[i]; 
                i++;
                index++;
                temp=resizeStr(temp, index);          
            }
            i--;
            temp=resizeStr(temp, index);
            temp[index+1]='\0';
            //Atoi takes a string of digits and turns it into a usable int number
            number=atoi(temp);
            
            stack_push(stk, &number);
        }
        // If operator found then pop two numbers from the stack and operate
        else if(postfix[i]== '+' || postfix[i]== '-' || postfix[i]== '*' || postfix[i]== '/')
        {
            //Pop two numbers of the stack
            double result=0;
            double *val1= (double *)stack_pop(stk);
            double *val2= (double *)stack_pop(stk);
            //Operate and push the result back to stack
            switch (postfix[i])
            {
            case '+':
                result=*val2 + *val1;
                stack_push(stk, &result);
                break;
            case '-':
                result=*val2 - *val1;
                stack_push(stk, &result);
                break;
            case '*':
                result=*val2 * *val1;
                stack_push(stk, &result);
                break;
            case '/':
                result=*val2 / *val1;
                stack_push(stk, &result);
                break;
            default:
                break;
            }
        }
        i++;
    }
    EVAL result=stack_pop(stk);
    stack_destroy(stk);
    return result;
}
// Takes the queue and constructs the final expresion on an string of the exact size
EXP posfixCreate(Queue q1)
{
    
    int size=queueSize(q1), indx=0;
    char * new=calloc(size+1, sizeof(char));
    char *add=NULL;
    while (!queueEmpty(q1))
    {
        add= (char *) dequeue(q1);
        new[indx]=*add;
        indx++;
    }
    new[indx+1]='\0';
    queueDestroy(q1);
    return new;
    
}