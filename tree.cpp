#include <iostream>
#include <stack>
#include "tree.h"

using namespace std;

BTreeNode* BiTree::createBiTree()
{
    BTreeNode *r;
    char val;

    cin>>val;

    if(val=='#')
        return NULL;
    else{
        r = new BTreeNode;
        r->data = val;
        r->lchild = createBiTree();
        r->rchild = createBiTree();
        return r;
    }
}

void BiTree::inOrder()
{
    inOrder(root);
    cout<<endl;
}

void BiTree::inOrder(BTreeNode* r)
{
    if(r!=0)
    {
        inOrder(r->lchild);
        cout<<r->data<<" ";
        inOrder(r->rchild);
    }
}

void BiTree::NotReinOrder()
{
    stack<BTreeNode*> s;
    BTreeNode *r = getRoot();
    while(!s.empty()||r!=0)
    {
        while(r!=0)
        {
            s.push(r);
            r=r->lchild;
        }
        if(!s.empty())
        {
            r=s.top();
            s.pop();
            cout<<r->data<<" ";
            r = r->rchild;
        }
    }
    cout<<endl;
}

void BiTree::preOrder()
{
    preOrder(root);
    cout<<endl;
}

void BiTree::preOrder(BTreeNode *r)
{
    if(r!=0)
    {
        cout<<r->data<<" ";
        preOrder(r->lchild);
        preOrder(r->rchild);
    }
}

void BiTree::NotRepreOrder()
{
    stack<BTreeNode *> s;
    BTreeNode *r = getRoot();
    s.push(r);

    while(!s.empty())
    {
        r = s.top();
        s.pop();

        cout<<r->data<<" ";

        if(r->rchild!=0)
            s.push(r->rchild);
        if(r->lchild!=0)
            s.push(r->lchild);
    }
    cout<<endl;
}

void BiTree::postOrder()
{
    postOrder(root);
    cout<<endl;
}

void BiTree::postOrder(BTreeNode *r)
{
    if(r!=0)
    {
        postOrder(r->lchild);
        postOrder(r->rchild);
        cout<<r->data<<" ";
    }
}

int BiTree::BiTreeSize()
{
    return BiTreeSize(root);
}

int BiTree::BiTreeSize(BTreeNode *r)
{
    if(r==0) return 0;
    else
        return 1+BiTreeSize(r->lchild)+BiTreeSize(r->rchild);
}

int BiTree::BiTreeLeaves()
{
    return BiTreeLeaves(root);
}

int BiTree::BiTreeLeaves(BTreeNode *r)
{
    if(r==NULL)
        return 0;
    else if(r->lchild==NULL&&r->rchild==NULL)
        return 1;
    else
        return BiTreeLeaves(r->lchild)+BiTreeLeaves(r->rchild);
}

int BiTree::BiTreeHeight()
{
    return BiTreeHeight(root);
}

int BiTree::BiTreeHeight(BTreeNode* r)
{
    int HL,HR,max;
    if(r!=NULL)
    {
        HL = BiTreeHeight(r->lchild);
        HR = BiTreeHeight(r->rchild);
        max = HL>HR? HL:HR;
        return max+1;
    }
    else
        return 0;
}


int main()
{
    BiTree tree;
    BTreeNode *root;
    root = tree.createBiTree();
    tree.setRoot(root);
    tree.preOrder();
    tree.NotRepreOrder();
    tree.inOrder();
    tree.NotReinOrder();
    tree.postOrder();
    // tree.NotRepostOrder();

    return 0;
}