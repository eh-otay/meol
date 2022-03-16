#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

node linker(vector<node> divcode)
{
	node root;
	while (divcode.size() != 0)
	{
	}
	return root;
}

node link(vector<node> divcode)
{
	vector<node> nodes = divcode;

	bool good = true;
	vector<int> brackets;
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].type == "groupo")
		{
			brackets.push_back(1);
		}
		if (nodes[i].type == "serieso")
		{
			brackets.push_back(2);
		}
		if (nodes[i].type == "blocko")
		{
			brackets.push_back(3);
		}
		if (nodes[i].type == "groupc")
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
		if (nodes[i].type == "seriesc")
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
		if (nodes[i].type == "blockc")
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
		cout << ((brackets.size() > 0) ? to_string(brackets.back()) : "") << "\t" << nodes[i].type << "\t" << nodes[i].self << endl;
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

	node root;
	reverse(nodes.begin(), nodes.end());
	root = linker(nodes);
	return root;
}