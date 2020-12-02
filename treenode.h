#ifndef TREENODE_H
#define TREENODE_H
#pragma once


/*
 * This is a type that represents a node in an encoding tree.
 * Each node stores two pointers, with the left pointer pointing to a child
 * labeled 0 and the right pointer pointing to a child labeled 1. If the node is
 * a leaf, then both child pointers are nullptr. If the node is a leaf, then
 * the char ch of the node is set to the value of the leaf; otherwise, ch should
 * not be accessed. 
 */

struct EncodingTreeNode {

    char ch;
    EncodingTreeNode* zero;
    EncodingTreeNode* one;

    EncodingTreeNode(char c) {  //constructor for new leaf node
        ch = c;
        zero = nullptr; 
        one = nullptr;
    }

    EncodingTreeNode(EncodingTreeNode* zero, EncodingTreeNode* one) { //constructor for new interior (not-leaf) node
        this->zero = zero;
        this->one = one;
    }

    bool isLeaf() {
        return zero == nullptr && one == nullptr;
    }

    char getChar() {
        return ch;
    }

#endif // TREENODE_H
    
};

/*
 * This is a type that represents a node in an encoding tree
 * that also has a priority
 */

struct TreeNodeWithPriority {
    EncodingTreeNode* treeNode;
    int priority;

    TreeNodeWithPriority(EncodingTreeNode* treeNode, int priority) {  //constructor
        this->treeNode = treeNode;
        this->priority = priority;
    }
};

