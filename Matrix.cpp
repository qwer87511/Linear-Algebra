#include<iostream>
using namespace std;

template<class T>
class Matrix
{
    public:
        Matrix(const int&, const int&);

        /* operator overloading */

        // I / O

        friend istream& operator >> (istream&, Matrix&);
        friend ostream& operator << (ostream&, const Matrix&);

        /* properties */
        int column;
        int row;
        T** data;
};

// constructor
template<class T>
Matrix<T>::Matrix(const int& column, const int& row) : column(column), row(row)
{
    this->data = new T*[column];

    for (int i = 0; i < column; ++i)
    {
        this->data[i] = new T[row];
    }
}

// I/O
template<class T>
istream& operator >> (istream& in, Matrix<T>& m)
{
    return in >> m.data[0][0];
}

template<class T>
ostream& operator<<(ostream& out, const Matrix<T>& m)
{
    return out << m.data[0][0];
}