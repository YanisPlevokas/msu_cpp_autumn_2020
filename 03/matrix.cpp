#include <iostream>
using namespace std;
#include "matrix_header.hpp"

Matrix::Matrix()
{
    matr = nullptr;
    rows = 0;
    columns = 0;
}
Matrix::Matrix(int rowsNew, int columnsNew)
{
    if ((rowsNew <= 0) || (columnsNew <= 0)) {
        throw "Non-positive matrix declaration\n";
        matr = nullptr;
    }
    else {
    	rows = rowsNew;
    	columns = columnsNew;
        matr = new int*[rowsNew];
        for (int i = 0; i < rowsNew; i++) {
            matr[i] = new int[columnsNew];
        }
    }
}
Matrix &Matrix::operator*=(int number) 
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) 
        {
            matr[i][j] *= number;
        }
    }
    return *this;
}
Matrix Matrix::operator+(const Matrix& matrix)
{
    if (matr == nullptr || matrix.matr == nullptr) {
        throw string("At least one of the matrices is not declared\n");
    }
    else {
        if (rows != matrix.rows || columns != matrix.columns) {
            throw string("Different matrix sizes\n");
        }
        else {
        	Matrix newMatrix = Matrix(rows, columns);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    newMatrix[i][j] = matrix[i][j] + matr[i][j];
                }
            }
            return newMatrix;
        }
    }
}

bool Matrix::operator==(const Matrix& matrix) const
{
    if (matrix.rows != rows || matrix.columns != columns) {
        return false;
    }
    else {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (matrix[i][j] != matr[i][j])
                    return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& matrix) const
{
    return !(*this == matrix);
}

int Matrix::getRows()
{
    return rows;
}
int Matrix::getColumns()
{
    return columns;
}

Matrix::~Matrix()
{
    if (rows > 0 && columns > 0) {
        for (int i = 0; i < rows; i++)
            delete[] matr[i];
        delete[] matr;
    }
}

Matrix::Rows Matrix::operator[](int row)
{
    if (row >= rows) {
        throw std::out_of_range("");
    }
    return Rows(matr[row], columns);
}

const Matrix::Rows Matrix::operator[](int row) const
{
    if (row >= rows) {
        throw std::out_of_range("");
    }
    return Rows(matr[row], columns);
}

Matrix::Rows::Rows(int* row, int len)
{
    rowPtr = row;
    length = len;
}

ostream& operator<<(ostream& os, const Matrix& matrix)
{
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++) {
            os << matrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

Matrix::Rows::~Rows() = default;

int& Matrix::Rows::operator[](int col)
{
    if (col >= length) {
        throw std::out_of_range("");
    }
    int &res = rowPtr[col];
    return res;
}

const int& Matrix::Rows::operator[](int col) const
{
    if (col >= length) {
        throw std::out_of_range("");
    }
    int& res = rowPtr[col];
    return res;
}
