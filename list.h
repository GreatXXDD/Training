#ifndef LIST_H
#define LIST_H
using namespace std;


typedef struct listNode{
    int data;
    listNode *next;
}Node;

class List{
private:
    listNode *head;
    int len;
public:
    List(){head=NULL;len=0;}
    ~List();
    void creatlist(int elem);
    void clearList();
    listNode* getNode(int pos);
    void insert(int elem, int pos);
    void remove(int pos);
    int getlength(){return len;}
    void print();
    void reverse();
};

List::~List()
{
    while(head!=NULL)
    {
        listNode *s = head;
        head = head->next;
        delete s;
    }
    delete head;
}

void List::creatlist(int elem)
{
    head = new listNode;
    head->data = elem;
    head->next = NULL;
    len++;
}

void List::clearList()
{
    while(head!=NULL)
    {
        listNode *s = head;
        head = head->next;
        delete s;
    }
    delete head;
    len = 0;
}

listNode* List::getNode(int pos){
    if(pos<0||pos>len) return NULL;
    int i=1;
    listNode *cur=head;
    while(i<pos)
    {
        i++;
        cur = cur->next;
    }
    return cur;
}

void List::insert(int elem,int pos)
{
    listNode *l = getNode(pos);
    listNode *s = new listNode;
    s->data = elem;
    s->next = l->next;
    l->next = s;
    len++;
}

void List::remove(int pos)
{
    listNode* s = new listNode;
    listNode *l=getNode(pos);
    s = l->next;
    l->next = l->next->next;
    delete s;
    len --;
}

void List::print()
{
    listNode *cur =new listNode;
    cur =head;
    while(cur!=NULL)
    {
        cout<<cur->data<<" ";
        cur = cur->next;
    }
    cout<<endl;
}

void List::reverse()
{
    listNode *p,*q,*tmp;
    q = head;
    p = head->next;
    while(p)
    {
        tmp=p->next;
        p->next=q;
        q=p;
        p=tmp;
    }
    head->next=NULL;
    head = q;
}

#endif