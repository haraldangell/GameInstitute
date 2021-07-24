#pragma once
#include <iostream>

template <class T>
class TempArray
{
public:
	TempArray();
	~TempArray();

	TempArray(int size);
	TempArray(const TempArray<T>& rhs);


	TempArray<T>& operator=(const TempArray<T>& rhs);

	void resize(int newSize);
	int size() const;

	typename T& operator[](int i) const;

private:
	typename T * mData;
	int mSize;
};


template<class T>
TempArray<T>::TempArray()
{
	mData = nullptr;
}

template<class T>
TempArray<T>::~TempArray()
{
	delete[] mData;
	mData = nullptr;
}

template<class T>
TempArray<T>::TempArray(int size)
{
	mData = new T[size];
}

template<class T>
TempArray<T>::TempArray(const TempArray<T>& rhs)
{
	mData = rhs.mData;
	mSize = rhs.mSize;
}

template<class T>
typename TempArray<T>& TempArray<T>::operator=(const TempArray<T>& rhs)
{
	if (this != &rhs)
	{
		this->mData = rhs.mData;
		this->mSize = rhs.mSize;
	}
	return *this;
}

template<class T>
void TempArray<T>::resize(int newSize)
{
	mData = new T[newSize];
	mSize = newSize;
	for (int i = 0; i < newSize; ++i)
		mData[i] = 0;
}

template<class T>
int TempArray<T>::size() const
{
	return mSize;
}

template<class T>
T & TempArray<T>::operator[](int i) const
{
	return mData[i];
}
