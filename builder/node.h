
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

using namespace std;

struct node
{
	string value;
	string type;
	vector<node> children;
};

#endif