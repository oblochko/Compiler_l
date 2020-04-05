#pragma once
#include <iostream>
#include <string>
#include "scanner.h"

using namespace std;

class compiler
{
	private:
		string name_program;
		scanner Scanner;
	public:
		compiler(string name_file);
		void scanner();
};
