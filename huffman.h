#pragma once
#include "EncodedData.h"
#include "treenode.h"
#include <queue>
#include <string>
using namespace std;


void deallocateTree(EncodingTreeNode* t);

EncodingTreeNode* buildHuffmanTree(std::string messageText);

std::string decodeText(EncodingTreeNode* tree, queue<int>& messageBits);
queue<int> encodeText(EncodingTreeNode* tree, std::string messageText);

void flattenTree(EncodingTreeNode* tree, queue<int>& treeShape, queue<char>& treeLeaves);
EncodingTreeNode* unflattenTree(queue<int>& treeShape, queue<char>& treeLeaves);

EncodedData compress(std::string messageText);
std::string decompress(EncodedData& data);

