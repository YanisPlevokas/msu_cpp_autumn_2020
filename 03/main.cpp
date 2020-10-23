#include <iostream>
#include "matrix_header.hpp"
using namespace std;

void DefaultWork()
{
	const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);
    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);

    m[1][2] = 5; // строка 1, колонка 2
    cout << m[4][1];
    m *= 3; // умножение на число

    Matrix m1(rows, cols);

    if (m1 == m) {
    }
    Matrix m2 = m1 + m;
    cout << m2 << endl;
}
void OutOfBounds()
{
	const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

	cout << m[6][2] << endl;
}




int main()
{
	try
	{
		DefaultWork();
	}
	catch(...)
	{
		cout << "DefaultWork problem\n";
	}
	try
	{
		OutOfBounds();
	}
	catch(out_of_range) //Поймали это первым, так что у нас идет правильная обработка
	{

	}
	catch(...)
	{
		cout << "OutOfBounds problem\n" << endl;
	}
	

    
    return 0;
}