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
        throw string("Wrong equal test\n"); // Они должны быть разные, так как m1 заполнено нулями
    }
    m1[1][2] = 5;
    Matrix m2 = m1 + m; // Матрица из нулей, , только на [1][2] стоит 20
    Matrix m3(rows, cols);
    m3[1][2] = 20; //Вручную выставляем 20 в позицию [1][2], чтобы в дальнейшем проверить, действительно ли в m2 произошло сложение
    if (m3 != m2) {
        throw string("Wrong add operation\n");
    }
}
void OutOfBounds()
{
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);
}
void SumDiffMatrices()
{
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);
    Matrix m1(rows + 1, cols);
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
    catch (const string& exception) {
        cout << "DefaultWork problem: " << exception << endl;
    }
    catch (...) {
        cout << "DefaultWork problem\n";
    }
    try {
        OutOfBounds();
    }
    catch (const out_of_range& exception) //Поймали это первым, так что у нас идет правильная обработка
    {
    }
    catch (...) {
        cout << "OutOfBounds problem\n" << endl;
    }
    try {
        SumDiffMatrices();
    }
    catch (const string& exception) //Проверка на правильную обработку
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
    catch (const string& exception) {
        if (exception != "Non-positive matrix declaration\n") {
            cout << "InitNegativeSizeMatrix problem\n";
        }
    }
    catch (...) {
    	cout << "InitNegativeSizeMatrix problem\n";
    }
    cout << "Everything is ok\n";
    return 0;
}