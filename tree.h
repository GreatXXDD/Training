#ifndef TREE_H
#define TREE_H

typedef struct BTreeNode
{
    int data;
    BTreeNode *lchild;
    BTreeNode *rchild;

}NODE;

class BiTree{
    private:
        BTreeNode *root;
        
    public:
        BiTree(){root=NULL;}
        BTreeNode* createBiTree();
        BTreeNode* getRoot(){return root;}
        void setRoot(BTreeNode* r){root = r;}

        void inOrder();
        void NotReinOrder();

        void preOrder();
        void NotRepreOrder();

        void postOrder();

        int BiTreeSize();

        int BiTreeLeaves();

        int BiTreeHeight();


    protected:
        void inOrder(BTreeNode*);
        void preOrder(BTreeNode*);
        void postOrder(BTreeNode*);
        int BiTreeSize(BTreeNode*);
        int BiTreeLeaves(BTreeNode*);
        int BiTreeHeight(BTreeNode*);

};

#endif