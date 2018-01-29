#pragma once
#include <string>
using namespace std;

class Fraction
{
    public:
        Fraction(const int& = 0, const int& = 1);
        Fraction(string);

        // Exception handling
        enum ERROR_CODE { INIT_INT_ERROR, INIT_STR_ERROR, INVERSE_ERROR };

        /* Properties */
        int numerator; // 分子 // 負號只放於分子
        int denominator; // 分母 // 必為正數

        /* Methods */
        void Reduction();

        /* Operator overloading */
        // I/O
        friend istream& operator >> (istream&, Fraction&);
        friend ostream& operator <<	(ostream&, const Fraction&);

        // Arithmetic operators
        friend Fraction& operator+=(Fraction&		, const Fraction&); // Fraction += Fraction
        friend Fraction	 operator+ (const Fraction&	, const Fraction&); // Fraction +  Fraction
        friend Fraction& operator-=(Fraction&		, const Fraction&);
        friend Fraction  operator- (const Fraction&	, const Fraction&);
        friend Fraction& operator*=(Fraction&		, const Fraction&);
        friend Fraction  operator* (const Fraction&	, const Fraction&);
        friend Fraction& operator/=(Fraction&		, const Fraction&);
        friend Fraction  operator/ (const Fraction&	, const Fraction&);

        // Self arithmetic operators
        Fraction  operator- () const;
        Fraction  operator! () const; // 倒數
        Fraction& operator++();
        Fraction  operator++(int);
        Fraction& operator--();
        Fraction  operator--(int);

        // Comparison operators
        friend bool operator==(const Fraction&, const Fraction&); // Fraction == Fraction
        friend bool operator!=(const Fraction&, const Fraction&);
        friend bool operator< (const Fraction&, const Fraction&);
        friend bool operator<=(const Fraction&, const Fraction&);
        friend bool operator> (const Fraction&, const Fraction&);
        friend bool operator>=(const Fraction&, const Fraction&);

        // Cast
        int ToInt() const;
        double ToDouble() const;
        string ToString() const;
        explicit operator int() const;
        explicit operator double() const;
        explicit operator string() const;
};