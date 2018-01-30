#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

template<class T>
class Matrix
{
    public:

        // constructor
        Matrix(const int& = 1, const int& = 1);
        Matrix(const Matrix&);
        // destructor
        ~Matrix();

        //-------------------------------------------------------------------------

        // to construct
        Matrix& Copy(const Matrix&);
        Matrix& Swap(Matrix&); // 減少使用new

        // to destruct
        void Clear();
        //void Reset(const int&, const int&);

        //-------------------------------------------------------------------------

        // operator overloading

        // index operator
        T* operator[](int);

        // assign
        Matrix& operator=(const Matrix&);

        // Input
        template<class T> friend istream& operator >> (istream&, Matrix&);
        template<class T> friend ostream& operator << (ostream&, const Matrix&);

        // operation
        template<class T> friend Matrix& operator+=(Matrix&			, const Matrix&);
        template<class T> friend Matrix	 operator+ (const Matrix&	, const Matrix&);
        template<class T> friend Matrix& operator-=(Matrix&			, const Matrix&);
        template<class T> friend Matrix	 operator- (const Matrix&	, const Matrix&);
        template<class T> friend Matrix& operator*=(Matrix&			, const Matrix&);
        template<class T> friend Matrix	 operator* (const Matrix&	, const Matrix&);
        /* properties */
        int column;
        int row;
        T** data;
};

// constructor
template<class T>
Matrix<T>::Matrix(const int& column, const int& row) :
    column(column),
    row(row),
    data(new T*[column])
{
    for (int i = 0; i < column; ++i)
    {
        this->data[i] = new T[row] { 0 }; // T 需要支援初始參數.
    }
}

// copy constructor
template<class T>
Matrix<T>::Matrix(const Matrix<T>& m) :
    column(m.column),
    row(m.row),
    data(new T*[column])
{
    for (int i = 0; i < column; ++i)
    {
        this->data[i] = new T[row] { 0 }; // T 需要支援初始參數.
    }

    this->Copy(m);
}

// destructor
template<class T>
Matrix<T>::~Matrix()
{
    for (int i = 0; i < column; ++i)
    {
        delete[] this->data[i];
    }

    delete[] this->data;
}

template<class T>
Matrix<T>& Matrix<T>::Copy(const Matrix<T>& m)
{
    for (int i = 0; i < column; ++i)
    {
        memcpy(this->data[i], m.data[i], this->row * sizeof(T));
    }

    return *this;
}

template<class T>
void Matrix<T>::Clear()
{
    this->Swap(Matrix<T>());
}

//template<class T>
//void Matrix<T>::Reset(const int& column, const int& row)
//{
//    this->Clear();
//    this->column = column;
//    this->row = row;
//    this->Malloc(column, row);
//}

template<class T>
Matrix<T>& Matrix<T>::Swap(Matrix<T>& rhs)
{
    swap(this->column, rhs.column);
    swap(this->row, rhs.row);
    swap(this->data, rhs.data);
    return *this;
}

// operator overloading
template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
    if (this->column != m.column || this->row != m.row)
        //this->Reset(m.column, m.row); // version 1
        return this->Swap(Matrix<T>(m)); // version 2
    else
        return this->Copy(m);
}

// input
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

// output
template<class T>
ostream& operator << (ostream& out, const Matrix<T>& m)
{
    for (int i = 0; i < m.column; ++i)
    {
        out << setw(3) << "|";

        for (int j = 0; j < m.row; ++j)
        {
            out <<setw(3)<< m.data[i][j];
        }

        out << setw(3) << "|" << endl;
    }

    return out;
}

// index operation
template<class T>
T* Matrix<T>::operator[](int index)
{
    return this->data[index];
}

// operation

// Matrix += Matrix
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

// Matrix + Matrix
template<class T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return Matrix<T>(lhs) += rhs;
}

// Matrix -= Matrix
template<class T>
Matrix<T>& operator-=(Matrix<T>& lhs, const Matrix<T>& rhs)
{
    for (int i = 0; i < rhs.column; ++i)
    {
        for (int j = 0; j < rhs.row; ++j)
        {
            lhs.data[i][j] -= rhs.data[i][j];
        }
    }

    return lhs;
}

// Matrix - Matrix
template<class T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return Matrix<T>(lhs) -= rhs;
}

// Matrix *= Matrix
template<class T>
Matrix<T>& operator*=(Matrix<T>& lhs, const Matrix<T>& rhs)
{
    if (lhs.row != rhs.column) throw "MULTIPLE ERROR";

    // if rhs matrix is not square lhs matrix would change the size
    Matrix<T> result(lhs.column, rhs.row);

    for (int i = 0; i < lhs.column; ++i)
    {
        for (int j = 0; j < rhs.row; ++j)
        {
            for (int k = 0; k < lhs.row; ++k)
            {
                result.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
            }
        }
    }

    lhs.Swap(result);
    return lhs;
}

// Matrix * Matrix
template<class T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return Matrix<T>(lhs) *= rhs;
}