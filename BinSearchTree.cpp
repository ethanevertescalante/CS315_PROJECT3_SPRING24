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
        remove(root, v);
        return true;
    }
    return false;

}


TreeNode* BinSearchTree::remove(TreeNode *root, int v) {
  if(root == nullptr){
      return nullptr;
  }
  if(v > root->value()){
      root->rightSubtree(remove(root->rightSubtree(), v));
  }else if(v < root->value()){
      root->leftSubtree(remove(root->leftSubtree(), v));
  }else{
      if(root->leftSubtree() == nullptr && root->rightSubtree() == nullptr){
          root = nullptr;
      }else if(root->rightSubtree() != nullptr){
          root->value() = successor(root);
          root->rightSubtree(remove(root->rightSubtree(),root->value()));
      }else{
          root->value() = predecessor(root);
          root->leftSubtree(remove(root->leftSubtree(), root->value()));
      }
  }

    return root;
}

int BinSearchTree::predecessor(TreeNode *root) {
    root = root->leftSubtree();
    while(root->rightSubtree() != nullptr){
        root = root->rightSubtree();
    }
    return root->value();
}

int BinSearchTree::successor(TreeNode *root) {
    root = root->rightSubtree();
    while(root->leftSubtree() != nullptr){
        root = root->leftSubtree();
    }
    return root->value();
}
int BinSearchTree::kthSmallest(int k) {

    return kthSmallest(root, k);

}

//TODO:: still working on kthSmallest, also test remove and see how it goes


int BinSearchTree::kthSmallest(TreeNode *root, int k) {

    return 1;

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

//TODO:: runtime on intersect with is too long, try to figure out a better way of inputting into the new tree
void BinSearchTree::intersectWith(TreeNode *rootOf1, TreeNode *rootOf2, BinSearchTree *finalTree) {
    if(rootOf1 == nullptr || rootOf2 == nullptr){
        return;
    }

    if(rootOf1->value() == rootOf2->value()){ //values match
        finalTree->insert(rootOf1->value());//either value will work
        intersectWith(rootOf1->leftSubtree(), rootOf2->leftSubtree(), finalTree);
        intersectWith(rootOf1->rightSubtree(), rootOf2->rightSubtree(), finalTree);
    }

    //if no match, then we have to compare each node with every other node in the opposite tree
    //but also traverse adhering to the bst rules

    else if(rootOf1->value() > rootOf2->value()){
        intersectWith(rootOf1->rightSubtree(), rootOf2, finalTree); //smaller value, search in left


    }else if(rootOf1->value() < rootOf2->value()){
        intersectWith(rootOf1, rootOf2->rightSubtree(), finalTree); //bigger value, search in right
    }




}