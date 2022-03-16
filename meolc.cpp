#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "builder/node.h"
#include "builder/divider.cpp"
#include "builder/linker.cpp"
using namespace std;

string readfile(string name){
	string content;
	char ch;
	ifstream src(name);

	if (!src.is_open()) {
		return NULL;
	}

	while (src.get(ch)) {
		content.push_back(ch);
	}

	src.close();

	return content;
}

int main(int argc, char *argv[]){
	string srccode = readfile(argv[1]);
	vector<node> divcode;
	node tree;

	try{
		divcode = divide(srccode);
		for(int i = 0;i < divcode.size();i++){
			cout << divcode[i].type << "\t" << divcode[i].self << endl;
		}
	}catch(exception& e){
		cout << e.what();
	}

	cout << endl << endl;

	try{
		tree = link(divcode);
		cout << tree.self << endl;
	}catch(exception& e){
		cout << e.what();
	}

	return 0;
}