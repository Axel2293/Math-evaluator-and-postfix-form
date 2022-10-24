#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "containers.h"

// ========================== STACK
    //NODE OF STACK
struct nodeSTK
{
    DATA data;
    struct nodeSTK *prior;

};
    //POinter to node of stack
typedef struct nodeSTK * NodePS;

    //Container stack
struct stack
{
    NodePS top;
    int size;
    size_t bytes;
};

Stack stack_create(size_t bytes)
{
    //Memory for all the elements in the struct stack
    Stack stk= malloc(sizeof(struct stack));

    //Initialize in 0
    stk->bytes=bytes;
    stk->size=0;
    stk->top=NULL;
    return stk;

}

int stack_size(Stack stk)
{
    return stk->size;
}

bool stack_isEmpty(Stack stk)
{
    if(stk->top==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

DATA stack_top(Stack stk)
{
    if(stk->top!=NULL && stk!=NULL)
    {
        return stk->top->data;
    }
    else 
    {
        return NULL;
    }
}

NodePS newNode(DATA data)
{
    NodePS new= malloc(sizeof(struct nodeSTK));
    new->data=data;
    new->prior=NULL;
    return new;
}

void stack_push(Stack stk, DATA data)
{
    if(stk!=NULL)
    {
        NodePS nd=newNode(data);
        stk->size++;
        nd->prior=stk->top;
        stk->top=nd;
    }
    else
    {
        printf("Error: Stack is null");
    }
}

DATA stack_pop(Stack stk)
{
    if(stk->top!=NULL && stk!=NULL)
    {
        void *dataTemp=stk->top->data;

        NodePS new_top=stk->top->prior;
        free(stk->top);
        stk->top=new_top;
        stk->size--;
        return dataTemp;
    }
    else
    {
        return NULL;
    }
}

void stack_destroy(Stack stk)
{

    // Destroy nodes

    if(stk->top!=NULL || stk->size!=0)
    {
        for(int i=0; i<stk->size; i++)
        {
            // Save next node to destroy
            if(stk->top!=NULL)
            {
                NodePS next_node=stk->top->prior;
                //Destroy one at the top
                free(stk->top);
                //Make new top
                stk->top=next_node;
            }
        }
    }
    //Delete stack
    free(stk);
}

void print_stack(Stack stk)
{
    printf("Size: %d\n", stk->size);
    printf("Top[0]:  %p\n", stk->top);
    if(stk->top!=NULL)
    {
        printf("\tData: %p\n", stk->top->data);

    }

        
    if(stk->top!=NULL)
    {
        if(stk->top->prior!=NULL){
            NodePS next=stk->top->prior;
            for(int i=1; i<=stk->size-1; i++)
            {
                printf("Node[%d]: %p\n",i,next);
                printf("\t Data: %p\n", next->data);
                next=next->prior;
            }
        }
    }
}


// ======================== QUEUE
    //NODE OF QUEUE
struct nodeQE
{
    DATA data;
    struct nodeQE *next;
};

    //Pointer to node o queue
typedef struct nodeQE * NodePQ;

    //CONTAINER QUEUE THAT LINKS START AND END
struct Queue
{
    NodePQ first;
    NodePQ last;
    int size;
    size_t size_data;
};





QueueP queueCreate(size_t bytes)
{
    QueueP new=malloc(sizeof(struct Queue));
    new->first=NULL;
    new->last=NULL;
    new->size_data=bytes;
    new->size=0;
    return new;
}

int queueSize(QueueP q1)
{
    if(q1!=NULL)
    {
        return q1->size;
    }
    else
    {
        return -1;
    }
}

bool queueEmpty(QueueP q1)
{
    if(q1!=NULL && q1->size==0)
    {
        return true;
    }
    else if(q1!=NULL && q1->size!=0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

NodePQ newNodeP(DATA data, size_t bytes)
{
    NodePQ new=malloc(sizeof(struct nodeQE));
    //Create space for the data
    new->data=malloc(bytes);
    //Copy the given data to the asignated node data
    memcpy(new->data, data, bytes);
    new->next=NULL;
    return new;
}

void enqueue(QueueP q, DATA data)
{
    if(q!=NULL)
    {
        NodePQ new=newNodeP(data, q->size_data);
        //If queue has no elements, then firs and last are the same
        if(queueEmpty(q))
        {
            q->first=new;
            q->last=new;
            q->size++;
        }
        else
        {
            //Last node points to the new node
            q->last->next=new;
            //The new last gets added as last
            q->last=new;
            q->size++;
        }
    }
}

DATA peek(QueueP q)
{
    if(q!=NULL && queueEmpty(q))
    {
        return q->first->data;
    }
    else
    {
        return NULL;
    }
}

DATA dequeue(QueueP q)
{
    if(q!=NULL && queueEmpty(q))
    {
        NodePQ ret=q->first;
        DATA temp=ret->data;
        
        if(ret->next!=NULL){
            q->first=ret->next;

        }
        else
        {
            q->first=NULL;
        }
        free(ret);
        return temp;
    }
    else
    {
        return NULL;
    }
}

void queueDestroy(QueueP q)
{
    if(q!=NULL)
    {
        DATA temp;
        while (!queueEmpty(q))
        {
            temp=dequeue(q);
            free(temp);
        }
        
    }
}