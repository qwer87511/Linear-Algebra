#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

template<class T>
class Matrix
{
    public:
        Matrix(const int&, const int&);
        Matrix(const Matrix&);
        // for constructor
        void Malloc(const int&, const int&);
        void Copy(const Matrix&);
        void Clear();
        ~Matrix();
        /* operator overloading */

        // assign
        Matrix& operator=(const Matrix&);
        // Input
        template<class T> friend istream& operator >> (istream&, Matrix&);
        template<class T> friend ostream& operator << (ostream&, const Matrix&);
        // opertion
        template<class T> friend Matrix& operator+=(Matrix&, const Matrix&);
        template<class T> friend Matrix operator+(const Matrix&, const Matrix&);
        /* properties */
        int column;
        int row;
        T** data;
};

// for init
template<class T>
void Matrix<T>::Malloc(const int& column, const int& row)
{
    this->data = new T*[column];

    for (int i = 0; i < column; ++i)
    {
        this->data[i] = new T[row];
    }
}

template<class T>
void Matrix<T>::Copy(const Matrix<T>& m)
{
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            this->data[i][j] = m.data[i][j];
        }
    }
}

template<class T>
void Matrix<T>::Clear()
{
    for (int i = 0; i < column; ++i)
    {
        delete[] data[i];
    }

    delete[] data;
}

// constructor
template<class T>
Matrix<T>::Matrix(const int& column, const int& row) : column(column), row(row)
{
    this->Malloc(column, row);
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& m) : column(m.column), row(m.row)
{
    this->Malloc(column, row);
    this->Copy(m);
}

// destructor
template<class T>
Matrix<T>::~Matrix()
{
    this->Clear();
}

// operator overloading
template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
    if (this->column != m.column || this->row != m.row)
    {
        this->Clear();
        this->column = m.column;
        this->row = m.row;
        this->Malloc(m.column, m.row);
    }

    this->Copy(m);
    return *this;
}

// I/O
template<class T>
istream& operator >> (istream& in, Matrix<T>& m)
{
    for (int i = 0; i < m.column; ++i)
    {
        for (int j = 0; j < m.row; ++j)
        {
            in >> m.data[i][j];
        }
    }

    return in;
}

template<class T>
ostream& operator << (ostream& out, const Matrix<T>& m)
{
    for (int i = 0; i < m.column; ++i)
    {
        out << "|";

        for (int j = 0; j < m.row; ++j)
        {
            out <<setw(3)<< m.data[i][j];
        }

        out << setw(3) << "|" << endl;
    }

    return out;
}

// operation
template<class T>
Matrix<T>& operator+=(Matrix<T>& lhs, const Matrix<T>& rhs)
{
    for (int i = 0; i < rhs.column; ++i)
    {
        for (int j = 0; j < rhs.row; ++j)
        {
            lhs.data[i][j] += rhs.data[i][j];
        }
    }

    return lhs;
}

template<class T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return Matrix<T>(lhs) += rhs;
}