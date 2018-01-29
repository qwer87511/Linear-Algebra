#pragma once

class Matrix
{
    public:
        static const int SIZE = 3;
        static const int COLUMN = SIZE;
        static const int ROW = SIZE + 1;
        Matrix();
        Matrix operator+(const Matrix& right);
        Matrix operator*(const Matrix& right);
        void GetMatrix();
        void Show();
        void GaussianElimination();
        void ReverseGaussianElimination();
        void SolutionByInto();
    private:
        int _matrix[COLUMN][ROW];
};
