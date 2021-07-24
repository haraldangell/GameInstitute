#pragma once
class Fraction
{
	friend std::istream& operator>>(std::istream& is, Fraction& v);
	friend std::ostream& operator<<(std::ostream& os, const Fraction& v);
public:
	Fraction();
	Fraction(float num, float den);
	~Fraction();

	void Print() const;

	//(+, -, *, /) 
	Fraction operator +(const Fraction& rhs) const;
	Fraction operator -(const Fraction& rhs) const;
	Fraction operator *(const Fraction& rhs) const;
	Fraction operator /(const Fraction& rhs) const;
	Fraction operator =(const Fraction& rhs) const;


	
	//(==, !=, <, >, <=, >=)
	bool operator ==(const Fraction& rhs) const;
	bool operator !=(const Fraction& rhs) const;
	bool operator <(const Fraction& rhs) const;
	bool operator >(const Fraction& rhs) const;
	bool operator <=(const Fraction& rhs) const;
	bool operator >=(const Fraction& rhs) const;

	explicit operator float() const;

	float mNumerator;
	float mDenominator;
};

std::istream& operator>>(std::istream& is, Fraction& v);
std::ostream& operator<<(std::ostream& os, const Fraction& v);
