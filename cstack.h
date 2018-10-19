#ifndef CSTACK_H
#define CSTACK_H
/*
    用C语言实现栈
    风格竟可能和C++相似
*/
typedef struct {
    int *elems;
    int logicalLen;
    int alloclength;
}stack;

void StackNew(stack *s);
void StackDispose(stack *s);
void StackPush(stack *s, int value);
void StackPop(stack *s);
int StackTop(stack *s);


#endif