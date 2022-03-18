
#ifndef TOKEN_H
#define TOKEN_H

#include <vector>
#include <string>

using namespace std;

enum TokenType {groupo, serieso, blocko, groupc, seriesc, blockc, str, sym, num, name};

class Token
{
	public:
	TokenType type;
	string str;
	char sym;
	double num;
	string name;
};

#endif