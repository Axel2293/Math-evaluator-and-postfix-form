#ifndef _MATHEVAL_H_
#define _MATHEVAL_H_


#include <stdbool.h>
// Math expresion
typedef char * EXP;
typedef double * EVAL;

//Converts a infix expresion to postfix using Shunting Yard Algorithm, stack and queue, also evaluates the expresion using stack
EVAL MathEval();
EXP postFix(EXP);
EVAL postfixEval(EXP);
bool parenthesisBalance(EXP );
bool invalidCharacters(EXP );
bool operandsBalance(EXP );
bool operatorsBalance(EXP);





#endif /* _MATHEVAL_H_ */
