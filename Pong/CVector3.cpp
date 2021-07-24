#include "pch.h"
#include "CVector3.h"


CVector3::CVector3()
{
	mX = 0.0f;
	mY = 0.0f;
	mZ = 0.0f;
}

CVector3::CVector3(float coords[3])
{
	mX = coords[0];
	mY = coords[1];
	mZ = coords[2];
}

CVector3::CVector3(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

CVector3::~CVector3()
{
}

CVector3 CVector3::operator+(const CVector3& rhs)
{
	CVector3 sum;
	sum.mX = mX + rhs.mX;
	sum.mY = mY + rhs.mY;
	sum.mZ = mZ + rhs.mZ;
	return sum;
}
CVector3 CVector3::operator-(const CVector3& rhs)
{
	CVector3 sum;
	sum.mX = mX - rhs.mX;
	sum.mY = mY - rhs.mY;
	sum.mZ = mZ - rhs.mZ;
	return sum;
}
CVector3 CVector3::operator/(const CVector3& rhs)
{
	CVector3 dif;
	dif.mX = mX / rhs.mX;
	dif.mY = mY / rhs.mY;
	dif.mZ = mZ / rhs.mZ;
	return dif;
}
CVector3 CVector3::operator*(const float scalar)
{
	CVector3 sum;
	sum.mX = mX * scalar;
	sum.mY = mY * scalar;
	sum.mZ = mZ * scalar;
	return sum;
}
void CVector3::operator+=(const CVector3& rhs)
{

	mX += rhs.mX;
	mY += rhs.mY;
	mZ += rhs.mZ;

}
void CVector3::operator-=(const CVector3& rhs)
{

	mX -= rhs.mX;
	mY -= rhs.mY;
	mZ -= rhs.mZ;

}
void CVector3::operator*=(const float scalar)
{

	mX *= scalar;
	mY *= scalar;
	mZ *= scalar;

}
bool CVector3::operator==(const CVector3& rhs)
{
	return
		mX == rhs.mX &&
		mY == rhs.mY &&
		mZ == rhs.mZ;
}
bool CVector3::operator!=(const CVector3& rhs)
{
	return
		mX != rhs.mX &&
		mY != rhs.mY &&
		mZ != rhs.mZ;
}

float CVector3::Length()
{
	return sqrtf(mX * mX + mY * mY + mZ * mZ);
}
void CVector3::Normalize()
{
	float len = Length();

	mX /= len;
	mY /= len;
	mZ /= len;
}
float CVector3::Dot(const CVector3& rhs)
{
	float dotP = mX * rhs.mX + mY * rhs.mY + mZ * rhs.mZ;
	return dotP;
}
CVector3 CVector3::Cross(CVector3& rhs)
{

	CVector3 sum(0, 0, 0);
	sum.mX = (mY * rhs.mZ) - (mZ * rhs.mY);
	sum.mY = (mZ * rhs.mX) - (mX * rhs.mZ);
	sum.mZ = (mX * rhs.mY) - (mY * rhs.mX);

	return sum;
}
float* CVector3::ToFloatArray()
{
	/*
	This code returns the address of the first component of this vector. However, we must remember that
	the memory of class objects is contiguous, just like we saw with arrays.
	float mX;
	float mY;
	float mZ;
	The memory of mY comes directly after mX, and the memory for mZ comes directly after mY. The above
	memory layout is equivalent to:
	float v[3];
	Thus, by getting a pointer to mX, we are implicitly getting a pointer to the first element in a threeelement
	array, which represents the vector components. We can now access the x-, y-, and zcomponents
	using the array bracket operator:
	Vector3 w(-5.0f, 2.0f, 0.0f);
	float* wArray = w.toFloatArray();
	// wArray[0] == w.x == -5.0f
	// wArray[1] == w.y == 2.0f
	// wArray[2] == w.z == 0.0f
	*/
	return &mX;
}
void CVector3::Print()
{
	std::cout << "<" << mX << ", " << mY << ", " << mZ << "> \n";
}
