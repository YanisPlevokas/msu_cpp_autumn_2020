#include <iostream>
#include "bigint.hpp"
using namespace std;
int main()
{
	BigInt a("222222222222222222222222222222222222222222222222222222222222222222222222222");
	BigInt x("5432");
	x = a;
	cout << x << endl;
	return 0;
}