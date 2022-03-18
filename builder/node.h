#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

using namespace std;

enum NodeType{groupnode, seriesnode, blocknode, linenode, strnode, symnode, numnode, namenode};

class Node
{
public:
	NodeType type;
	vector<Node> children;
	string str;
	char sym;
	double num;
	string name;
};

#endif