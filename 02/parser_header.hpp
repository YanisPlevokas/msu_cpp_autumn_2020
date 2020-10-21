#pragma once
#include <iostream>
#include <string>
#include <functional>
using namespace std;

using callback = function<string()>;
using digit = function<string (int)>;
using stringFunc = function<string (const string&)>;

class TokenParser
{
private:
	bool callbackFlag;
	bool digitFlag;
	bool stringFlag;
	callback functionCallback;
	digit functionDigit;
	stringFunc functionString;
public:
	TokenParser();
	void SetStartCallback(const callback &functionCallbackNew);
	void SetDigitTokenCallback(const digit &functionCallbackNew);
	void SetStringTokenCallback(const stringFunc &functionSetStringNew);
	string StartParsing(const string& textName);
};
