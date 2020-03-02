#include <iostream>
#include <string>

#include "QMorse.h"

using namespace std;


treeNode* createTreeNode(char data)
{
	treeNode* node = new treeNode;
	node->s_data = data;
	node->s_children[LEFT] = nullptr;
	node->s_children[RIGHT] = nullptr;

	return node;
}

treeNode* createMorseTree(string dictio, int& cursor, treeNode* tree, int level)
{
	/* TEST
	cout << "level: " << level << endl;
	cout << "cursor: " << cursor << endl;
	cout << "dictio[]: " << dictio[cursor] << endl;
	cout << endl;
	*/

	tree = createTreeNode(dictio[cursor]);

	if ((level + 1) >= 8) return tree;

	level++;
	// LEFT
	cursor++;
	tree->s_children[LEFT] = createMorseTree(dictio, cursor, NULL, level);

	// RIGHT
	cursor++;
	tree->s_children[RIGHT] = createMorseTree(dictio, cursor, NULL, level);

	return tree;
}

void displayTree(treeNode* tree, int index)
{
	if (tree == nullptr) return;

	for (int i = 0; i < index; i++)
	{
		i + 1 == index ? cout << "|_" : cout << "| ";
	}

	cout << tree->s_data << endl;

	index++;

	displayTree(tree->s_children[RIGHT], index);
	displayTree(tree->s_children[LEFT], index);
}

string codingString(string data, treeNode* treeMorse)
{
	string out;
	string codeChar = "";

	for (unsigned long i = 0; i < data.size(); i++)
	{
		codeChar = codingChar(data[i], treeMorse);

		/* TEST
		cout << "codeChar: " << codeChar << endl;
		*/

		if (codeChar.empty())
		{
			out += " /";
		}
		else
		{
			out += codeChar;
			out += '/';
		}

		codeChar.assign("");
	}

	return out;
}

string codingChar(char data, treeNode* treeMorse, int index, int dir)
{
	/* TEST
	cout << "tree->data: " << treeMorse->s_data << endl << "index: " << index << endl;
	*/

	if (treeMorse == NULL) return "";

	// check and
	matchingChar(data);

	// manage special char
	if (data == '\n') return "\n";
	if (data == '\r') return "\r";

	if (data == treeMorse->s_data)
	{
		string out = "";

		if (dir == LEFT)
		{
			out.insert(0, ".");
		}
		if (dir == RIGHT)
		{
			out.insert(0, "-");
		}

		return out;
	}

	string strChildLeft = codingChar(data, treeMorse->s_children[LEFT], index + 1, LEFT);
	string strChildRight = codingChar(data, treeMorse->s_children[RIGHT], index + 1, RIGHT);

	string strTmp = "";
	if (strChildLeft != "") strTmp = strChildLeft;
	if (strChildRight != "") strTmp = strChildRight;
	if (strTmp != "")
	{
		if (dir == LEFT)
		{
			strTmp.insert(0, ".");
		}
		if (dir == RIGHT)
		{
			strTmp.insert(0, "-");
		}
		return strTmp;
	}

	return "";
}

string decodingString(string data, treeNode* treeMorse)
{
	string out;
	string codeChar = "";
	char c;

	for (unsigned long i = 0; i < data.size(); i++)
	{
		c = data[i];

		if (c == '/' && codeChar != "")
		{
			out += decodingChar(codeChar, treeMorse);
			codeChar.assign("");
		}
		else if (c == '.' || c == '-')
		{
			codeChar += c;
		}
		else if (c == ' ')
		{
			out += ' ';
			codeChar.assign("");
		}
		else
		{
			codeChar.assign("");
		}
	}

	return out;
}

char decodingChar(string data, treeNode* treeMorse, int index)
{
	if (treeMorse == nullptr || data == "") return ' ';

	if (data.size() == (unsigned long)(index - 1)) return treeMorse->s_data;

	if (data[index - 1] == '.') return decodingChar(data, treeMorse->s_children[LEFT], index + 1);
	if (data[index - 1] == '-') return decodingChar(data, treeMorse->s_children[RIGHT], index + 1);

	return ' ';
}

void matchingChar(char& data)
{
	if (((int)data >= (int)'a') && ((int)data <= (int)'z')) data -= 32;

}
