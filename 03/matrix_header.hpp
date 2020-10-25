#pragma once
#include <iostream>
using namespace std;

class Matrix {

private:
    int** matr;

    int rows;

    int columns;

public:
    Matrix();

    Matrix(int rowsNew, int columnsNew);

    Matrix &operator*=(int number);

    Matrix operator+(const Matrix& matrix);

    friend ostream& operator<<(ostream& os, const Matrix& matrix);

    bool operator==(const Matrix& matrix) const;

    bool operator!=(const Matrix& Matrix) const;

    int getRows();

    int getColumns();

    ~Matrix();

    class Rows {

    public:
        Rows(int* row, int len);

        ~Rows();

        const int &operator[](int col) const;

        int &operator[](int col);

        int* rowPtr;

    private:
        int length;
    };
    Rows operator[](int row);
    const Rows operator[](int row) const;
};