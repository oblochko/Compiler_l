#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "tokken.h"

using namespace std;



class scanner
{
	private:
		string name_file;
		vector<char> enum_separetor;
		vector<char> enum_operator;
		//vector<string> enum_keyword;
	public:
		scanner();
		scanner(string _name_file);
		void init(string _name_file);
		void determine_the_state(string _symbol, state& _state);
		void state_machine();

};
