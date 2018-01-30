#include "Fraction.h"
#include <string>
#include <regex>
#include <iostream>
using namespace std;

int GreatestCommonDivisor(int a, int b)
{
    a = abs(a);
    b = abs(b);

    while (1)
    {
        if (!a)
            return b;
        else if (!b)
            return a;

        if (a > b)
            a %= b;
        else
            b %= a;
    }
}
int LowestCommonMultiple(const int& a, const int& b)
{
    return abs(a * b / GreatestCommonDivisor(a, b));
}

Fraction::Fraction(const int& nNumerator, const int& nDenominator) : numerator(nNumerator), denominator(nDenominator)
{
    if (!denominator) throw INIT_INT_ERROR;

    if (denominator < 0)
    {
        numerator = -numerator;
        denominator = -denominator;
    }

    this->Reduction();
}
Fraction::Fraction(string input)
{
    regex reg("-?[0-9]+(/-?[0-9]+)?");

    if (!regex_match(input, reg)) throw INIT_STR_ERROR;

    int cut = input.find('/');

    if (cut != string::npos)
        *this = Fraction(stoi(input.substr(0, cut)), stoi(input.substr(cut + 1, input.size() - cut - 1))); // だダ
    else
        *this = Fraction(stoi(input)); // 俱计
}
void Fraction::Reduction()
{
    int gcd = GreatestCommonDivisor(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

// I/O
istream& operator >> (istream& in, Fraction& f)
{
    string input;
    in >> input;
    f = Fraction(input);
    return in;
}
ostream& operator << (ostream& out, const Fraction& f)
{
    if (f.denominator == 1) return out << f.numerator;
    else return out << f.numerator << " / " << f.denominator;
}

// Arithmetic operators
// operator +=
Fraction& operator+=(Fraction& lhs, const Fraction& rhs)
{
    // 硄だ
    int lcm = LowestCommonMultiple(lhs.denominator, rhs.denominator); // 程そ计
    int lhsMult = lcm / lhs.denominator; // オ娩硄だ┮惠计
    int rhsMult = lcm / rhs.denominator; // 娩硄だ┮惠计
    // 
    lhs.numerator = lhs.numerator * lhsMult + rhs.numerator * rhsMult;
    lhs.denominator = lcm;
    lhs.Reduction();
    return lhs;
}

// operator +
Fraction operator+(const Fraction& lhs, const Fraction& rhs)
{
    return Fraction(lhs) += rhs;
}
// operator -=
Fraction& operator-=(Fraction& lhs, const Fraction& rhs)
{
    return lhs += -rhs;
}
// operator -
Fraction operator-(const Fraction& lhs, const Fraction& rhs)
{
    return Fraction(lhs) += -rhs;
}
// operator *=
Fraction& operator*=(Fraction& lhs, const Fraction& rhs)
{
    lhs.numerator *= rhs.numerator;
    lhs.denominator *= rhs.denominator;
    lhs.Reduction();
    return lhs;
}
// operator *
Fraction operator*(const Fraction& lhs, const Fraction& rhs)
{
    return Fraction(lhs) *= rhs;
}
// operator /=
Fraction& operator/=(Fraction& lhs, const Fraction& rhs)
{
    return lhs *= !rhs;
}
// operator /
Fraction operator/(const Fraction& lhs, const Fraction& rhs)
{
    return Fraction(lhs) *= !rhs;
}

// self operator
Fraction Fraction::operator!() const // 计
{
    if (!denominator) throw INVERSE_ERROR;

    return Fraction(denominator, numerator);
}
Fraction Fraction::operator-() const
{
    return Fraction(-numerator, denominator);
}
Fraction& Fraction::operator++()
{
    return *this += Fraction(1);
}
Fraction Fraction::operator++(int)
{
    Fraction result(*this);
    ++(*this);
    return result;
}
Fraction& Fraction::operator--()
{
    return *this += Fraction(-1);
}
Fraction Fraction::operator--(int)
{
    Fraction result(*this);
    --(*this);
    return result;
}

// Comparison operators
bool operator==(const Fraction& lhs, const Fraction& rhs)
{
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}
bool operator!=(const Fraction& lhs, const Fraction& rhs)
{
    return !(lhs == rhs);
}
bool operator<(const Fraction& lhs, const Fraction& rhs)
{
    // 硄だ
    int lcm = LowestCommonMultiple(lhs.denominator, rhs.denominator); // 程そ计
    int lhsMult = lcm / lhs.denominator; // オ娩硄だ┮惠计
    int rhsMult = lcm / rhs.denominator; // 娩硄だ┮惠计
    return lhs.numerator * lhsMult < rhs.numerator * rhsMult;
}
bool operator>(const Fraction& lhs, const Fraction& rhs)
{
    return rhs < lhs;
}
bool operator<=(const Fraction& lhs, const Fraction& rhs)
{
    return !(lhs > rhs);
}
bool operator>=(const Fraction& lhs, const Fraction& rhs)
{
    return !(lhs < rhs);
}

// conversion
int Fraction::ToInt() const
{
    return numerator / denominator;
}
double Fraction::ToDouble() const
{
    return (double)numerator / (double)denominator;
}
string Fraction::ToString() const
{
    if (denominator == 1) return to_string(numerator);
    else return to_string(numerator) + " / " + to_string(denominator);
}
Fraction::operator int() const
{
    return this->ToInt();
}
Fraction::operator double() const
{
    return this->ToDouble();
}
Fraction::operator string() const
{
    return this->ToString();
}