#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "builder/token.h"
#include "builder/node.h"
#include "builder/divider.cpp"
#include "builder/linker.cpp"

using namespace std;

string readfile(string name)
{
	string content;
	char ch;
	ifstream src(name);

	if (!src.is_open())
	{
		return NULL;
	}

	while (src.get(ch))
	{
		content.push_back(ch);
	}

	src.close();

	return content;
}

void printrecursive(Node tree, int count){
}
void printtree(Node tree){
	printrecursive(tree, 0);
}

int main(int argc, char *argv[])
{
	cout << "reading" << endl;
	string srccode = readfile(argv[1]);
	cout << "done" << endl;

	cout << "dividing" << endl;
	vector<Token> tokens;
	try
	{
		tokens = divide(srccode);
	}
	catch (exception &e)
	{
		cout << e.what();
	}
	cout << "done" << endl;

	cout << "linking" << endl;
	Node tree;
	try
	{
		tree = link(tokens);
		printtree(tree);
	}
	catch (exception &e)
	{
		cout << e.what();
	}
	cout << "done" << endl;

	return 0;
}