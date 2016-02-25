#pragma once
template <class T>
class Node
{
public:
	T *Data;
	Node<T> *Next;
	Node(); //default construct
	Node(T* temp);
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
inline Node<T>::Node()
{
}

template<class T>
inline Node<T>::Node(T* temp)
{
	Data = temp;
	NExt = NULL;
}

template<class T>
inline List<T>::List()
{
	pHead = NULL;
	pTail = NULL;
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
		pTail = pTail->Next;
	}
	size++;

}

template<class T>
inline void List<T>::DeleteElement(unsigned int index)
{
	Node<T>* temp = pHead;
	if (index < size)
	{
		if (index != 0)
		{
			for (int i = 0; i < index; i++)
			{
				temp = temp->Next;
			}
			Node<T>* temp2 = temp->Next;
			temp->Next = temp2->Next;
			delete(temp2->Data);
			delete(temp2);
	}
	else
	{
			pHead = pHead->Next;
			delete(temp->Data);
			delete(temp);
		}
	}
	size--;
}

template<class T>
inline T* List<T>::GetElement(unsigned int index)
{
	Node<T> *temp = pHead;
	if (index < size)
	{
		for (int i = 0; i < index; i++)
		{
			temp = temp->Next;
		}
		return temp->Data;
	}
	else return NULL;
}

template<class T>
inline List<T>::~List()
{
}

