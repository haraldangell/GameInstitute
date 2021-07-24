#include <iostream>
#include "Fraction.h"



Fraction::Fraction()
{
	mNumerator = 0.0f;
	mDenominator = 1.0f;
}

Fraction::Fraction(float num, float den)
{
	mNumerator = num;
	mDenominator = den;
}


Fraction::~Fraction()
{

}

void Fraction::Print() const
{
	std::cout << "Numerator: " << mNumerator << std::endl << "Denominator: " << mDenominator << std::endl;
}

Fraction Fraction::operator+(const Fraction & rhs) const
{
	Fraction sum;
	sum.mNumerator = mNumerator + rhs.mNumerator;
	sum.mDenominator = mNumerator + rhs.mDenominator;
	return sum;
}

Fraction Fraction::operator-(const Fraction & rhs) const
{
	Fraction sum;
	sum.mNumerator = mNumerator - rhs.mNumerator;
	sum.mDenominator = mNumerator - rhs.mDenominator;
	return sum;
}

Fraction Fraction::operator*(const Fraction & rhs) const
{
	Fraction sum;
	sum.mNumerator = mNumerator * rhs.mNumerator;
	sum.mDenominator = mNumerator * rhs.mDenominator;
	return sum;
}
Fraction Fraction::operator/(const Fraction & rhs) const
{
	Fraction sum;
	if (rhs.mNumerator != 0 && rhs.mDenominator != 0)
	{
		sum.mNumerator = mNumerator / rhs.mNumerator; // = 0  NaN
		sum.mDenominator = mNumerator / rhs.mDenominator;
	}
	else
	{
		sum.mNumerator = 0.0f;
		sum.mDenominator = 1.0f;
	}

	return sum;
}

Fraction Fraction::operator=(const Fraction& rhs) const
{
	Fraction f;
	f.mNumerator = rhs.mNumerator;
	f.mDenominator = rhs.mDenominator;
	return f;
}


bool Fraction::operator==(const Fraction & rhs) const
{
	return mNumerator == rhs.mNumerator && mDenominator == rhs.mDenominator;
}

bool Fraction::operator!=(const Fraction & rhs) const // || = or and && = and
{
	return mNumerator != rhs.mNumerator || mDenominator != rhs.mDenominator;
}

bool Fraction::operator<(const Fraction & rhs) const
{
	return mNumerator < rhs.mNumerator && mDenominator < rhs.mDenominator;
}

bool Fraction::operator>(const Fraction & rhs) const
{
	return mNumerator > rhs.mNumerator && mDenominator > rhs.mDenominator;
}

bool Fraction::operator<=(const Fraction & rhs) const
{
	return mNumerator <= rhs.mNumerator && mDenominator <= rhs.mDenominator;
}

bool Fraction::operator>=(const Fraction & rhs) const
{
	return mNumerator >= rhs.mNumerator && mDenominator >= rhs.mDenominator;
}

Fraction::operator float() const
{
	float sum = 0.0f;
	if (mDenominator != 0.0f)
		sum = mNumerator / mDenominator;
	return sum;
}
std::istream& operator>>(std::istream& is, Fraction& v)
{
	std::cout << "Enter Numerator: ";
	std::cin >> v.mNumerator;
	std::cout << "Enter Denominator: ";
	std::cin >> v.mDenominator;


	return is;
}

std::ostream& operator<<(std::ostream& os, const Fraction& v)
{
	std::cout << "<" << v.mNumerator << ", " << v.mDenominator << "> \n";

	return os;
}