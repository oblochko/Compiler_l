#include "scanner.h"

scanner::scanner()
{

}

scanner::scanner(string _name_file)
{
	name_file = _name_file;
}

void scanner::init(string _name_file)
{
	name_file = _name_file;
	//enum_seperetor = { "(", ")", "{", "}", "\'", "\"" };
	enum_separetor = { '(', ')', '{', '}', '\'', '\"', ',', ';' };
	enum_operator = { '+', '-', '*', '%', '[', ']', '.', ':', '=', '<', '>', '!'};
	token::import_standart_keywords();
	token::import_fmt_keywords();
	//enum_keyword = { "package", "main", "import", "func", "main", "fmt", "Println"};
}

void scanner::determine_the_state(string _symbol, state& _state)
{		
	if (isalpha(_symbol[0]) || _symbol[0] == '_')
	{
		_state = state_indentifiter;
		return;
	}
	if (isdigit(_symbol[0]))
	{
		_state = state_literal;
		return;
	}
	for (int i = 0; i < enum_separetor.size(); i++)
	{
		if (_symbol[0] == enum_separetor[i])
		{
			_state = state_separator;
			return;
		}
	}
	for (int i = 0; i < enum_operator.size(); i++)
	{
		if (_symbol[0] == enum_operator[i])
		{
			_state = state_operator;
			return;
		}
	}
	if (_symbol[0] == '/')
	{
		_state = state_comment;
		return;
	}
	if (isspace(_symbol[0]))
	{
		_state = state_space;
	}
	_state = state_error;
	return;
}

void scanner::state_machine()
{
	char temp[2]="";
	//char temp;
	string lambda;
	state current_state = state_empty;
	fstream fin(name_file.c_str());
	if (!fin.is_open())
	{
		cout << "file not open" << endl;
		return; 
	}
	//fin >> temp;
	fin.get(temp[0]);
	//fin >> lambda;
	lambda = string(temp);
	determine_the_state(lambda, current_state);
	while (!fin.eof() && current_state != state_error)
	{
		switch (current_state)
		{
			case state_indentifiter:
			{
				if (!fin.get(temp[0]) || isspace(temp[0]) || temp[0] == '\n')
				{
					/*if (temp[0] == '\n')
						cout << "end of line" << endl;*/
					//cout << lambda << endl;
					token token_temp(token_indentifiter, lambda);
					token::enum_token.push_back(token_temp);
					current_state = state_space;
					break;
				}
				//state temp_state;
				determine_the_state(string(temp), current_state);
				//if (isalpha(temp[0]) || isdigit(temp[0]) || temp[0] == '_')	
				if (current_state == state_indentifiter || current_state == state_literal)
				{
					lambda += string(temp);
					current_state = state_indentifiter;
					break;
				}

				if (current_state == state_separator || current_state == state_operator)
				{
					token token_temp(token_indentifiter, lambda);
					token::enum_token.push_back(token_temp);
					break;
				}
				// если оператор или сеператор стоят в упор, то индентификатор не запишется и будет выход с ошибкой
				current_state = state_error;
				break;
			}

			case state_literal:
			{
				if (!fin.get(temp[0]) || isspace(temp[0]) || temp[0] == '\n')
				{
					//cout << lambda << endl;
					token token_temp(token_literal, lambda);
					token::enum_token.push_back(token_temp);
					current_state = state_space;
					break;
				}

				if (isdigit(temp[0]))
				{
					lambda += string(temp);
					current_state = state_literal;
					break;
				}

				if (temp[0] == '.')
				{
					lambda += string(temp);
					current_state = state_literal_fractional;
					break;
				}

				determine_the_state(string(temp), current_state);
				if (current_state == state_separator || current_state == state_operator)
				{
					token token_temp(token_indentifiter, lambda);
					token::enum_token.push_back(token_temp);
					break;
				}
				current_state = state_error;
				break;
			}

			case state_literal_fractional:
			{
				if (!fin.get(temp[0]) || isspace(temp[0]) || temp[0] == '\n')
				{
					//cout << lambda << endl;
					token token_temp(token_literal, lambda);
					token::enum_token.push_back(token_temp);
					current_state = state_space;
					break;
				}

				if (isdigit(temp[0]))
				{
					lambda += string(temp);
					current_state = state_literal;
					break;
				}

				determine_the_state(string(temp), current_state);
				if (current_state == state_separator || current_state == state_operator)
				{
					token token_temp(token_indentifiter, lambda);
					token::enum_token.push_back(token_temp);
					break;
				}

				current_state = state_literal_fractional;
				break;
			}

			case state_separator:
			{
				lambda = string(temp);
				token token_temp(token_separator, lambda);
				token::enum_token.push_back(token_temp);
				current_state = state_space;
				break;
			}

			case state_operator:
			{
				lambda = string(temp);
				token token_temp(token_operator, lambda);
				token::enum_token.push_back(token_temp);
				current_state = state_space;
				break;
			}

			case state_comment:
			{
				fin.get(temp[0]);
				lambda.clear();
				if (temp[0] == '/')
				{
					current_state = state_comment_slash;
					break;
				}
				if (temp[0] == '*')
				{
					current_state = state_comment_star;
					break;
				}
				current_state = state_error;
				break;
			}

			case state_comment_slash:
			{
				if (!fin.get(temp[0]) || temp[0] == '\n')
				{

					token token_temp(token_comment, lambda);
					token::enum_token.push_back(token_temp);
					current_state = state_space;
					break;
				}
				lambda += string(temp);
				current_state = state_comment_slash;
				break;
			}

			case state_comment_star:
			{
				if (!fin.get(temp[0]) || temp[0] == '*')
				{						
					current_state = state_comment_star_star;
					break;
				}
				lambda += string(temp);
				current_state = state_comment_star;
				break;
			}

			case state_comment_star_star:
			{
				if (!fin.get(temp[0]) || temp[0] == '/')
				{
					token token_temp(token_comment, lambda);
					token::enum_token.push_back(token_temp);
					current_state = state_space;
					break;
				}
				lambda += "*" + string(temp);
				current_state = state_comment_star_star;
				break;
			}

			case state_space:
			{
				//fin >> temp;
				fin.get(temp[0]);
				if (isspace(temp[0]))
				{
					//token Token(token_indentifiter, lambda);
					//token::enum_token.push_back(Token);
					current_state = state_space;
				}
				else 
				{
					lambda = string(temp);
					determine_the_state(lambda, current_state);
				}
				
				break;
			}

			default:
			{
				current_state = state_error;
				break;
			}
		}		
	}
	token::vector_show();
}


