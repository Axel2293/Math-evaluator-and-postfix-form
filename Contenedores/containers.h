#ifndef _CONTAINERS_H_
#define _CONTAINERS_H_

#include <stdbool.h>
#include <stddef.h>

//Generic data storage
typedef void * DATA;

// ========================== STACK
    //Pointer to the stack container
typedef struct stack * Stack;

Stack stack_create(size_t);
int stack_size(Stack);
bool stack_isEmpty(Stack);
DATA stack_top(Stack);
void stack_push(Stack, DATA);
DATA stack_pop(Stack);
void stack_destroy(Stack);
void print_stack(Stack);


// =========================== QUEUE
    // Pointer to the queue container
typedef struct queue * Queue;

//Create the queue container
Queue queueCreate(size_t);
//Returns the size_t of the queue
int queueSize(Queue);
//Returns true or false depending if the queue is empty
bool queueEmpty(Queue);
//Destroys the que and all the data in it
void queueDestroy(Queue);
//Adds an element to the end of the queue list
void enqueue(Queue, DATA);
//Returns and removes the first element in the queue
DATA dequeue(Queue);
//Consult the first element of the list
DATA peek(Queue);


#endif /*_CONTAINERS_H_*/