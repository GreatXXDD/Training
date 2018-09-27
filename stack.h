#ifndef STACK_H
#define STACK_H


class Stack{
    private:
         int *ptr;
         int top;
         int maxSize;
    public:
        Stack():top(-1),maxSize(100)
        {
            ptr = new int[maxSize];
            if(ptr==NULL)
                exit(1);
        }
        Stack(int size):top(-1),maxSize(size)
        {
            ptr = new int[maxSize];
            if(ptr==NULL)
                exit(1);
        }
        ~Stack(){delete[] ptr;}

        bool Empty();
        void Push(int elem);
        void Pop();
        int Top();
        int Size();
};

bool Stack::Empty()
{
    if(top==-1)
    {
        return true;
    }
    else{
        return false;
    }
}

void Stack::Push(int elem)
{
    if(top+1<maxSize)
    {
        ptr[++top] = elem;
    }
    else{
        exit(1);
    }
}

void Stack::Pop()
{
    if(top==-1)
    {
        exit(1);
    }
    else{
        top--;
    }
}

int Stack::Top()
{
    if(top==-1)
        exit(1);
    else{
        return ptr[top];
    }
}

int Stack::Size(){

    int i;
    return top+1;
}

#endif