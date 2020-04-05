#include "tokken.h"

vector<token> token::enum_token;
vector<string> token::enum_keyword;

token::token(token_name _token_name, string _value)
{
	value = _value;
	switch(_token_name)
	{
		case token_indentifiter:
		{
			name_token_value = "indentifiter";
			for (int i = 0; i < enum_keyword.size(); i++)
			{
				if (_value == enum_keyword[i])
				{
					name_token_value = "keyword";
					break;
				}
			}
			break;
		}

		/*case token_keyword:
		{
			name_token_value = "keyword";
			break;
		}*/

		case token_separator:
		{
			name_token_value = "separator";
			break;
		}
		
		case token_operator:
		{
			name_token_value = "operator";
			break;
		}

		case token_literal:
		{
			name_token_value = "literal";
			break;
		}

		case token_comment:
		{
			name_token_value = "comment";
			break;
		}
	}
}

void token::import_standart_keywords()
{
	string temp_keyword;
	fstream fin("key word/standart keywords.txt");
	if (!fin.is_open())
	{
		cout << "file not open" << endl;
		return;
	}
	for (; !fin.eof();)
	{
		fin >> temp_keyword;
		enum_keyword.push_back(temp_keyword);
	}
}

void token::import_fmt_keywords()
{
	string temp_keyword;
	fstream fin("key word/fmt keywords.txt");
	if (!fin.is_open())
	{
		cout << "file not open" << endl;
		return;
	}
	for (; !fin.eof();)
	{
		fin >> temp_keyword;
		enum_keyword.push_back(temp_keyword);
	}
	/*for (int i = 0; i < enum_keyword.size(); i++)
		cout << enum_keyword[i] << " ";
	cout << endl;*/
}

void token::vector_show()
{
	for (int i = 0; i < token::enum_token.size(); i++)
	{
		token::enum_token[i].show();
		cout << endl;
	}
}

void token::show()
{
	cout << name_token_value << " " << value;
}
