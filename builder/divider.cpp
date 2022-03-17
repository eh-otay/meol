#include <string>
#include <vector>
#include <algorithm>
#include "token.h"

using namespace std;

vector<token> divide(string src)
{
	vector<token> divcode;
	token current;

	string numbers = ".01234566789";
	string whitespaces = " \t\n\r";
	string specials = "()[]{};$<\"";
	string terminators = whitespaces + specials;

	// tools for dividing
	bool inquote = false;
	bool incomment = false;
	bool escape = false;
	int line = 1;
	int ch = 1;

	for (int i = 0; i < src.size(); i++)
	{
		char c = (char)src[i];

		// for error detection during division
		if (c == '\n')
		{
			line++;
			ch = 1;
		}
		else
		{
			ch++;
		}

		if (inquote)
		{ // dividing while in string
			if (escape)
			{ // escaping - next character is always escaped
				current.value.push_back(c);
				escape = false;
			}
			else
			{ // not escaping - check for end of string and escape
				if (c == '\"')
				{
					inquote = false;
					divcode.push_back(current);
					current.value = "";
					current.type = "";
				}
				else
				{
					if (c == '\\')
					{
						escape = true;
					}
					current.value.push_back(c);
				}
			}
		}
		else if (incomment)
		{ // dividing while in comment
			if (c == '>')
			{
				incomment = false;
			}
		}
		else
		{ // dividing outside
			if (terminators.find(c) != string::npos)
			{ // on terminator
				// terminate old token if exists
				if (current.value != "")
				{
					divcode.push_back(current);
					current.value = "";
					current.type = "";
				}
				if (specials.find(c) != string::npos)
				{ // on special
					// assign token types
					switch (c)
					{
					case '(':
						current.type = "groupo";
						break;
					case ')':
						current.type = "groupc";
						break;
					case '[':
						current.type = "serieso";
						break;
					case ']':
						current.type = "seriesc";
						break;
					case '{':
						current.type = "blocko";
						break;
					case '}':
						current.type = "blockc";
						break;
					case ';':
						current.type = "linee";
						break;
					case '$':
						current.type = "value";
						break;
					case '<':
						incomment = true;
						break;
					case '\"':
						inquote = true;
						current.type = "str";
						break;
					}

					// some specials are entire tokens
					if (((string) "()[]{};$").find(c) != string::npos)
					{
						current.value.push_back(c);
						divcode.push_back(current);
						current.value = "";
						current.type = "";
					}
				}
			}
			else
			{ // not terminator, so part of token name
				if (current.type == "")
				{ // unknown type, guess with first character
					if (numbers.find(c) != string::npos)
					{
						current.type = "num";
					}
					else
					{
						current.type = "symbol";
					}
					current.value.push_back(c);
				}
				else
				{ // known type, make sure number is valid
					if (current.type == "num")
					{
						if (count(current.value.begin(), current.value.end(), '.') > 1)
						{
							throw runtime_error("invalid number at " + to_string(line) + ":" + to_string(ch) + ":\n" + current.value);
						}
						else if (current.value[0] == '.')
						{
							throw runtime_error("invalid number at " + to_string(line) + ":" + to_string(ch) + ":\n" + current.value);
						}
						else
						{
							current.value.push_back(c);
						}
					}
					else
					{
						current.value.push_back(c);
					}
				}
			}
		}
	}
	return divcode;
}