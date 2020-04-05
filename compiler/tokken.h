#pragma once

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>

using namespace std;

enum token_name
{
	token_indentifiter,
	token_keyword,
	token_separator,
	token_operator,
	token_literal,
	token_comment
};

enum state
{
	state_empty,
	state_indentifiter,
	state_literal,
	state_literal_fractional,
	state_separator,
	state_operator,
	state_comment,
	state_comment_star,
	state_comment_star_star,
	state_comment_slash,
	state_space,
	state_error
};

class token
{
	public:
		static vector<token> enum_token;
		static vector<string> enum_keyword;
	private:		
		string name_token_value;
		string value;
	public:
		static void import_standart_keywords();
		static void import_fmt_keywords();
		static void vector_show();
	public:
		token(token_name _token_name, string _value);		
		void show();
};