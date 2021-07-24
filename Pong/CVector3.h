#pragma once

class CVector3
{
public:
	CVector3();
	CVector3(float coords[3]);
	CVector3(float x, float y, float z);
	~CVector3();

	CVector3 operator+(const CVector3& rhs);
	CVector3 operator-(const CVector3& rhs);
	CVector3 operator/(const CVector3& rhs);
	CVector3 operator*(const float scalar);
	void operator+=(const CVector3& rhs);
	void operator-=(const CVector3& rhs);
	void operator*=(const float scalar);

	bool operator==(const CVector3& rhs);
	bool operator!=(const CVector3& rhs);

	float Length();
	void Normalize();
	float Dot(const CVector3& rhs);
	CVector3 Cross(CVector3& rhs);
	float* ToFloatArray();

	void Print();


	float mX;
	float mY;
	float mZ;
};