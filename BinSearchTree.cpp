//
// Created by Ali Kooshesh on 3/1/23.
//

//Ethan Escalante
//James Togher

#include "BinSearchTree.hpp"
#include <iostream>
#include <algorithm>
#include <queue>

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

//Additions for Project 3
void BinSearchTree::levelOrderDump(){
    /*prints the values in the tree, one per line, using a level-order traversal.
      You must write an iterative solution using an STL queue.
     */


    if(root == nullptr){
        return;
    }
    std::queue<TreeNode*> treeQueue;
    treeQueue.push(root);


    while(!treeQueue.empty()){

        auto currentNode = treeQueue.front();
        treeQueue.pop();

        std::cout << currentNode->value() << std::endl;


        if(currentNode->leftSubtree() != nullptr){
            treeQueue.push(currentNode->leftSubtree());
        }
        if(currentNode->rightSubtree() != nullptr){
            treeQueue.push(currentNode->rightSubtree());
        }


    }


}

bool BinSearchTree::remove(int v) {
    if(find(v)){
       root = remove(root, v);
        return true;
    }

    return false;

}


TreeNode* BinSearchTree::remove(TreeNode *root, int v) {
    //future Ethan, this one was the hardest
    if (root == nullptr) {
        return nullptr;
    } else if (v > root->value()) {
        root->rightSubtree(remove(root->rightSubtree(), v));
    } else if (v < root->value()) {
        root->leftSubtree(remove(root->leftSubtree(), v));
    } else {
        if (root->leftSubtree() == nullptr && root->rightSubtree() == nullptr) {
            TreeNode *temp = nullptr;
            delete root;
            return temp;

        } else if (root->leftSubtree() == nullptr && root->rightSubtree() != nullptr) {
            TreeNode *temp = root->rightSubtree();
            delete root;
            return temp;
        } else if (root->rightSubtree() == nullptr && root->leftSubtree() != nullptr) {
            TreeNode *temp = root->leftSubtree();
            delete root;
            return temp;
        }

        TreeNode* temp(predecessor(root->leftSubtree()));
        root->value() = temp->value();
        root->leftSubtree(remove(root->leftSubtree(), temp->value()));



    }

    return root;
}


TreeNode * BinSearchTree::predecessor(TreeNode *root) {
    TreeNode* current = root;
    while (current->rightSubtree() != nullptr) {
        current = current->rightSubtree();
    }
    return current;
}
int BinSearchTree::kthSmallest(int k) {
    if(size(root) < k){
        return 0;
    }


   return kthSmallest(root, k);


}



int BinSearchTree::kthSmallest(TreeNode* root, int k) {
    if(root == nullptr){
        return 0;
    }

    int leftSize = size(root->leftSubtree()); //get the size of left

    if(k <= leftSize){ //check the left subtree
        return kthSmallest(root->leftSubtree(), k);
    }

    if(k == leftSize + 1){ //checking for smallest node
        return root->value();
    }

    return kthSmallest(root->rightSubtree(), (k-leftSize-1)); //else, visit the right subtree


}

void BinSearchTree::valuesAtLevel(int k) {

    valuesAtLevel(root, k);
}

void BinSearchTree::valuesAtLevel(TreeNode *root, int k) {
    if(root == nullptr){
        return;
    }

    if(k == 1){
        std::cout << root->value() << std::endl;
    }

    valuesAtLevel(root->leftSubtree(), k - 1);
    valuesAtLevel(root->rightSubtree(), k - 1);


}

void BinSearchTree::iterValuesAtLevel(int k) {
    //similar to levelOrderDump(), but print by each level

    if(root == nullptr){ //base case
        return;
    }

    std::queue<TreeNode*> treeQueue;
    treeQueue.push(root);
    int currentLevel = 1; //level counter

    while(!treeQueue.empty() ){
        int currentLevelMembers = treeQueue.size(); //for level by level

        while(currentLevelMembers > 0) {
            auto currentNode = treeQueue.front();
            treeQueue.pop();
            currentLevelMembers--; //taking in a member of the level, so we decrement

            if (k == currentLevel) {
                std::cout << currentNode->value() << std::endl;
            }

            if (currentNode->leftSubtree() != nullptr) {
                treeQueue.push(currentNode->leftSubtree());
            }
            if (currentNode->rightSubtree() != nullptr) {
                treeQueue.push(currentNode->rightSubtree());
            }


        }

        currentLevel++; //move onto the next level
    }

}

