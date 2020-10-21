#include <iostream>
#include <string>
#include "parser_header.hpp"
using namespace std;

string functionGreeting()
{
    return "greetings ";
}

string functionNumber(int number)
{
    return to_string(number) + ' ';
}
string functionString(string word)
{
    return word + ' ';
}
string functionNumberSecond(int number)
{
    return to_string(number * 2) + ' ';
}

void DefaultWorkTest()
{
    TokenParser parser;
    parser.SetStringTokenCallback(functionString);
    parser.SetDigitTokenCallback(functionNumber);
    parser.SetStartCallback(functionGreeting);
    string testString = "rock \n granj \r uvula \t pasosh 16 10 2020 zakroyte mgu na carantin asd10 10asd";
    string expectedString = "greetings rock granj uvula pasosh 16 10 2020 zakroyte mgu na carantin asd10 10asd ";
    if (parser.StartParsing(testString) != expectedString) {
        throw "DefaultWorkTest problem";
    }
}

void EmptyString()
{
    TokenParser parser;
    parser.SetStringTokenCallback(functionString);
    parser.SetDigitTokenCallback(functionNumber);
    parser.SetStartCallback(functionGreeting);
    string testString = "";
    if (parser.StartParsing(testString) != "greetings ") {
        throw "Empty File problem";
    }
}
void NonDeclaredFunction()
{
    TokenParser parser;
    parser.SetStringTokenCallback(functionString);
    parser.SetDigitTokenCallback(functionNumber);
    string testString = "rock \n granj \r uvula \t pasosh 16 10 2020 zakroyte mgu na carantin asd10 10asd";
    if (parser.StartParsing(testString) != "You didn't declare functions. Try again.") {
        throw "NonDeclaredFunction problem";
    }
    parser.SetStartCallback(functionGreeting);
    string expectedString = "greetings rock granj uvula pasosh 16 10 2020 zakroyte mgu na carantin asd10 10asd ";
    if (parser.StartParsing(testString) != expectedString) {
        throw "DefaultWorkTest problem";
    }
}
void ReinstallFunction()
{
    TokenParser parser;
    parser.SetStringTokenCallback(functionString);
    parser.SetDigitTokenCallback(functionNumber);
    parser.SetStartCallback(functionGreeting);
    string testString = "rock \n granj \r uvula \t pasosh 16 10 2020 zakroyte mgu na carantin asd10 10asd";
    string expectedStringFirst = "greetings rock granj uvula pasosh 16 10 2020 zakroyte mgu na carantin asd10 10asd ";
    string expectedStringSecond = "greetings rock granj uvula pasosh 32 20 4040 zakroyte mgu na carantin asd10 10asd ";
    if (parser.StartParsing(testString) != expectedStringFirst) {
        throw "ReinstallFunction problem";
    }
    parser.SetDigitTokenCallback(functionNumberSecond);
    if (parser.StartParsing(testString) != expectedStringSecond) {
        throw "ReinstallFunction problem";
    }
}

int main()
{
    try {
        DefaultWorkTest();
        EmptyString();
        ReinstallFunction();
        NonDeclaredFunction();
    }
    catch (const char* exception) {
        std::cerr << "Error: " << exception << '\n';
    }
    catch (...) {
        std::cout << "unexpected problem occured\n";
    }
    std::cout << "Everything is fine!\n";

    return 0;
}