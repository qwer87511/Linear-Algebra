#pragma once
#include "Fraction.h"

class Matrix
{
    public:
        Matrix(const int& = 1, const int& = 1);
        ~Matrix();

        enum ERROR_CODE { MULTIPLE_ERRPOR, DIFFERENT_SIZE };

        Matrix(const Matrix&);
        void Malloc(int, int);
        void Reset(int, int);
        void Clear();
        void Copy(const Matrix&);
        void SetDiagonalMatrix(const int&);

        /* operator overloading */

        Matrix& operator=(const Matrix&);

        // I/O

        friend istream& operator >> (istream&, Matrix&);
        friend ostream& operator << (ostream&, const Matrix&);

        Matrix Inverse();

        Matrix operator-() const;

        friend Matrix& operator+=(Matrix&		, const Matrix&);
        friend Matrix  operator+ (const Matrix&	, const Matrix&);
        friend Matrix& operator-=(Matrix&		, const Matrix&);
        friend Matrix  operator- (const Matrix&	, const Matrix&);
        friend Matrix& operator*=(Matrix&		, const Matrix&);
        friend Matrix& operator*=(Matrix&		, const int&);
        friend Matrix  operator* (const Matrix&	, const Matrix&);
        friend Matrix  operator* (const Matrix&	, const int&);
        friend Matrix  operator* (const int&	, const Matrix&);

        /* properties */
        int column;
        int row;
        Fraction** data;
};