#ifndef QMORSE_H
#define QMORSE_H

#define LEFT 0
#define RIGHT 1

#include <string>

using namespace std;

static string dictio = " EISH5  4  V   3  UF        ?_2  ARL&   \"  + .   WP    @ J   1' TNDB6 -=  X/     KC    ;!Y( )   MGZ7    ,Q      O 8:     9  0  ";

struct treeNode
{
	char s_data;
	struct treeNode* s_children[2];
};

treeNode* createTreeNode(char data);
treeNode* createMorseTree(string dictio, int &cursor, treeNode* tree=nullptr, int level=1);
void displayTree(treeNode* tree, int index=0);

// coding
string codingString(string data, treeNode* treeMorse);
string codingChar(char data, treeNode* treeMorse, int index=1, int dir=-1);

// decoding
string decodingString(string data, treeNode* treeMorse);
char decodingChar(string data, treeNode* treeMorse, int index=1);

// checks and converts unknown characters to Morse code
void matchingChar(char &data);


#endif // QMORSE_H
