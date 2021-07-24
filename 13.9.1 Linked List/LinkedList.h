#pragma once

template<typename T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList& rhs);
	LinkedList& operator=(const LinkedList& rhs);
	bool isEmpty();
	LinkedNode* getFirst();
	LinkedNode* getLast();
	void insertFirst(T data);
	void insertLast(T data);
	void insertAfter(T tKey, T tData);
	void removeFirst();
	void removeLast();
	void remove(T removalCandidate);
	void destroy();
private:
	LinkedNode<T>* mFirst;
	LinkedNode<T>* mLast
};

template<typename T>
inline LinkedList<T>::LinkedList()
{
	mFirst = nullptr;
	mLast = nullptr;
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	destroy();
}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList & rhs)
{
	mFirst = rhs;
}

template<typename T>
inline LinkedList & LinkedList<T>::operator=(const LinkedList & rhs)
{
	// TODO: insert return statement here
}

template<typename T>
inline bool LinkedList<T>::isEmpty()
{
	if(!*this == null)
		return false;
	return true;
}

template<typename T>
inline LinkedNode * LinkedList<T>::getFirst()
{
	return *mFirst;
}

template<typename T>
inline LinkedNode * LinkedList<T>::getLast()
{
	return *mLast;
}

template<typename T>
inline void LinkedList<T>::insertFirst(T data)
{
	LinkedNode<T>* newNode = new LinkedNode<T>(tData);
	// If the list is empty, this is the first and the last node
	// and doesn't have a previous ptr.
	if (IsEmpty())
		mLast = newNode;
	// If the list is not empty, the new node becomes the previous
	// node of the current first node.
	else
		mFirst->prev = newNode;
	// The new node's next ptr is the old first ptr. May be null
	// if this is the first node being added to the list.
	newNode->next = mFirst;
	// The new node becomes the first ptr.
	mFirst = newNode;
}

template<typename T>
inline void LinkedList<T>::insertLast(T data)
{
	mLast = LinkedList<T>(data);
}

template<typename T>
inline void LinkedList<T>::insertAfter(T tKey, T tData)
{
	if (IsEmpty()) return false;
	// Get a ptr to the front of the list
	LinkedNode<T>* current = mFirst;
	// Loop until we find tKey (the value of the node to
	// insert after)
	while (current->data != tKey)
	{
		// Hop to the next node
		current = current->next;
		// Test if we reached the end, if we did we didn't
		// find the node to insert after (tKey).
		if (current == 0)
			return false;
	}

	// Allocate memory for the new node to insert.
	LinkedNode<T>* newNode = new LinkedNode<T>(tData);
	// Special case: Are we inserting after the last node?
	if (current == mLast)
	{
		newNode->next = 0;
		mLast = newNode;
	}
	// No, link in newNode after the current node.
	else
	{
		newNode->next = current->next;
		current->next->prev = newNode;
	}
	newNode->prev = current;
	current->next = newNode;
	return true;
}

template<typename T>
inline void LinkedList<T>::removeFirst()
{
	//Needs do a loop and get the first of the once to see where the one has
	delete mFirst;
	mFirst = nullptr;
}

template<typename T>
inline void LinkedList<T>::removeLast()
{
	//Needs do a loop and get the first of the once to see where the one has null for last
	delete mLast;
	mLast = nullptr;
}

template<typename T>
inline void LinkedList<T>::remove(T removalCandidate)
{
}

template<typename T>
inline void LinkedList<T>::destroy()
{
	// Is there at least one node in the list?
	if (mFirst != 0)
	{
		// Get a pointer to the first node.
		LinkedNode<T>* current = mFirst;
		// Loop until the end of the list.
		while (current != 0)
		{
			// Save the current node.
			LinkedNode<T>* oldNode = current;
			// Move to the next node.
			current = current->next;
			// Delete the old node.
			delete oldNode;
			oldNode = 0;
		}
	}
}
