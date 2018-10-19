#include "stdio.h"
#include "cstack.h"
#include "stdlib.h"
#include "assert.h"


void StackNew(stack *s)
{
    s->logicalLen = 0;
    s->alloclength = 0;
    s->elems = mallloc(4*sizeof(int));
    assert(s->elems!=NULL);
}

void StackDispose(stack *s)
{
    free(s->elems);
}

void StackPush(stack *s, int value)
{
    if(s->logicalLen == s->alloclength){
        s->alloclength *= 2;
        s->elems = realloc(s->elems,s->alloclength*sizeof(int));
        assert(s->elems!=NULL);
    }

    s->elems[s->logicalLen] = value;
    s->logicalLen++;
}

int StackTop(stack *s)
{
    return s->elems[s->logicalLen-1];
}


void StackPop(stack *s)
{
    assert(s->logicalLen>0);
    s->logicalLen --;
}

int main()
{
    stack s;

    StackNew(&s);
    for(int i=0;i<5;i++)
    {
        StackPUsh(&s,i);
    }
    StackDispose(&s);

    return 0;
}