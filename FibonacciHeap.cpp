#include<bits/stdc++.h>
using namespace std;

struct heapNode{
    int key;
    int degree;
    bool mark;
    heapNode* parent;
    heapNode* child;
    heapNode* left;
    heapNode* right;
    bool flag;
};

class FibonacciHeap{
    int noOfNodes;
    heapNode* maxNode;

    void linkNodes(){
        //link the nodes
    }

    void consolidate(){
        //consolidate the nodes
    }

    void cutNode(){
        //cut the node
    }

    void cascadingCut(){
        //cascading cut
    }
    
    heapNode* createNode(int key){
        heapNode* node = new heapNode;
        node->key = key;
        node->degree = 0;
        node->mark = false;
        node->flag = false;
        node->parent = NULL;
        node->child = NULL;
        node->left = node;
        node->right = node;
        return node;
    }

  public:
    //return reference after initializing the heap
    heapNode* initializeHeap(){
        noOfNodes = 0;
        maxNode = NULL;
        return maxNode;
    }
    
    bool isEmpty(heapNode* node){
        return node == NULL;
        //return noOfNodes == 0;
    }
    
    void insertNode(heapNode* node, int key){
        heapNode* newNode = createNode(key);
        if(node != NULL){
            (node->left)->right = newNode;
            newNode->right = node;
            newNode->left = node->left;
            node->left = newNode;
            if(newNode->key > node->key){
                node = newNode;
            }
        }else{
            node = newNode;
        }    
        noOfNodes++;
    }

    int extract_max(heapNode *hNode){

    }

    int find_max(heapNode *hNode){
        return hNode->key;         //return value later
    }
    
    heapNode* meld(heapNode *h1, heapNode *h2){   //need edits(this should be in priority queue class)
        // if(h1 == NULL && h2 == NULL){
        //     return NULL;
        // }else if(h1 != NULL && h2 == NULL){
        //     return h1;
        // }else if(h1 == NULL && h2 != NULL){
        //     return h2;
        // }else{
        //     heapNode* leftNode = h1->left;
        //     heapNode* rightNode = h2->right;
        //     h1->left = h2;
        //     h2->right = h1;
        //     leftNode->right = rightNode;
        //     rightNode->left = leftNode;
        //     if(h1->key > h2->key){
        //         return h1;
        //     }else{
        //         return h2;
        //     }
        // }
    }

    void print(heapNode *hNode){
        
    }

};




//https://www.programiz.com/dsa/fibonacci-heap

//https://github.com/woodfrog/FibonacciHeap/blob/master/FibHeap.h

//https://github.com/woodfrog/FibonacciHeap/blob/master/FibHeap.cpp

//https://iq.opengenus.org/fibonacci-heap/

//https://www.programiz.com/dsa/decrease-key-and-delete-node-from-a-fibonacci-heap

//https://brilliant.org/wiki/fibonacci-heap/
