#pragma once
template<typename T>
class Stack
{
public:
	Stack();
	~Stack();
	T& getTopItem();
	bool isEmpty(void);
	void push(T newElement);
	void pop();
private:
	LinkedList<T> mList;
};