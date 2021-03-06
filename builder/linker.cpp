#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "token.h"
#include "node.h"

using namespace std;

Node group(vector<Token> &tokens);
Node series(vector<Token> &tokens);
Node block(vector<Token> &tokens);
Node expr(vector<Token> &tokens);
Node other(vector<Token> &tokens);
Node fillexpr(vector<Token> &tokens, Node root);
Node fillgroup(vector<Token> &tokens, Node root);
Node fillseries(vector<Token> &tokens, Node root);
Node fillblock(vector<Token> &tokens, Node root);

void debugprinttokens(vector<Token> tokens)
{
	for (int i = 0; i < tokens.size(); i++)
	{
		switch (tokens[i].type)
		{
		case groupo:
			cout << "groupo";
			break;
		case serieso:
			cout << "serieso";
			break;
		case blocko:
			cout << "blocko";
			break;
		case groupc:
			cout << "groupc";
			break;
		case seriesc:
			cout << "seriesc";
			break;
		case blockc:
			cout << "blockc";
			break;
		case str:
			cout << "str" << tokens[i].str;
			break;
		case sym:
			cout << "sym" << tokens[i].sym;
			break;
		case num:
			cout << "num" << tokens[i].num;
			break;
		case name:
			cout << "name" << tokens[i].name;
			break;
		}
		cout << " ";
	}
	cout << endl
		 << endl;
}
void debugprintlasttoken(vector<Token> tokens)
{
	cout << tokens.back().type << endl;
}
void debugprintnodes(vector<Node> nodes)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		cout << nodes[i].type;
	}
	cout << endl
		 << endl;
}
void debugprintlastnode(vector<Node> nodes)
{
	cout << "size " << nodes.size() << endl;
}
Node group(vector<Token> &tokens)
{
	Node root;
	root.type = groupnode;
	return fillgroup(tokens, root);
}
Node series(vector<Token> &tokens)
{
	Node root;
	root.type = seriesnode;
	return fillseries(tokens, root);
}
Node block(vector<Token> &tokens)
{
	Node root;
	root.type = blocknode;
	return fillblock(tokens, root);
}
Node expr(vector<Token> &tokens)
{
	Node root;
	root.type = exprnode;
	root = fillexpr(tokens, root);
	return root;
}
Node other(vector<Token> &tokens)
{
	Node root;
	switch (tokens.back().type)
	{
	case str:
		root.type = strnode;
		root.str = tokens.back().str;
		break;
	case sym:
		root.type = symnode;
		root.sym = tokens.back().sym;
		break;
	case num:
		root.type = numnode;
		root.num = tokens.back().num;
		break;
	case name:
		root.type = namenode;
		root.name = tokens.back().name;
		break;
	}
	tokens.pop_back();
	return root;
}
Node fillexpr(vector<Token> &tokens, Node root)
{
	while (tokens.size() != 0)
	{
		Token current = tokens.back();
		Node child;
		switch (current.type)
		{
		case groupo:
			tokens.pop_back();
			child = group(tokens);
			break;
		case serieso:
			tokens.pop_back();
			child = series(tokens);
			break;
		case blocko:
			tokens.pop_back();
			child = block(tokens);
			break;
		case groupc:
		case seriesc:
		case blockc:
			return root;
			break;
		case sym:
			if (current.sym == ',')
			{
				tokens.pop_back();
				return root;
			}
		default:
			child = other(tokens);
		}
		root.children.push_back(child);
	}
	return root;
}
Node fillgroup(vector<Token> &tokens, Node root)
{
	while (tokens.size() != 0)
	{
		Token current = tokens.back();
		Node child;
		switch (current.type)
		{
		case groupo:
			tokens.pop_back();
			child = group(tokens);
			break;
		case serieso:
			tokens.pop_back();
			child = series(tokens);
			break;
		case blocko:
			tokens.pop_back();
			child = block(tokens);
			break;
		case groupc:
			tokens.pop_back();
			return root;
			break;
		default:
			child = expr(tokens);
		}
		root.children.push_back(child);
	}
}
Node fillseries(vector<Token> &tokens, Node root)
{
	while (tokens.size() != 0)
	{
		Token current = tokens.back();
		Node child;
		switch (current.type)
		{
		case groupo:
			tokens.pop_back();
			child = group(tokens);
			break;
		case serieso:
			tokens.pop_back();
			child = series(tokens);
			break;
		case blocko:
			tokens.pop_back();
			child = block(tokens);
			break;
		case seriesc:
			tokens.pop_back();
			return root;
			break;
		default:
			child = expr(tokens);
		}
		root.children.push_back(child);
	}
	return root;
}
Node fillblock(vector<Token> &tokens, Node root)
{
	while (tokens.size() != 0)
	{
		Token current = tokens.back();
		Node child;
		switch (current.type)
		{
		case groupo:
			tokens.pop_back();
			child = group(tokens);
			break;
		case serieso:
			tokens.pop_back();
			child = series(tokens);
			break;
		case blocko:
			tokens.pop_back();
			child = block(tokens);
			break;
		case blockc:
			tokens.pop_back();
			return root;
			break;
		default:
			child = expr(tokens);
		}
		root.children.push_back(child);
	}
	return root;
}

Node link(vector<Token> &tokens)
{
	// check if brackets are valid
	bool good = true;
	vector<int> brackets;
	for (int i = 0; i < tokens.size(); i++)
	{
		switch (tokens[i].type)
		{
		case groupo:
			brackets.push_back(1);
			break;
		case serieso:
			brackets.push_back(2);
			break;
		case blocko:
			brackets.push_back(3);
			break;
		case groupc:
			if (brackets.size() != 0)
			{
				if (brackets.back() == 1)
				{
					brackets.pop_back();
				}
				else
				{
					good = false;
				}
			}
			else
			{
				good = false;
			}
			break;
		case seriesc:
			if (brackets.size() != 0)
			{
				if (brackets.back() == 2)
				{
					brackets.pop_back();
				}
				else
				{
					good = false;
				}
			}
			else
			{
				good = false;
			}
			break;
		case blockc:
			if (brackets.size() != 0)
			{
				if (brackets.back() == 3)
				{
					brackets.pop_back();
				}
				else
				{
					good = false;
				}
			}
			else
			{
				good = false;
			}
			break;
		}
		if (!good)
		{
			break;
		}
	}
	if (brackets.size() != 0)
	{
		good = false;
	}
	if (!good)
	{
		throw runtime_error("invalid bracket arrangement");
	}

	// reverse tokens to be able to pop seen tokens
	reverse(tokens.begin(), tokens.end());

	Node root;
	root.type = blocknode;
	return fillblock(tokens, root);
}