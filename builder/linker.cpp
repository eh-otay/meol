#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "token.h"
#include "node.h"

using namespace std;

node group(vector<token> &tokens);
node series(vector<token> &tokens);
node block(vector<token> &tokens);
node line(vector<token> &tokens);
node symbol(vector<token> &tokens);
node fillcode(vector<token> &tokens, node root);
node filldata(vector<token> &tokens, node root, string stopper);

node group(vector<token> &tokens)
{
	node root;
	root.type = "group";
	return filldata(tokens, root, "groupc");
}
node series(vector<token> &tokens)
{
	node root;
	root.type = "series";
	return filldata(tokens, root, "seriesc");
}
node block(vector<token> &tokens)
{
	node root;
	root.type = "block";
	return fillcode(tokens, root);
}
node line(vector<token> &tokens)
{
	node root;
	root.type = "line";
	return filldata(tokens, root, "linee");
}
node symbol(vector<token> &tokens)
{
	node root;
	root.type = tokens.back().type;
	root.value = tokens.back().value;
	tokens.pop_back();
	return root;
}
node fillcode(vector<token> &tokens, node root)
{
	while (tokens.size() != 0)
	{
		token current = tokens.back();
		node child;
		if (current.type == "groupo")
		{
			tokens.pop_back();
			child = group(tokens);
		}
		else if (current.type == "serieso")
		{
			tokens.pop_back();
			child = series(tokens);
		}
		else if (current.type == "blocko")
		{
			tokens.pop_back();
			child = block(tokens);
		}
		else if (current.type == "blockc")
		{
			tokens.pop_back();
			break;
		}
		else
		{
			child = line(tokens);
		}
		root.children.push_back(child);
	}
	return root;
}
node filldata(vector<token> &tokens, node root, string stopper)
{
	while (tokens.size() != 0)
	{
		token current = tokens.back();
		node child;
		if (current.type == "groupo")
		{
			tokens.pop_back();
			child = group(tokens);
		}
		else if (current.type == "serieso")
		{
			tokens.pop_back();
			child = series(tokens);
		}
		else if (current.type == "blocko")
		{
			tokens.pop_back();
			child = block(tokens);
		}
		else if (current.type == stopper)
		{
			tokens.pop_back();
			break;
		}
		else
		{
			child = symbol(tokens);
		}
		root.children.push_back(child);
	}
	return root;
}

node link(vector<token> &tokens)
{
	// check if brackets are valid
	bool good = true;
	vector<int> brackets;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].type == "groupo")
		{
			brackets.push_back(1);
		}
		if (tokens[i].type == "serieso")
		{
			brackets.push_back(2);
		}
		if (tokens[i].type == "blocko")
		{
			brackets.push_back(3);
		}
		if (tokens[i].type == "groupc")
		{
			if (brackets.size() != 0)
			{
				if (brackets.back() == 1)
				{
					brackets.pop_back();
				}
				else
				{
					good = true;
				}
			}
			else
			{
				good = true;
			}
		}
		if (tokens[i].type == "seriesc")
		{
			if (brackets.size() != 0)
			{
				if (brackets.back() == 2)
				{
					brackets.pop_back();
				}
				else
				{
					good = true;
				}
			}
			else
			{
				good = true;
			}
		}
		if (tokens[i].type == "blockc")
		{
			if (brackets.size() != 0)
			{
				if (brackets.back() == 3)
				{
					brackets.pop_back();
				}
				else
				{
					good = true;
				}
			}
			else
			{
				good = true;
			}
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

	node root;
	root.type = "root";
	return fillcode(tokens, root);
}