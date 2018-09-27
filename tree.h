#ifndef TREE_H
#define TREE_H

typedef struct
{
    int data;
    BTreeNode *lchild;
    BTreeNode *rchild;

}BTreeNode;

class BiTree{
    private:
        BTreeNode *root;
        
    public:
        BiTree(){root=NULL;}
        createBiTree();

        inOrder();
        NotReinOrder();

        preOrder();
        NotRepreOrder();

        postOrder();

        BiTreeSize();

        BiTreeLeaves()

        BiTreeHeight()


    protected:
        inOrder(BTreeNode*);
        preOrder(BTreeNode*);
        postOrder(BTreeNode*);
        BiTreeSize(BTreeNode*);
        BiTreeLeaves(BTreeNode*);
        BiTreeHeight(BTreeNode*);

}

#endif