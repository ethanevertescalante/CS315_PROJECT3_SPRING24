//
// Created by Ali Kooshesh on 3/1/23.
//

#ifndef BINSEARCHTREE_BINSEARCHTREE_HPP
#define BINSEARCHTREE_BINSEARCHTREE_HPP


#include "TreeNode.hpp"

class BinSearchTree {
public:
    BinSearchTree();
    void insert( int v );
    bool find( int v );
    bool iterFind( int v );
    int size();
    void inorderDump();
    int maxDepth();
    void iterInsert( int v );
    void destructorHelper(TreeNode *);

    ~BinSearchTree();

private:
    TreeNode *insert( TreeNode *, int );
    int size(TreeNode *);
    bool find(TreeNode *, int v);
    void inorderDump(TreeNode *);
    int maxDepth(TreeNode *);

    TreeNode *root;
};


#endif //BINSEARCHTREE_BINSEARCHTREE_HPP
