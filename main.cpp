#include <iostream>
#include "treenode.h"
#include "huffman.h"
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

void intro();
string menu();
void compressFile(); 
void decompressFile();
int convertToBaseTen(int number, int base);
string convertBase(int number, int base);


int main()
{
    intro();
    while (true) {
        string choice = menu();
        if (choice == "C"){
            break;}
        else if (choice == "A"){
            compressFile();}
        else if (choice == "B"){
            decompressFile();}
    }
    return 0;
}

/*
 * Sets up the output console
 */
void intro() {
    cout << "This program uses the Huffman coding algorithm for compression and decompression." << endl;
    cout << "Any type of file can be encoded using a Huffman code." << endl;
    cout << "Decompressing the result will faithfully reproduce the original." << endl;
}

string menu() {
    string choice;
    cout << endl;
    cout << "Choose an option:" << endl;
    cout << "A) compress file" << endl;
    cout << "B) decompress file" << endl;
    cout << "C) quit" << endl;
    cin >> choice;
    transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
    return choice;
}

/*
 * Compresses a file.
 * Prompts for input/output file names and and opens streams on those files. The compress
 * function is called to compress the file.
 */
void compressFile(){

    cout << "What is the file name to be compressed?" << endl;
    string filename;
    cin >> filename;

    ifstream infile {filename};
    string text { istreambuf_iterator<char>(infile), istreambuf_iterator<char>() };
    EncodedData data = compress(text);

    string treeShape = "";
    while(!data.treeShape.empty()){
        treeShape = treeShape + to_string(data.treeShape.front());
        data.treeShape.pop();
    }

    string treeLeaves = "";
    while(!data.treeLeaves.empty()){
        string s (1, data.treeLeaves.front());
        if(s == "\n")
            s = "\\n";
        treeLeaves = treeLeaves +  s;
        data.treeLeaves.pop();
    }

    string messageBits = "";
    while(!data.messageBits.empty()){
        messageBits = messageBits + to_string(data.messageBits.front());
        data.messageBits.pop();
    }

    cout << endl << "What do you want to call the compressed file? Please include the path and the file name." << endl;
    string compressedFile;
    cin >> compressedFile;
    ofstream outFile (compressedFile, ios::out);
    outFile << treeShape << endl;
    outFile << treeLeaves << endl;
    outFile << messageBits;
    cout << "Succesfully compressed." << endl;
}

/*
 * Decompresses a file.
 * Prompts for input/output file names and and opens streams on those files. The decompress
 * function is called to decompress the file.
 */
void decompressFile(){
    cout << "What is the file to be decompressed?" << endl;
    string filename;
    cin >> filename;

    ifstream in(filename);
    vector<string> vecOfStrs;
    string str;
    // Read the next line from file until it reaches the end.
    while (getline(in, str))
    {
        // if line contains string of length > 0 then save it in vector
        if(str.size() > 0)
            vecOfStrs.push_back(str);
    }

    if(vecOfStrs.size() != 3){
        cout << "This is not a valid file to be decompressed." << endl;
        return;
    }

    EncodedData data;
    str = vecOfStrs[0];
    for(auto it = str.begin(); it != str.end(); it++){
        data.treeShape.push(*it - '0');
    }

    str = vecOfStrs[1];
    for(auto it = str.begin(); it != str.end(); it++){
        if(it < (str.end() -1) && *it == '\\' && *(it+1) == 'n'){
            data.treeLeaves.push('\n');
            it++;
        }
        else{
            data.treeLeaves.push(*it);
        }
    }


    str = vecOfStrs[2];
    for(auto it = str.begin(); it != str.end(); it++){
        data.messageBits.push(*it - '0');
    }

    string decompressedData = decompress(data);

    cout << endl << "What do you want to call the decompressed file? Please include the path and the file name." << endl;
    string decompressedFile;
    cin >> decompressedFile;
    ofstream outFile (decompressedFile, ios::out);
    outFile << decompressedData << endl;
    cout << "Succesfully decompressed." << endl;
}







