#include <iostream>
#include <string>
#include "parser_header.hpp"
using namespace std;


void function_greeting()
{
    cout << "greetings\n";
}

void function_number(int number)
{

    cout << "hello_numb " << number << endl;
}
void function_string(string word)
{

    cout << "hello_string " << word << endl;
}
void function_number_2(int number)
{
    cout <<"hello_numb_2 * 2 " << number * 2 << endl;
}

void DefaultWorkTest()
{
    TokenParser parser;
    parser.SetStringTokenCallback(function_string);
    parser.SetDigitTokenCallback(function_number);
    parser.SetStartCallback(function_greeting);
    parser.StartParsing("file");
}

void EmptyFile()
{
    TokenParser parser;
    parser.SetStringTokenCallback(function_string);
    parser.SetDigitTokenCallback(function_number);
    parser.SetStartCallback(function_greeting);
    parser.StartParsing("empty_file");
}
void NonDeclaredFunction()
{
    TokenParser parser;
    parser.SetStringTokenCallback(function_string);
    parser.SetDigitTokenCallback(function_number);
    parser.StartParsing("file");
}
void ReinstallFunction()
{
    TokenParser parser;
    parser.SetStringTokenCallback(function_string);
    parser.SetDigitTokenCallback(function_number);
    parser.SetStartCallback(function_greeting);
    parser.StartParsing("file");
    parser.SetDigitTokenCallback(function_number_2);
    parser.StartParsing("file");
}



int main()
{
    try
    {
        DefaultWorkTest();
        ReinstallFunction();
        NonDeclaredFunction();
        EmptyFile();
    }
    catch (const char* exception)
    {
        std::cerr << "Error: " << exception << '\n';
    }
    catch (...)
    {
        std::cout << "unexpected problem occured\n";
    }
    std::cout << "Everything is fine!\n";

    return 0;
}