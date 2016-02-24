#pragma once
template <class T>
class Node
{
public:
	T *Data;
	Node<T> *Next;
	Node();
};
template <class T>
class List
{
	long int size;
	Node<T> *pHead;
	Node<T> *pTail;
public:
	List();
	void AddNewElement(T *Data);
	void DeleteElement(unsigned int index);
	T *GetElement(unsigned int index);
	~List();
};

template<class T>
inline List<T>::List()
{
	Head = NULL;
	size = 0;
}

template<class T>
inline void List<T>::AddNewElement(T *Data)
{
	Node<T>* temp = pHead;
	if (temp == NULL)
	{
		pHead = pTail = new Node<T>(Data);
		return;
	}
	else
	{
		pTail->Next = new Node<T>(Data);
		pTail = pTal->Next;
	}
	size++;

}

template<class T>
inline void List<T>::DeleteElement(unsigned int index)
{
	Node<T>* temp = pHead;
	if (temp != NULL)
	{
		throw 0;
	}
	else
	{
		while()
	}
	size--;
}

template<class T>
inline T* List<T>::GetElement(unsigned int index)
{
}

template<class T>
inline List<T>::~List()
{
}

template<class T>
inline Node<T>::Node(T* temp)
{
	Data = temp;
}
