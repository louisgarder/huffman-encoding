# huffman-encoding
This program uses the Huffman coding algorithm for compression and decompression. The purpose of this program is to compress any large text files. The same program
can also be used to decompress the resulting compressed file and faithfully reproduce the original.

To run this project, open HuffmanEncoding.pro with qtcreator. 
The main.cpp source code file contains the code that prompts for the input file name be compressed/decompressed and the output file name
where the resulting data will be saved. When providng file names, include both the file name and the path.

The EncodedData.h and treenode.h header files contain the code for the types representing a binary-encoded message and a node in an encoding tree
respectively. View these files for more information on how these types work and the functions/variables available. 

The huffman.cpp source code file contains all of the code for the actual implementation of the huffman compression and decompression algorithms. For more 
information on how these algorithms are implemented, view the code and comments in the source file.

This project was created and is mantained by Raymond Suo. For any questions, pleae email rms7988@gmail.com

