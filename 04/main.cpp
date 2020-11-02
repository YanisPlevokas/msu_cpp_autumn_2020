#include <iostream>
#include "bigint.hpp"
using namespace std;


void DefaultWork()
{
	BigInt a = 1;
	BigInt b("123456789012345678901234567890");
	BigInt c = a * b + 2;
	BigInt d;
	d = move(c);
	a = d + b;
	//cout << a << endl;
	if (a != BigInt("0246913578024691357802469135782"))
	{
		throw string("Wrong add and mult oper!\n");
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
	try {
        DefaultWork();
    }
    catch (const string& exception) {
        cout << "DefaultWork problem: " << exception << endl;
    }
    catch (...) {
        cout << "DefaultWork problem\n";
    }
    try {
        EqualTest();
    }
    catch (const string& exception)
    {
    	{
            cout << "EqualTest problem: " << exception << endl;
    	}
    }
    catch (...) {
        cout << "EqualTest problem\n" << endl;
    }
    try {
        UnarMinus();
    }
    catch (const string& exception) {
            cout << "UnarMinus problem: " << exception << endl;
    }
    catch (...) {
    	cout << "UnarMinus problem\n";
    }
    cout << "Everything is ok\n";
    return 0;

}