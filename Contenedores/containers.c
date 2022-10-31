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
    if (stk!=NULL)
    {
        return stk->size;
    }
    else
    {
        return -1;
    }
    
}

bool stack_isEmpty(Stack stk)
{
    if (stk != NULL)
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
    else
    {
        return true;
    }
    
}

DATA stack_top(Stack stk)
{
    if (stk!=NULL)
    {
        if(stk->top!=NULL)
        {
            return stk->top->data;
        }
        else 
        {
            return NULL;
        }
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
    if(stk!=NULL)
    {
        if(stk->top!=NULL)
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
    else
    {
        return NULL;
    }
}

void stack_destroy(Stack stk)
{

    // Destroy nodes

    if (stk!=NULL)
    {
        if(stk->top!=NULL && stk->size!=0)
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
struct queue
{
    NodePQ first;
    NodePQ last;
    int size;
    size_t size_data;
};





Queue queueCreate(size_t bytes)
{
    Queue new=malloc(sizeof(struct queue));
    new->first=NULL;
    new->last=NULL;
    new->size_data=bytes;
    new->size=0;
    return new;
}

int queueSize(Queue q1)
{
    if(q1!=NULL)
    {
        return q1->size;
    }
    else
    {
        return 0;
    }
}

bool queueEmpty(Queue q1)
{
    if(q1!=NULL)
    {
        if(q1->size==0 && q1->first==NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
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

void enqueue(Queue q, DATA data)
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

DATA peek(Queue q)
{
    if (q!=NULL)
    {
        if( !queueEmpty(q))
        {
            return q->first->data;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
    
}

DATA dequeue(Queue q)
{
    if (q!=NULL)
    {
        if(!queueEmpty(q))
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
            q->size--;
            return temp;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
    
}

void queueDestroy(Queue q)
{
    if(q!=NULL)
    {
        DATA temp;
        while (!queueEmpty(q))
        {
            temp=dequeue(q);
            free(temp);
        }
        free(q);
    }
}