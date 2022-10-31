#ifndef _MATHEVAL_H_
#define _MATHEVAL_H_

// Math expresion
typedef char * EXP;
typedef double * EVAL;

//Converts a infix expresion to postfix using Shunting Yard Algorithm, stack and queue, also evaluates the expresion using stack
EXP postFix();
EVAL postfixEval(EXP);





#endif /* _MATHEVAL_H_ */
