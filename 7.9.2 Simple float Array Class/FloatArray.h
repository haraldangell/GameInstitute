#pragma once
class FloatArray
{
public:
	FloatArray();
	FloatArray(int size);
	FloatArray(const FloatArray& rhs);
	~FloatArray();

	FloatArray& operator=(const FloatArray& rhs);

	void resize(int newSize);
	int size() const;

	float& operator[](int i) const;

private:
	float* mData;
	int mSize;
};
