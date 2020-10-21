#include <iostream>
#include <string>
using namespace std;
#include "parser_header.hpp"


TokenParser::TokenParser()
{
	callbackFlag = false;
	stringFlag = false;
	digitFlag = false;
}
void TokenParser::SetStartCallback(const callback& functionCallbackNew)
{
	functionCallback = functionCallbackNew;
	callbackFlag = true;
}
void TokenParser::SetDigitTokenCallback(const digit& functionSetDigitNew)
{
	functionDigit = functionSetDigitNew;
	digitFlag = true;
}
void TokenParser::SetStringTokenCallback(const stringFunc &functionSetStringNew)
{
	functionString = functionSetStringNew;
	stringFlag = true;
}
string TokenParser::StartParsing(const string& textName)
{
	string resultString = "";
	string buf = "";
	if ( !(callbackFlag && digitFlag && stringFlag) )
	{
		resultString = "You didn't declare functions. Try again.";
		return resultString;
	}
	bool spaceFlag = true;
	bool digitFlag = true;
	resultString += functionCallback(); // starting callback function
	for (const char & c: textName)
	{
		if (isspace(c))
		{
			if (!spaceFlag)
			{
				if (digitFlag) // If it is number
				{
					resultString += functionDigit(stoi(buf));
				}
				else // it is string
				{
					resultString += functionString(buf);
				}
				buf = "";
				digitFlag = true;
				spaceFlag = true;
				continue;
			}
		}
		else
		{
				spaceFlag = false;
				buf = buf + c;
				if (!isdigit(c))
				{
					digitFlag = false;
				}
		}
	}
	if (buf != "")
	{
		if (digitFlag) // If it is number
			{
				resultString += functionDigit(stoi(buf));
			}
		else // it is string
			{
				resultString += functionString(buf);
			}
	}
	return resultString;
}

