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
    List l2;
    l2.creatlist(2);
    l2.insert(3,1);
    l2.insert(4,2);
    l2.insert(10,3);
    l2.print();
    listNode* head = new listNode;

    // cout<<l.getlength()<<endl;
    // l.remove(1);
    // l.print();
    // l.reverse();
    // l.print();
    // cout<<l.getlength()<<endl;
    // l.clearList();
    // cout<<l.getlength()<<endl;

    
    return 0;
}