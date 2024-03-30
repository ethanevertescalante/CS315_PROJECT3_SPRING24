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

    //Additions for Project 3
    void levelOrderDump();
    bool remove( int v );
    int kthSmallest( int k );
    void valuesAtLevel( int k );
    void iterValuesAtLevel( int k );
    int iterMaxDepth();
    bool hasRootToLeafSum( int sum );
    bool areIdentical( BinSearchTree* bst);
    BinSearchTree* intersectWith(BinSearchTree* bst);
    BinSearchTree* unionWith(BinSearchTree* bst);
    BinSearchTree* differenceOf(BinSearchTree* bst);


private:

    //lab 6 helper functions
    TreeNode *insert( TreeNode *, int );
    int size(TreeNode *);
    bool find(TreeNode *, int v);
    void inorderDump(TreeNode *);
    int maxDepth(TreeNode *);

    //project 3 helper functions
    TreeNode* remove(TreeNode* root, int v);
    TreeNode* predecessor(TreeNode* root);


    int kthSmallest(TreeNode* root, int k);

    void valuesAtLevel(TreeNode* root, int k);

    bool hasRootToLeafSum(TreeNode* root ,int sum);

    bool areIdentical(TreeNode* root, TreeNode* copy);

    void intersectWith(TreeNode* rootOf1, TreeNode* rootOf2, BinSearchTree* finalTree);

    void unionWith(TreeNode* rootof1, TreeNode* rootof2, BinSearchTree* finalTree);

    void differenceOf(TreeNode* rootof1, TreeNode* rootof2, BinSearchTree* finalTree);


    TreeNode *root;
};


#endif //BINSEARCHTREE_BINSEARCHTREE_HPP
