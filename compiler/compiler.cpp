#include "compiler.h"

compiler::compiler(string name_file)
{
	name_program = name_file;
}

void compiler::scanner()
{
	Scanner.init(name_program); 
	Scanner.state_machine();

}