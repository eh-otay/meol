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
Node line(vector<Token> &tokens);
Node other(vector<Token> &tokens);
Node fillline(vector<Token> &tokens, Node root);
Node fillgroup(vector<Token> &tokens, Node root);
Node fillseries(vector<Token> &tokens, Node root);
Node fillblock(vector<Token> &tokens, Node root);

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
Node line(vector<Token> &tokens)
{
	Node root;
	root.type = linenode;
	return fillline(tokens, root);
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
Node fillline(vector<Token> &tokens, Node root)
{

	while (tokens.size() != 0)
	{
		Token current = tokens.back();
		Node child;
		bool linee = false;
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
		case sym:
			if (current.sym == ';')
			{
				return root;
			}
		default:
			child = other(tokens);
		}
		root.children.push_back(child);
	}
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
			return root;
			break;
		default:
			child = other(tokens);
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
			return root;
			break;
		default:
			child = other(tokens);
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
			return root;
			break;
		default:
			child = line(tokens);
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
	return fillblock(tokens, root);
}