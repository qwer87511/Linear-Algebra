#include "Matrix.h"
#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::setw;
uint16_t l;
Matrix::Matrix()
{
}
Matrix Matrix::operator+(const Matrix& right)
{
    Matrix newMatrix;

    for (int i = 0; i < COLUMN; ++i)
    {
        for (int j = 0; j < ROW; ++j)
        {
            newMatrix._matrix[i][j] = this->_matrix[i][j] + right._matrix[i][j];
        }
    }

    return newMatrix;
}
Matrix Matrix::operator*(const Matrix& right)
{
    Matrix resultMatrix;

    for (int i = 0; i < COLUMN; ++i)
    {
        for (int j = 0; j < ROW; ++j)
        {
            //resultMatrix._matrix[i][j] = this->_matrix[][] + right._matrix[][];
        }
    }
}
void Matrix::GetMatrix()
{
    for (int i = 0; i < COLUMN; ++i)
    {
        for (int j = 0; j < ROW; ++j)
        {
            cin >> this->_matrix[i][j];
        }
    }
}
void Matrix::Show()
{
    for (int i = 0; i < COLUMN; ++i)
    {
        for (int j = 0; j < ROW; ++j)
        {
            cout << setw(3) << this->_matrix[i][j];
        }

        cout << endl;
    }
}
void Matrix::GaussianElimination()
{
    for (int i = 0; i < COLUMN; ++i)
    {
        int pivot = this->_matrix[i][i];

        for (int j = i + 1; j < COLUMN; ++j)
        {
            int multiple = -this->_matrix[j][i] / pivot;

            for (int k = i; k < ROW; ++k)
            {
                this->_matrix[j][k] += multiple * this->_matrix[i][k];
            }
        }
    }
}
void Matrix::SolutionByInto()
{
    int sol[COLUMN];
}
void Matrix::ReverseGaussianElimination()
{
    for (int i = COLUMN; i >= 0; --i)
    {
        int pivot = this->_matrix[i][i];

        for (int j = i - 1; j >= 0; --j)
        {
            int multiple = -this->_matrix[j][i] / pivot;

            for (int k = i; k >= 0; --k)
            {
                this->_matrix[j][k] += multiple * this->_matrix[i][k];
            }
        }
    }
}