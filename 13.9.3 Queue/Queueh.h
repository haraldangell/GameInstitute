#pragma once
template<class T>
class Queue
{
public:
	Queue();
	~Queue();
	T& getFirst();
	bool isEmpty();
	void push(T newElement);
	void pop();
private:
	LinkedList<T> mList;
};