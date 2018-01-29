#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

Matrix::Matrix(const int& column, const int& row) : column(column), row(row)
{
    this->Malloc(column, row);
    this->SetDiagonalMatrix(0);
}
Matrix::Matrix(const Matrix& rhs) : column(rhs.column), row(rhs.row)
{
    this->Malloc(column, row);
    this->Copy(rhs);
}
Matrix::~Matrix()
{
    this->Clear();
}
void Matrix::Malloc(int column, int row)
{
    this->data = new Fraction*[column];

    for (int i = 0; i < column; ++i)
    {
        this->data[i] = new Fraction[row];
    }
}
void Matrix::Copy(const Matrix& rhs)
{
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            this->data[i][j] = rhs.data[i][j];
        }
    }
}
void Matrix::Reset(int column, int row)
{
    this->Clear();
    this->column = column;
    this->row = row;
    this->Malloc(column, row);
    this->SetDiagonalMatrix(0);
}
void Matrix::SetDiagonalMatrix(const int& num)
{
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            if (i == j) this->data[i][j] = num;
            else this->data[i][j] = 0;
        }
    }
}
void Matrix::Clear()
{
    for (int i = 0; i < column; ++i)
    {
        delete[] data[i];
    }

    delete[] data;
}
Matrix& Matrix::operator=(const Matrix& rhs)
{
    if (this->column != rhs.column || this->row != rhs.row)
        this->Reset(column, row);

    this->Copy(rhs);
    return *this;
}
istream& operator >> (istream& in, Matrix& m)
{
    for (int i = 0; i < m.column; ++i)
    {
        for (int j = 0; j < m.row; ++j)
        {
            cin >> m.data[i][j];
        }
    }

    return in;
}
ostream& operator << (ostream& out, const Matrix& m)
{
    for (int i = 0; i < m.column; ++i)
    {
        cout << '|';

        for (int j = 0; j < m.row; ++j)
        {
            cout << setw(3) << m.data[i][j];
        }

        cout << setw(3) << '|' << endl;
    }

    return out;
}
Matrix Matrix::operator-() const
{
    return Matrix(*this) *= -1;
}
Matrix& operator+=(Matrix& lhs, const Matrix& rhs)
{
    if (lhs.column != rhs.column || lhs.row != rhs.row) throw Matrix::DIFFERENT_SIZE;

    for (int i = 0; i < lhs.column; ++i)
    {
        for (int j = 0; j < lhs.row; ++j)
        {
            lhs.data[i][j] = lhs.data[i][j] + rhs.data[i][j];
        }
    }

    return lhs;
}
Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    return Matrix(lhs) += rhs;
}
Matrix& operator-=(Matrix& lhs, const Matrix& rhs)
{
    return lhs += -rhs;
}
Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
    return Matrix(lhs) += -rhs;
}
Matrix& operator*=(Matrix& lhs, const Matrix& rhs)
{
    if (lhs.row != rhs.column) throw Matrix::MULTIPLE_ERRPOR;

    Matrix lhsTemp(lhs);
    lhs.Reset(lhs.column, rhs.row);
    cout << lhs << endl << rhs << endl;
    /*for (int i = 0; i < lhsTemp.column; ++i)
    {
        for (int j = 0; j < rhs.row; ++j)
        {
            for (int k = 0; k < rhs.column; ++k)
            {
                cout << "data[" << i << "][" << j << "] += data[" << i << "][" << k << "] * data[" << k << "][" << j << "]" << endl;
                cout << lhs.data[i][j] << " += " << lhsTemp.data[i][k] << " * " << rhs.data[k][j] << endl;
                lhs.data[i][j] += lhsTemp.data[i][k] * rhs.data[k][j];
            }
        }
    }*/
    return lhs;
}
Matrix& operator*=(Matrix& m, const int& mul)
{
    for (int i = 0; i < m.column; ++i)
    {
        for (int j = 0; j < m.row; ++j)
        {
            m.data[i][j] *= mul;
        }
    }

    return m;
}
Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
    return Matrix(lhs) *= rhs;
}
Matrix operator*(const Matrix& m, const int& mul)
{
    return Matrix(m) *= mul;
}
Matrix operator*(const int& mul, const Matrix& m)
{
    return Matrix(m) *= mul;
}
Matrix Matrix::Inverse()
{
    Matrix result(this->column, this->row);

    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            result.data[i][j] = 1 / this->data[i][j];
        }
    }

    return result;
}