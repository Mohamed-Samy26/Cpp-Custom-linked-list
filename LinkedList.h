#pragma once
#include <stack>

template <class T>
class Node
{
	public:
	Node<T>* next;
	T value;
	Node();                 
	Node(T val);
};

//Class to handle edited nodes
template <class T>
class HistoryNode
{
public:
	Node<T>* old;
	T value;
	char op;
	int id;
	HistoryNode(Node<T>* prev, int x, char m);
};


template <class T>
class LinkedList
{
	int count;
	int undoCount;
	Node<T>* head;
	Node<T>* tail;
public:
	std::stack<HistoryNode<T>*> history;
	LinkedList();
	int Length();
	T At(int);
	Node<T>* nodeAt(int);
	void InsertAt(int,T);
	void Append(T);
	void DeleteAt(int);
	void undo();
	~LinkedList(void);
};