#ifndef _MATHEVAL_H_
#define _MATHEVAL_H_


#include <stdbool.h>
// Math expresion
typedef char * EXP;
typedef double * EVAL;

//Sacans and validates the input, also converts to postfix and evaluates
EVAL MathEval();
//Converts a infix expresion to postfix using Shunting Yard Algorithm, stack and queue
EXP postFix(EXP);
//Evaluates a postfix expresion using stack
EVAL postfixEval(EXP);
//Returns true if balace is correct
bool parenthesisBalance(EXP );
//Returns true if no invalid characters are found
bool invalidCharacters(EXP );
//Checks the balance of numbers on each operator
bool operandsBalance(EXP );
//Checks the balance of operators between numbers
bool operatorsBalance(EXP);





#endif /* _MATHEVAL_H_ */
