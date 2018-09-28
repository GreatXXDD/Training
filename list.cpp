#include <iostream>
#include "list.h"

int main()
{
    List l;
    l.creatlist(1);
    l.insert(1,1);
    l.insert(2,2);
    l.insert(3,3);
    l.print();
    cout<<l.getlength()<<endl;
    l.remove(1);
    l.print();
    l.reverse();
    l.print();
    cout<<l.getlength()<<endl;
    l.clearList();
    cout<<l.getlength()<<endl;

    return 0;
}