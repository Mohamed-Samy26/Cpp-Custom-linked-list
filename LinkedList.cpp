#include "LinkedList.h"
#include <assert.h>
#include<iostream>

template <class T>
Node<T>::Node()
{
	value=0;
	next=0;
}

template <class T>
Node<T>::Node(T val)
{
	value=val;
	next=0;
}

template<class T>
HistoryNode<T>::HistoryNode(Node<T>* prev, int x, char m)
{
	old = prev;
	id = x;
	op = m;
	value = prev->value;
}

template <class T>
LinkedList<T>::LinkedList(void)
{
	head=tail=0;
	count=0;
	undoCount = 0;
}

template <class T>
int LinkedList<T>::Length()
{
	return count;
}

template <class T>
void LinkedList<T>::Append(T val)
{
	Node<T>* newNode=new Node<T>(val);
	if (head == 0) {
		head=tail=newNode;
		history.push(new HistoryNode<T>(tail, -1, 'f')); //first node
	}
	else
	{
		Node<T>* oldNode = tail;
		tail->next=newNode;
		tail=newNode;
		history.push(new HistoryNode<T>(head , -1 ,'a'));
	}
	count++;
}

template <class T>
T LinkedList<T>::At(int pos)
{
	assert(pos>=0&&pos<count);
	Node<T>* tmp=head;
	for(int i=0;i<pos;i++)
		tmp=tmp->next;
	return tmp->value;
}

template <class T>
Node<T>* LinkedList<T>::nodeAt(int pos)
{
	assert(pos>=0&&pos<count);
	Node<T>* tmp=head;
	for (int i = 0; i < pos; i++)
		std::cout << tmp;
		tmp=tmp->next;
	return tmp;
}

template <class T>
void LinkedList<T>::InsertAt(int pos, T val)
{
	assert(pos>=0&&pos<count);
	Node<T>* oldNode = tail;
	Node<T>* tmp=head;
	Node<T>* newNode=new Node<T>(val);
	if(pos==0)
	{
		newNode->next=head;
		head=newNode;
	}
	else
	{
		for(int i=0;i<pos-1;i++)
			tmp=tmp->next;
	
		newNode->next=tmp->next;
		tmp->next=newNode;
	}
	history.push(new HistoryNode<T>(oldNode, pos, 'i'));
	count++;

}

template <class T>
void LinkedList<T>::DeleteAt(int pos)
{
	std::cout << "Count : " << count << " POS: " << pos <<"\n";
	assert(pos>=0&&pos<count);
	Node<T>* tmp=head;
	if(pos==0)
	{
		head=head->next;
		Node<T>* oldNode = tmp;
		//handle history stack
		history.push(new HistoryNode<T>(oldNode, pos, 'd'));
		delete tmp;
	}
	else
	{
		for(int i=0;i<pos-1;i++)
			tmp=tmp->next;
		Node<T>* del=tmp->next;
		tmp->next=del->next;
		Node<T>* oldNode = del;
		history.push(new HistoryNode<T>(oldNode, pos, 'd'));
		delete del;
		if(pos==count-1)
			tail=tmp;
	}
	count--;
}


//Main undo function to handle reverting
template<class T>
void LinkedList<T>::undo()
{
	if (history.empty())
	{
		std::cout << "No recent history!! \n";
	}
	else
	{
		std::cout << "Undoing ... \n";
		HistoryNode<T>* rev = history.top();
		history.pop();
		switch (rev->op)
		{
			case 'a':
			{
				/*cout<<"UN-Appending "<<rev->value<<"\n";
				Node<T>* tmp = nodeAt(Length());
				delete tail;
				tail = tmp;
				count--;*/
				DeleteAt(Length());
				break;
			}
			case 'i':
			{
				DeleteAt(rev->id);
				break;
			}
			case 'd':
			{
				InsertAt(rev->id, rev->value);
				break;
			}
			case 'f': //first inserted node
			{
				delete tail;
				break;
			}
			default:
				break;
			}
	}
}


template <class T>
LinkedList<T>::~LinkedList(void)
{
	while(count!=0)
		DeleteAt(0);
}
