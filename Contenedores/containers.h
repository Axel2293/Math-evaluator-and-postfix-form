#ifndef _CONTAINERS_H_
#define _CONTAINERS_H_

#include <stdbool.h>
#include <stddef.h>

//Generic data storage
typedef void * DATA;

// ========================== STACK
    //Pointer to the stack container
typedef struct stack * Stack;

Stack stack_create();
int stack_size(Stack);
bool stack_isEmpty(Stack);
DATA stack_top(Stack);
void stack_push(Stack, DATA);
DATA stack_pop(Stack);
void stack_destroy(Stack);
void print_stack(Stack);


// =========================== QUEUE
    // Pointer to the queue container
typedef struct Queue * QueueP;

//Create the queue container
QueueP queueCreate(size_t);
//Returns the size_t of the queue
int queueSize(QueueP);
//Returns true or false depending if the queue is empty
bool queueEmpty(QueueP);
//Destroys the que and all the data in it
void queueDestroy(QueueP);
//Adds an element to the end of the queue list
void enqueue(QueueP, DATA);
//Returns and removes the first element in the queue
DATA dequeue(QueueP);
//Consult the first element of the list
DATA peek(QueueP);


#endif /*_CONTAINERS_H_*/