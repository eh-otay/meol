#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "token.h"

using namespace std;

vector<Token> div(string &src);
Token divname(string &src);
Token divnum(string &src) throw (runtime_error);
void divcmt(string &src);
Token divsym(char c);
Token divstr(string &src);
vector<Token> divide(string src);

vector<Token> div(string &src)
{
	string numbers = ".01234566789";
	string whitespaces = " \t\n\r";
	string structures = "()[]{}#\"";
	string symbols = ";+-*/%=$";
	string terminators = whitespaces + structures + symbols;

	vector<Token> tokens;
	while (src.size() != 0)
	{
		char c = src.back();
		if (c == '(')
		{
			src.pop_back();
			Token token;
			token.type = groupo;
			tokens.push_back(token);
		}
		else if (c == '[')
		{
			src.pop_back();
			Token token;
			token.type = serieso;
			tokens.push_back(token);
		}
		else if (c == '{')
		{
			src.pop_back();
			Token token;
			token.type = blocko;
			tokens.push_back(token);
		}
		else if (c == ')')
		{
			src.pop_back();
			Token token;
			token.type = groupc;
			tokens.push_back(token);
		}
		else if (c == ']')
		{
			src.pop_back();
			Token token;
			token.type = seriesc;
			tokens.push_back(token);
		}
		else if (c == '}')
		{
			src.pop_back();
			Token token;
			token.type = blockc;
			tokens.push_back(token);
		}
		else if (c == '#')
		{
			src.pop_back();
			divcmt(src);
		}
		else if (c == '\"')
		{
			src.pop_back();
			tokens.push_back(divstr(src));
		}
		else if (symbols.find(c) != string::npos)
		{
			src.pop_back();
			tokens.push_back(divsym(c));
		}
		else
		{
			if (whitespaces.find(c) == string::npos)
			{
				if (numbers.find(c) != string::npos)
				{
					try
					{
						tokens.push_back(divnum(src));
					}
					catch (runtime_error e)
					{
						cout << e.what() << endl;
						break;
					}
				}
				else
				{
					tokens.push_back(divname(src));
				}
			}else{
				src.pop_back();
			}
		}
	}
	return tokens;
}
Token divname(string &src)
{
	string whitespaces = " \t\n\r";
	string structures = "()[]{}";
	string symbols = ";<\"+-*/%=$";
	string terminators = whitespaces + structures + symbols;
	Token token;
	token.type = name;
	while (terminators.find(src.back()) == string::npos)
	{
		token.name.push_back(src.back());
		src.pop_back();
	}
	return token;
}
Token divnum(string &src) throw (runtime_error)
{
	string numbers = ".01234566789";
	string whitespaces = " \t\n\r";
	string structures = "()[]{}";
	string symbols = ";<\"+-*/%=$";
	string terminators = whitespaces + structures + symbols;
	string number;
	while (src.size() != 0)
	{
		char c = src.back();
		if (numbers.find(c) != string::npos)
		{
			number.push_back(c);
			src.pop_back();
		}
		else if (terminators.find(c) != string::npos)
		{
			Token token;
			token.type = num;
			token.num = stod(number);
			return token;
		}
		else
		{
			throw runtime_error("invalid number");
		}
	}
}
void divcmt(string &src)
{
	while (src.size() != 0)
	{
		src.pop_back();
		if (src.back() == '\n')
		{
			break;
		}
	}
}
Token divsym(char c)
{
	cout << c << endl;
	Token token;
	token.type = sym;
	token.sym = c;
	return token;
}
Token divstr(string &src)
{
	Token token;
	token.type = str;
	bool escape = false;
	while (src.size() != 0)
	{
		char c = src.back();
		if (escape)
		{ // escaping - next character is always escaped
			token.str.push_back(c);
			src.pop_back();
			escape = false;
		}
		else
		{ // not escaping - check for end of string and escape
			if (c == '\"')
			{
				return token;
			}
			else
			{
				if (c == '\\')
				{
					escape = true;
				}
				token.str.push_back(c);
				src.pop_back();
			}
		}
	}
}
vector<Token> divide(string src)
{
	vector<Token> tokens;
	Token current;

	string numbers = ".01234566789";
	string whitespaces = " \t\n\r";
	string structures = "()[]{};<\"+-*/%=$";
	string terminators = whitespaces + structures;

	// tools for dividing
	bool inquote = false;
	bool incomment = false;
	bool escape = false;

	// reverse to pop back
	reverse(src.begin(), src.end());

	return div(src);
}