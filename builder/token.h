
#ifndef TOKEN_H
#define TOKEN_H

#include <vector>
#include <string>

using namespace std;

enum TokenType {groupo, groupc, serieso, seriesc, blocko, blockc, str, sym, num, name};

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