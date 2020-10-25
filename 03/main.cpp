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
    assert(0 == m[4][1]);
    m *= 3; // умножение на число

    Matrix m1(rows, cols);

    if (m1 == m) {
    }
    Matrix m2 = m1 + m;
}
void OutOfBounds()
{
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    cout << m[6][2] << endl;
}
void SumDiffMatrices()
{
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);
    Matrix m1(rows + 1, cols);
    cout << m + m1 << endl;
}
void InitNegativeSizeMatrix()
{
    int rows = -5;
    int cols = 3;

    Matrix m(rows, cols);
}

int main()
{
    try {
        DefaultWork();
    }
    catch (...) {
        cout << "DefaultWork problem\n";
    }
    try {
        OutOfBounds();
    }
    catch (out_of_range) //Поймали это первым, так что у нас идет правильная обработка
    {
    }
    catch (...) {
        cout << "OutOfBounds problem\n" << endl;
    }
    try {
        SumDiffMatrices();
    }
    catch (string exception) //Проверка на правильную обработку
    {
        if (exception != "Different matrix sizes\n") {
            cout << "SumDiffMatrices problem\n" << endl;
        }
    }
    catch (...) {
        cout << "SumDiffMatrices problem\n" << endl;
    }
    try {
        InitNegativeSizeMatrix();
    }
    catch (string exception) {
        if (exception != "Non-positive matrix declaration\n") {
            cout << "InitNegativeSizeMatrix problem\n";
        }
    }
    cout << "Everything is ok\n";
    return 0;
}