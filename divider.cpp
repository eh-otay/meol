#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<node> divide(string src){
	vector<node> divcode;
	node current;

	string numbers = ".01234566789";
	string whitespaces = " \t\n\r";
	string specials = "()[]{},;$<\"";
	string terminators = whitespaces + specials;

	// tools for dividing
	bool inquote = false;
	bool incomment = false;
	bool escape = false;
	int line = 1;
	int ch = 1;

	for(int i = 0;i < src.size();i++){
		char c = (char) src[i];

		// for error detection during division
		if(c == '\n'){
			line++;
			ch = 1;
		}else{
			ch ++;
		}

		if(inquote){ // dividing while in string
			if(escape){ // escaping - next character is always escaped
				current.self.push_back(c);
				escape = false;
			}else{ // not escaping - check for end of string and escape
				if(c == '\"'){
					inquote = false;
					divcode.push_back(current);
					current.self = "";
					current.type = "";
				}else{
					if(c == '\\'){
						escape = true;
					}
					current.self.push_back(c);
				}
			}
		}else if (incomment){ // dividing while in comment
			if(c == '>'){
				incomment = false;
			}
		}else{ // dividing outside
			if(terminators.find(c) != string::npos){ // on terminator
				// terminate old node if exists
				if(current.self != ""){
					divcode.push_back(current);
					current.self = "";
					current.type = "";
				}
				if(specials.find(c) != string::npos){ // on special
					// assign node types
					switch(c){
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
						case ',':
						current.type = "iteme";
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

					// some specials are entire nodes
					if(((string)"()[]{},;$").find(c) != string::npos){
						current.self.push_back(c);
						divcode.push_back(current);
						current.self = "";
					current.type = "";
					}
				}
			}else{ // not terminator, so part of token name
				if(current.type == ""){ // unknown type, guess with first character
					if(numbers.find(c) != string::npos){
						current.type = "num";
					}else{
						current.type = "token";
					}
					current.self.push_back(c);
				}else{ // known type, make sure number is valid
					if(current.type == "num"){
						if(count(current.self.begin(),current.self.end(), '.') > 1){
							throw runtime_error("invalid number at "+to_string(line)+":"+to_string(ch)+":\n"+current.self);
						}else if(current.self[0] == '.'){
							throw runtime_error("invalid number at "+to_string(line)+":"+to_string(ch)+":\n"+current.self);
						}else{
							current.self.push_back(c);
						}
					}else{
						current.self.push_back(c);
					}
				}
			}
		}
	}
	return divcode;
}