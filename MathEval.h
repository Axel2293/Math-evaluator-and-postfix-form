#ifndef _MATHEVAL_H_
#define _MATHEVAL_H_

#include <stdbool.h>

// Math expresion
typedef char * EXP;
typedef double * EVAL;


EXP cleanSpaces(EXP);
bool parenthesisBalance(EXP expresion);
bool invalidCharacters(EXP expresion);
bool operandsBalance(EXP expresion);

EXP postFix(EXP);
EVAL postfixEval(EXP);





#endif /* _MATHEVAL_H_ */
