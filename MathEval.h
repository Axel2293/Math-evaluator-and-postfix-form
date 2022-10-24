#ifndef _MATHEVAL_H_
#define _MATHEVAL_H_

#include <stdbool.h>

// Main expresión
typedef char * EXP;

bool parenthesisBalance(EXP expresion);
bool invalidCharacters(EXP expresion);
bool operandsBalance(EXP expresion);

//Conversion
void infToPost(EXP expresion);






#endif /* _MATHEVAL_H_ */