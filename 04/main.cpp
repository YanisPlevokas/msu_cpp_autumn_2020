#include <iostream>
#include "bigint.hpp"
using namespace std;
#include <string>
#include <sstream>   


void DefaultWork()
{
    BigInt a = 1;
    BigInt b("123456789012345678901234567890");
    BigInt c = a * b + 2;
    BigInt d;
    d = move(c);
    a = d + b;
    stringstream buffer;
    buffer << a;
    if (buffer.str() != "246913578024691357802469135782")
    {
    	throw string("Wrong add and mult oper!\n");
    }
    BigInt test1("999999999999999999999980000000000000000000001");
    BigInt test2("10000");
    buffer.str("");
    buffer << test2 * (test1 * test2);
    if (buffer.str() != "99999999999999999999998000000000000000000000100000000")
    {
    	throw string("Wrong add and mult oper!\n");	
    }
}

void BigNumberMultZero()
{
	BigInt a("9999999999999999999999800000000000000000000010000000099999999999999999999998000000000000000000000100000000");
	BigInt zero("0");
	stringstream buffer;
	buffer << a * zero;
	if (buffer.str() != "0")
	{
		throw string("Wrong mult!\n");
	}
}

void ZeroesTest()
{
	BigInt a("0000101010101010111101000001010101010101111010000000");
	stringstream buffer;
	buffer << a;
	if (buffer.str() != "101010101010111101000001010101010101111010000000")
	{
		throw string("Wrong ZeroProcessing\n");
	}
}

void EqualTest()
{
    BigInt a("-123535445678765435678987654");
    BigInt b("-1234567876543234567876543265432345");
    BigInt c("4323343233");
    BigInt d("43233432334323343233");
    string exception = "problem in Equal Test\n";
    if (a <= b)
    {
        throw string("First");
    }
    if (c >= d)
    {
        throw string("Second");
    }
    if (b >= c)
    {
        throw string("Third");
    }
}

void UnarMinus()
{
    BigInt a("123");
    BigInt b("-123");
    if (-a != b)
    {
        throw string("Wrong unar minus\n");
    }
}

int main()
{
    try
    {
        DefaultWork();
    }
    catch (const string& exception)
    {
        cout << "DefaultWork problem: " << exception << endl;
    }
    catch (...)
    {
        cout << "DefaultWork problem\n";
    }
    try
    {
        EqualTest();
    }
    catch (const string& exception)
    {
        {
            cout << "EqualTest problem: " << exception << endl;
        }
    }
    catch (...)
    {
        cout << "EqualTest problem\n" << endl;
    }
    try
    {
    	BigNumberMultZero();
    }
    catch (const string& exception)
    {
    	cout << "Mult problem: " << exception << endl;
    }
    catch (...)
    {
    	cout << "Mult problem\n";
    }
    try
    {
        UnarMinus();
    }
    catch (const string& exception)
    {
        cout << "UnarMinus problem: " << exception << endl;
    }
    catch (...)
    {
        cout << "UnarMinus problem\n";
    }
    try
    {
    	ZeroesTest();
    }
    catch (const string& exception)
    {
        cout << "ZeroesTest problem: " << exception << endl;
    }
    catch (...)
    {
        cout << "ZeroesTest problem\n";
    }

    cout << "Everything is ok\n";
    return 0;
}