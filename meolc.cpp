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

void printtokens(vector<Token> tokens)
{
	for (int i = 0; i < tokens.size(); i++)
	{
		switch (tokens[i].type)
		{
		case groupo:
			cout << "groupo" << endl;
			break;
		case serieso:
			cout << "serieso" << endl;
			break;
		case blocko:
			cout << "blocko" << endl;
			break;
		case groupc:
			cout << "groupc" << endl;
			break;
		case seriesc:
			cout << "seriesc" << endl;
			break;
		case blockc:
			cout << "blockc" << endl;
			break;
		case str:
			cout << "str\t" << tokens[i].str << endl;
			break;
		case sym:
			cout << "sym\t" << tokens[i].sym << endl;
			break;
		case num:
			cout << "num\t" << tokens[i].num << endl;
			break;
		case name:
			cout << "name\t" << tokens[i].name << endl;
			break;
		}
	}
}
void printtree(Node root, int count){
	string tabs(count, '\t');
	switch(root.type){
		case groupnode:
		cout << tabs << "group\t" << endl;
		for(int i = 0;i < root.children.size();i++){
			printtree(root.children[i], count + 1);
		}
		break;
		case seriesnode:
		cout << tabs << "series\t" << endl;
		for(int i = 0;i < root.children.size();i++){
			printtree(root.children[i], count + 1);
		}
		break;
		case blocknode:
		cout << tabs << "block\t" << endl;
		for(int i = 0;i < root.children.size();i++){
			printtree(root.children[i], count + 1);
		}
		break;
		case exprnode:
		cout << tabs << "expr\t" << endl;
		for(int i = 0;i < root.children.size();i++){
			printtree(root.children[i], count + 1);
		}
		break;
		case strnode:
		cout << tabs << "str\t" << root.str << endl;
		break;
		case symnode:
		cout << tabs << "sym\t" << root.sym << endl;
		break;
		case numnode:
		cout << tabs << "num\t" << root.num << endl;
		break;
		case namenode:
		cout << tabs << "name\t" << root.name << endl;
		break;
	}
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
		cout << endl << endl;
		printtokens(tokens);
		cout << endl << endl;
	}
	catch (exception &e)
	{
		cout << "division error: " << e.what() << endl;
	}
	cout << "done" << endl;

	cout << "linking" << endl;
	Node root;
	try
	{
		root = link(tokens);
		printtree(root, 0);
	}
	catch (exception &e)
	{
		cout << e.what();
	}
	cout << "done" << endl;

	return 0;
}