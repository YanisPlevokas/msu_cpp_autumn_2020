#include <iostream>
#include <string>
using namespace std;
#include "parser_header.hpp"


void TokenParser::gc()
{
	c = fgetc(filePointer);
}
void TokenParser::SetStartCallback(void (*function_callback_new) () )
{
	function_callback = function_callback_new;
	callbackFlag = true;
}
void TokenParser::SetDigitTokenCallback(void (*function_set_digit_new) (int))
{
	function_digit = function_set_digit_new;
	digitFlag = true;
}
void TokenParser::SetStringTokenCallback(void (*function_set_string_new) (string))
{
	function_string = function_set_string_new;
	stringFlag = true;
}
bool TokenParser::StartParsing(const char* text_name)
{
	enum state
	{
		H, IDENT, NUMB
	};
	if ((filePointer = fopen(text_name, "r")) == NULL)
	{
		cout << "Cannot open file.\n";
		return true;
	}
	flagFile = true;

	if ( !(callbackFlag && digitFlag && stringFlag) )
	{
		cout << "You didn't declare functions. Try again.\n";
		return true;
	}
	string buf;
	function_callback();
	state CS = H;
	do
	{
		gc();
		switch (CS)
		{
		case H:
			if (isspace(c));
			else
				if (!isdigit(c) && c != EOF)
				{
					buf.push_back(c);
					CS = IDENT;
				}
				else
					if (isdigit(c))
					{
						buf.push_back(c);
						CS = NUMB;
					}
					else
						if (c == EOF)
						{
							fclose(filePointer);
							flagFile = false;
							return false;
						}
			break;
		case IDENT:
			if (c != EOF && !isspace(c))
			{
				buf.push_back(c);
			}
			else if (isspace(c))
			{
				CS = H;
				function_string(buf);
				buf.clear();
			}
			else if (c == EOF)
			{
				function_string(buf);
				fclose(filePointer);
				flagFile = false;
				return false;
			}
			break;
		case NUMB:
			if (isdigit(c))
			{
				buf.push_back(c);
			}
			else if (!isdigit(c) && (c != EOF && !isspace(c)))
			{
				buf.push_back(c);
				CS = IDENT;
			}
			else if (c != EOF)
			{
				CS = H;
				function_digit(stoi(buf));
				buf.clear();
			}
			else
			{
				function_digit(stoi(buf));
				fclose(filePointer);
				flagFile = false;
				return false;
			}
			break;
		
		default:
			break;
		}
	} 
while (1);
return false;
}

TokenParser::~TokenParser()
{
	callbackFlag = false;
	digitFlag = false;
	stringFlag = false;
	if (flagFile)
		fclose(filePointer);
}
