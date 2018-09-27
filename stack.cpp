#include <iostream>
#include "stack.h"
using namespace std;

int main()
{
    Stack s;
    s.Push(1);
    s.Push(2);
    s.Push(3);


    cout<<s.Size()<<endl;
    cout<<s.Empty()<<endl;
    cout<<s.Top()<<endl;
    s.Pop();
    cout<<s.Top()<<endl;
    s.Pop();
    cout<<s.Top()<<endl;
    s.Pop();
    cout<<s.Top()<<endl;
    cout<<s.Empty()<<endl;

    return 0;
}