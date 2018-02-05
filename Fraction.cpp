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
Fraction& Fraction::operator+=(const Fraction& rhs)
{
    // 硄だ
    int lcm = LowestCommonMultiple(this->denominator, rhs.denominator); // 程そ计
    int lhsMult = lcm / this->denominator; // オ娩硄だ┮惠计
    int rhsMult = lcm / rhs.denominator; // 娩硄だ┮惠计
    // 
	this->numerator = this->numerator * lhsMult + rhs.numerator * rhsMult;
	this->denominator = lcm;
	this->Reduction();
    return *this;
}
// operator +
Fraction operator+(const Fraction& lhs, const Fraction& rhs)
{
	Fraction lhsTemp(lhs);
	return lhsTemp += rhs;
}
// operator -=
Fraction& Fraction::operator-=(const Fraction& rhs)
{
    return *this += -rhs;
}
// operator -
Fraction operator-(const Fraction& lhs, const Fraction& rhs)
{
	Fraction lhsTemp(lhs);
	return lhsTemp += -rhs;
}
// operator *=
Fraction& Fraction::operator*=(const Fraction& rhs)
{
	this->numerator *= rhs.numerator;
	this->denominator *= rhs.denominator;
	this->Reduction();
    return *this;
}
// operator *
Fraction operator*(const Fraction& lhs, const Fraction& rhs)
{
    Fraction lhsTemp(lhs);
	return lhsTemp *= rhs;
}
// operator /=
Fraction& Fraction::operator/=(const Fraction& rhs)
{
    return *this *= rhs.Inverse();
}
// operator /
Fraction operator/(const Fraction& lhs, const Fraction& rhs)
{
	Fraction lhsTemp(lhs);
	return lhsTemp *= rhs.Inverse();
}

// self operator
Fraction Fraction::Inverse() const // 计
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
    return *this += 1;
}
Fraction Fraction::operator++(int)
{
    Fraction result(*this);
    ++(*this);
    return result;
}
Fraction& Fraction::operator--()
{
    return *this -= 1;
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
Fraction::operator bool() const
{
    return bool(numerator);
}
Fraction::operator int() const
{
    return numerator / denominator;
}
Fraction::operator double() const
{
    return (double)numerator / (double)denominator;
}
Fraction::operator string() const
{
    if (denominator == 1) return to_string(numerator);
    else return to_string(numerator) + " / " + to_string(denominator);
}