#include "FloatArray.h"



FloatArray::FloatArray()
{
	mData = nullptr;
	mSize = 0;
}

FloatArray::FloatArray(int size)
{
	mData = new float[size];
}

FloatArray::FloatArray(const FloatArray & rhs)
{
	mData = rhs.mData;
	mSize = rhs.mSize;
}


FloatArray::~FloatArray()
{
	delete[] mData;
	mData = nullptr;
}

FloatArray & FloatArray::operator=(const FloatArray & rhs)
{
	if (this != &rhs)
	{
		this->mData = rhs.mData;
		this->mSize = rhs.mSize;
	}
	return *this;
}

void FloatArray::resize(int newSize)
{
	mData = new float[newSize];
	mSize = newSize;
	for (int i = 0; i < newSize; ++i)
		mData[i] = 0;
}

int FloatArray::size() const
{
	return mSize;
}

float & FloatArray::operator[](int i) const
{
	return mData[i];
}
