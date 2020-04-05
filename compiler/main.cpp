#include <iostream>
#include "compiler.h"

using namespace std;

int main()
{
	compiler compiler_main("text program/text2.txt");
	compiler_main.scanner();
	return 0;
}