int BinSearchTree::iterMaxDepth() {
    //level order, similar to the first problem in terms of traversal

    if(root == nullptr){
        return 0;
    }

    std::queue<TreeNode*> treeQueue;
    treeQueue.push(root);
    int maxDepth = 0;

    while(!treeQueue.empty()){
        int size = treeQueue.size();


        for(int i = 0; i < size; i++){
            TreeNode* currentNode = treeQueue.front();
            treeQueue.pop();

            if(currentNode->leftSubtree() != nullptr){
                treeQueue.push(currentNode->leftSubtree());
            }
            if(currentNode->rightSubtree() != nullptr){
                treeQueue.push(currentNode->rightSubtree());
            }

        }
        maxDepth++;



    }

    return maxDepth;


}

bool BinSearchTree::hasRootToLeafSum(int sum) {
    return hasRootToLeafSum(root, sum);
}

bool BinSearchTree::hasRootToLeafSum(TreeNode * root, int sum) {

    if(root == nullptr){
        return false;
    }

    if(root->leftSubtree() == nullptr && root->rightSubtree() == nullptr) {

       if(root->value() == sum){
            return true;
       }

       return false;
    }

    return hasRootToLeafSum(root->leftSubtree(), sum - root->value()) || hasRootToLeafSum(root->rightSubtree(), sum - root->value());





}

bool BinSearchTree::areIdentical(BinSearchTree *bst) {

    return areIdentical(root, bst->root);
}

bool BinSearchTree::areIdentical(TreeNode *root, TreeNode* copy ) {


    if(root == nullptr && copy == nullptr){
        return true;
    }
    if(root == nullptr || copy == nullptr){
        return false;
    }

    return areIdentical(root->leftSubtree(), copy->leftSubtree()) && areIdentical(root->rightSubtree(), copy->rightSubtree());




}

BinSearchTree *BinSearchTree::intersectWith(BinSearchTree *bst) {
    BinSearchTree* finalResult = new BinSearchTree();
    intersectWith(root, bst->root, finalResult);
    return finalResult;

}


void BinSearchTree::intersectWith(TreeNode *rootOf1, TreeNode *rootOf2, BinSearchTree *finalTree) {
    //base case
    if(rootOf1 == nullptr || rootOf2 == nullptr){
        return;
    }

    //go through new tree and try to find same values as in the 1st tree
    if(find(rootOf2, rootOf1->value())){
        finalTree->insert(rootOf1->value());
    }

    //if these values were not found, then we have to traverse to the left and right of the tree
    //and try again

    if(rootOf1->leftSubtree() != nullptr){

        intersectWith(rootOf1->leftSubtree(),rootOf2,finalTree);
    }
    if(rootOf1->rightSubtree() != nullptr){

        intersectWith(rootOf1->rightSubtree(),rootOf2,finalTree);
    }




}



BinSearchTree *BinSearchTree::unionWith(BinSearchTree *bst) {
    BinSearchTree* finalResult = new BinSearchTree();
    unionWith(root, bst->root, finalResult);
    return finalResult;
}

void BinSearchTree::unionWith(TreeNode *rootof1, TreeNode *rootof2, BinSearchTree *finalTree) {
    if(rootof1 == nullptr && rootof2 == nullptr){
        return;
    }

    //case 1: values of both trees are different
    if(!find(rootof2, rootof1->value())){
        finalTree->insert(rootof1->value());
        finalTree->insert(rootof2->value());
    }

    //case 2: values of both trees are the same
    finalTree->insert(rootof1->value());

    if(rootof1->leftSubtree() != nullptr){

        unionWith(rootof1->leftSubtree(),rootof2,finalTree);
    }
    if(rootof1->rightSubtree() != nullptr){

        unionWith(rootof1->rightSubtree(),rootof2,finalTree);
    }


}


BinSearchTree *BinSearchTree::differenceOf(BinSearchTree *bst) {
    BinSearchTree* finalResult = new BinSearchTree();
    differenceOf(root, bst->root, finalResult);
    return finalResult;

}

void BinSearchTree::differenceOf(TreeNode *rootof1, TreeNode *rootof2, BinSearchTree *finalTree) {
    if(rootof1 == nullptr && rootof2 == nullptr){
        return;
    }

    if(!find(rootof1, rootof2->value())){
        finalTree->insert(rootof2->value());
    }

    if(rootof2->leftSubtree() != nullptr){

        differenceOf(rootof1,rootof2->leftSubtree(),finalTree);
    }
    if(rootof2->rightSubtree() != nullptr){

        differenceOf(rootof1,rootof2->rightSubtree(),finalTree);
    }




}