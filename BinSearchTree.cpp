//
// Created by Ali Kooshesh on 3/1/23.
//

//Ethan Escalante
//James Togher

#include "BinSearchTree.hpp"
#include <iostream>
#include <algorithm>

BinSearchTree::BinSearchTree(): root{nullptr} {}

TreeNode *BinSearchTree::insert( TreeNode *root, int v ) {
    if( root == nullptr )
        return new TreeNode( v );
    if( root->value() < v )
        root->rightSubtree( insert( root->rightSubtree(), v ) );
    else
        root->leftSubtree( insert( root->leftSubtree(), v ) );
    return root;
}

void BinSearchTree::insert(int v) {
    // Insert v in the tree if it is not already a member.
    if( ! find(v) ) {
        root = insert(root, v);
    }
}

int BinSearchTree::size() {
    // Write this function first!
    return size(root);

}

int BinSearchTree::size(TreeNode * root) {
    //helper function
    if(root == nullptr)
        return 0;

    return 1 + size(root->leftSubtree()) + size(root->rightSubtree());
}

bool BinSearchTree::find(int v) {
    // You need to write a recursive implementation for this function.
    // Right now, it returns false so that insert can do its job.
    // That means, it will add duplicates to the tree, which is not desirable.
   return find(root, v);

}

bool BinSearchTree::find(TreeNode * root, int v) {
    //helper function

    if(root == nullptr){
        return false;
    }
    if(root->value() == v){
        return true;
    }
    if(root->value() < v){
        return find(root->rightSubtree(), v);
    }else {
        return find(root->leftSubtree(), v);
    }
}

bool BinSearchTree::iterFind(int v) {
    TreeNode *temp = root;
    while(temp != nullptr){
        if(temp->value() == v){
            return true;
        }else if(temp->value() < v){
            temp = temp->rightSubtree();
        }else if(temp->value() > v){
            temp = temp->leftSubtree();
        }
    }

    return false;

}

void BinSearchTree::inorderDump() {
    inorderDump(root);
}

void BinSearchTree::inorderDump(TreeNode * root) {
    TreeNode* temp = root;
    if(temp == nullptr){
        return;
    }
    inorderDump(temp->leftSubtree());
    std::cout << temp->value() << std::endl;
    inorderDump(temp->rightSubtree());

}


int BinSearchTree::maxDepth() {
    return maxDepth(root);
}


int BinSearchTree::maxDepth(TreeNode * root) {
    TreeNode* temp = root;
    if(temp == nullptr){
        return 0;
    }

    return 1 + std::max(maxDepth(temp->leftSubtree()), maxDepth(temp->rightSubtree()));

}

void BinSearchTree::iterInsert(int v) {

    TreeNode *newNode = new TreeNode(v);
    if (root == nullptr){
        root = newNode;
        return;
    }

    TreeNode *temp = root;

if(!find(temp, v)){
    while (temp != nullptr){

        //I pretty much just combined the two if statements we had and put then into the while loop

        if (v > temp->value()){
            if (temp->rightSubtree() == nullptr){
                temp->rightSubtree(newNode);
                return;
            }
            temp = temp->rightSubtree();
        } else if (v < temp->value()){
            if (temp->leftSubtree() == nullptr){
                temp->leftSubtree(newNode);
                return;
            }
            temp = temp->leftSubtree();
        }
    }

}
}

BinSearchTree::~BinSearchTree(){
    // This function should delete every node in the tree.
    // To do that, you will have to recursively traverse the tree, using
    // a post-order traversal.
    /*
        left
        right
        node
     */

    destructorHelper(root);


}

void BinSearchTree::destructorHelper(TreeNode * root){
  

    if(root == nullptr) {
        return;
    }

    destructorHelper(root->leftSubtree());
    destructorHelper(root->rightSubtree());
    delete root;


    /*
    if(root->leftSubtree() == nullptr && root->rightSubtree() == nullptr){
        delete root;
    }else{
        destructorHelper(root->leftSubtree());
        destructorHelper(root->rightSubtree());
    }
     */
}
