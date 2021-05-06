#pragma once

// Node class declaration

template <class T>
class Node
{
public:              // it is not very good to put these class members under public, but for the purposes of this assignment,
	Node<T>* next;   // I didn't think implementing extra methods to return these pointers would be necessary
	Node<T>* prev;
	T data;
	Node(const T& item = 0, Node<T>* ptrNext = NULL, Node<T>* ptrPrev = NULL);
	void InsertAfter(Node<T>* p);

};

// Node class implementation

template <class T> // constructor
Node<T>::Node(const T& item, Node<T>* ptrNext, Node<T>* ptrPrev)
{
	data = item;
	next = ptrNext;
	prev = ptrPrev;
}

// this method is to add a node to next of the node operated on
template <class T>
void Node<T>::InsertAfter(Node<T>* p)
{
	p->next = next;
	next = p;
	p->prev = this;
}


// allocating a new node and returning it
template <class T>
Node<T>* GetNode(const T& item, Node<T>* prevPtr = NULL, Node<T>* nextPtr = NULL)
{
	Node<T>* newNode;
	newNode = new Node<T>(item, nextPtr, prevPtr);
	if (newNode == NULL)
	{
		exit(EXIT_FAILURE);
	}
	return newNode;
}

// StackQueue2 class declaration
// methods have the same names as the ones in StackQueue class
// I only declared/implemented what I thought was necessary,
// this a doubly-linked list class is not exactly the same as the one covered in lectures
template <class T>
class StackQueue2
{
private:
	int numOfElements;
	Node<T>* head;
	Node<T>* tail;
public:
	StackQueue2(); // constructor with no arguments
	void push_front(const T& item);
	T pop_front();
	T pop_rear();
	int numOfE();
	T get_front();

};

template <class T>
T StackQueue2<T>::get_front() // just returns the T data, doesn't remove it from storage
{
	return head->data;
}

template <class T>
int StackQueue2<T>::numOfE() // returns number of elements in the storage
{
	return numOfElements;
}

template <class T>
T StackQueue2<T>::pop_rear()
{
	T temp = tail->data; // temporarily holds the T data from the current Node since it will be abandoned
	tail = tail->next;   // sets the end(tail) of the list to the next node
	numOfElements--;
	return temp;    // returns the T data
}

template <class T>
T StackQueue2<T>::pop_front()
{
	T temp = head->data;    // again, temporarily holds data
	head = head->prev;      // sets the start(head) of the list to the previous node
	numOfElements--;
	return temp;
}

template <class T>
StackQueue2<T>::StackQueue2()   // next and prev pointers are not initialized, they are pointed
{                               // to a Node after the first push_front operation in the main method.
	numOfElements = 0;
}

template <class T>
void StackQueue2<T>::push_front(const T& item)
{
	numOfElements++;
    if (numOfElements > 1)  // head and tail pointers are not initialized while numOfElements<=1
	{
		head->next = GetNode(item, head);   // allocates a new node and puts it next to the current one
		head = head->next;                  // new node is assigned to be the new head of the list
	}
	else                    // head and tail are initialized only for the first time push_front is called
	{
		head = GetNode(item, head);
		head->next=head;    // next node is itself, only for the first call of push_front
	}
	if (numOfElements==1)   // initializes tail as same as head on the first call
		tail = head;
}


