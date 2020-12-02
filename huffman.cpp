#include <iostream>
#include <fstream>
#include "treenode.h"
#include "huffman.h"
#include <map>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

/*
 * Given a queue<int> containing the compressed message bits and the encoding tree
 * used to encode those bits, this function decodes the bits back to the original
 * message text.
 *
 * The function goes thorugh a while loop and continues to remove
 * bits from the queue until the queue is empty. Additionally, there
 * is another while loop imbedded in the first while loop that keeps
 * track of the character is that is being encoded by traversing the
 * tree using the dequeued bits.
 *
 */
string decodeText(EncodingTreeNode* tree, queue<int>& messageBits) {

    string result = "";

    while(!messageBits.empty()){
        EncodingTreeNode* currentNode = tree;
        while(!currentNode->isLeaf()){
            int bit = messageBits.front();
            messageBits.pop();
            if(bit == 0){
                currentNode = currentNode->zero;
            }
            else{
                currentNode = currentNode->one;
            }
        }
        result += currentNode->getChar();
    }
    return result;
}

/*
 * This function reconstructs the encoding tree from flattened form queue<int> and qeue<char>.
 *
 * This function uses a recursvie implementation to unflatten out the tree.
 * If the bit equals zero, a new tree leaf node is created. Otherwise, the tree
 * splits into two subtrees, which are created by calling the function again, first
 * with the left branch and then with the right branch.
 */
EncodingTreeNode* unflattenTree(queue<int>& treeShape, queue<char>& treeLeaves) {

    EncodingTreeNode* root;
    int bit = treeShape.front();
    treeShape.pop();
    if(bit == 0){
        root = new EncodingTreeNode(treeLeaves.front());
        treeLeaves.pop();
        return root;
    }

    return root = new EncodingTreeNode(unflattenTree(treeShape, treeLeaves), unflattenTree(treeShape, treeLeaves));
}

/*
 * This function decompressses an EncodedData object by creating a tree
 * first with the unflattenTree helper function and then with the decodeText
 * helper function. The decoded string is then returned.
 */
string decompress(EncodedData& data) {
    EncodingTreeNode* tree = unflattenTree(data.treeShape, data.treeLeaves);
    string text = decodeText(tree, data.messageBits);
    deallocateTree(tree);
    return text;
}

struct comparator{
    bool operator()(TreeNodeWithPriority* &a, TreeNodeWithPriority* &b){
       return (a->priority > b->priority);
    }
};

/*
 * This function constructs an optimal Huffman coding tree for the given text.
 *
 * This functoin first adds each unique character in the text to a Map and then
 * sets the value of each character to the number of times it appears in the text.
 * It then creates a leaf using the characters and then adds the leaves to a priority
 * queue using the corresponding values as priorities. Two trees are then dequeued from
 * the queue at a time, are combined to create a new tree with priority equal to the sum
 * of the previous priorities, and then added back to the priority queue. Once the queue
 * has one element left, this tree is returned.
 */
EncodingTreeNode* buildHuffmanTree(string text) {

    map<char, int> characterWeights;

    while(text.length() != 0){
        char character = text[0];
        characterWeights[character] +=1;
        text = text.substr(1);
    }

    priority_queue<TreeNodeWithPriority*, vector<TreeNodeWithPriority*>, comparator> trees;
    for(auto const& x : characterWeights){
        EncodingTreeNode* leaf = new EncodingTreeNode(x.first);
        TreeNodeWithPriority* priorityLeaf = new TreeNodeWithPriority(leaf, x.second);
        trees.push(priorityLeaf);
    }

    while(trees.size() != 1){
        int priorityZero = trees.top()->priority;
        EncodingTreeNode* zero = trees.top()->treeNode;
        trees.pop();

        int priorityOne = trees.top()->priority;
        EncodingTreeNode* one = trees.top()->treeNode;
        trees.pop();

        EncodingTreeNode* newNode = new EncodingTreeNode(zero, one);

        trees.push(new TreeNodeWithPriority(newNode, priorityOne + priorityZero));
    }

    return trees.top()->treeNode;
}

/*
 * This function has an input of a EncodingTreeNode pointer to a tree, a Map with char
 * keys and string values, and a string path. For each leaf in the tree, the corresponding
 * char value is added to the map as well as the string of bits needed to reach this char
 * in the tree. To traverse this tree, the function is called recursively.
 */
void getCharacterKey(EncodingTreeNode* tree, map<char, string>& key, string path){
    if(tree->isLeaf()){
        key[tree->getChar()] = path;
        return;
    }
    getCharacterKey(tree->zero, key, path + "0");
    getCharacterKey(tree->one, key, path +  "1");
}

/*
 * Given a string and an encoding tree, the function encodes the text using the tree
 * and returns a queue<int> of the encoded bit sequence.
 *
 * To first get the corresponding bit string for each char in the tree,
 * getCharacterKey is called, which edits a Map that contains each char
 * in the tree as a key with its corresponding bit string path as its value.
 * Next, for each char in in text, the corresponding bit path is found using
 * the map. Then, this string of bits is converted to individual bits and is added
 * to the encodedText queue of bits. Finally, this queue is returned.
 */
queue<int> encodeText(EncodingTreeNode* tree, string text) {

    queue<int> encodedText;
    map<char, string> key;

    getCharacterKey(tree, key, "");

    while(text.length() != 0){
       for(char x: key[text[0]]){

           encodedText.push(x - '0');
       }

       text = text.substr(1);
    }

    return encodedText;
}

/*
 * This functions flattens the given tree into a queue<int> and queue<char>.
 *
 * The function is implemented using recursion. If the current tree node is a leaf,
 * 0 is added to the treeShape queue and the value of this leaf is added to the treeLeaves
 * queue. Otherwise, 1 is added to the treeShape queue and then the left and right substrees
 * are recursively called using the function.
 */
void flattenTree(EncodingTreeNode* tree, queue<int>& treeShape, queue<char>& treeLeaves) {
    if(tree->isLeaf()){
        treeShape.push(0);
        treeLeaves.push(tree->getChar());
        return;
    }
    treeShape.push(1);
    flattenTree(tree->zero, treeShape, treeLeaves);
    flattenTree(tree->one, treeShape, treeLeaves);
}

/*
 * This function compresses the input text using Huffman coding, producing as output
 * an EncodedData containing the encoded message and flattened
 * encoding tree used.
 *
 * This function creates an EncodedData object, and then calls
 * the buildHuffmanTree function to build a huffman tree using the
 * messageText. Next, this tree is flattened and the corresponding
 * data is stored in the treeShape and treeLeaves queue, which are then
 * added to the compressedData object. Finally, the encodeText function
 * is called to encode the message and the EncodedData is returned.
 */
EncodedData compress(string messageText) {
    EncodedData compressedData;
    EncodingTreeNode* tree = buildHuffmanTree(messageText);

    queue<int> treeShape;
    queue<char> treeLeaves;
    flattenTree(tree, treeShape, treeLeaves);

    compressedData.treeLeaves = treeLeaves;
    compressedData.treeShape = treeShape;
    compressedData.messageBits = encodeText(tree, messageText);
    deallocateTree(tree);
    return compressedData;
}

void deallocateTree(EncodingTreeNode* t) {
    if(t==nullptr){
        return;
    }
    if(t->isLeaf()){
        delete t;
        return;
    }
    deallocateTree(t->zero);
    deallocateTree(t->one);
    delete t;
}


