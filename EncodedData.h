#pragma once
#include <treenode.h>
#include <ostream>
#include <queue>
using namespace std;


/*
 * Type representing a binary-encoded message. The messageBits contains
 * the encoded message text and the treeShape and treeLeaves are the
 * flattened representation of the encoding tree. treeShape and 
 * messageBits can only contain the int 0 or 1.
 */
struct EncodedData {
    queue<int>  treeShape;
    queue<char> treeLeaves;
    queue<int>  messageBits;
};


