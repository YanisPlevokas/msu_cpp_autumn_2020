#include <iostream>
#include <string>
using namespace std;
#ifndef H_PARSER
#define H_PARSER

class TokenParser
{
private:
	FILE* filePointer;
	char c;
	bool flagFile;
	bool callbackFlag;
	bool digitFlag;
	bool stringFlag;
	function<void()> function_callback;
	function<void(int)> function_digit;
	function<void(string)> function_string;
	void gc();
public:
	void SetStartCallback(void (*function_callback_new) () );
	void SetDigitTokenCallback(void (*function_set_digit_new) (int));
	void SetStringTokenCallback(void (*function_set_string_new) (string));
	bool StartParsing(const char* program);
	~TokenParser();
};

#endif