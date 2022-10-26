#include "containers.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Stack s1=stack_create();
    printf("S1: %p\n", s1);

    int numbers[10]={5,6,4,8,2,4,1,8,9,0};

    stack_push(s1, (void *) &numbers[0]);
    print_stack(s1);
    printf("\n");

    stack_push(s1, (void *) &numbers[1]);
    print_stack(s1);
    printf("\n");

    stack_push(s1, (void *) &numbers[2]);
    print_stack(s1);
    printf("\n");

    stack_push(s1, (void *) &numbers[3]);
    print_stack(s1);
    printf("\n");

    stack_push(s1, (void *) &numbers[4]);
    print_stack(s1);
    printf("\n");
    
    printf("==========POST POPS========\n");
    void *data=stack_pop(s1);
    print_stack(s1);
    printf("POP: %p\n", data);
    printf("\n");

    data=stack_pop(s1);
    print_stack(s1);
    printf("POP: %p\n", data);
    printf("\n");

    data=stack_pop(s1);
    print_stack(s1);
    printf("POP: %p\n", data);
    printf("\n");

    data=stack_pop(s1);
    print_stack(s1);
    printf("POP: %p\n", data);
    printf("\n");

    data=stack_pop(s1);
    print_stack(s1);
    printf("POP: %p\n", data);
    printf("\n");


    //stack_destroy(s1);
    return 0;
}