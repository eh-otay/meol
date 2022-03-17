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

void printrecursive(node tree, int count){
	string value = "";
	if(!tree.value.empty()){
		value = tree.value;
	}
	string tabs(count, '\t');
	cout << tabs << tree.type << "\t" << tree.value << endl;
	for(int i = 0;i < tree.children.size();i++){
		printrecursive(tree.children[i], count+1);
	}
}
void printtree(node tree){
	printrecursive(tree, 0);
}

int main(int argc, char *argv[])
{
	string srccode = readfile(argv[1]);
	vector<token> divcode;
	node tree;

	try
	{
		divcode = divide(srccode);
	}
	catch (exception &e)
	{
		cout << e.what();
	}

	try
	{
		tree = link(divcode);
		printtree(tree);
	}
	catch (exception &e)
	{
		cout << e.what();
	}

	return 0;
}