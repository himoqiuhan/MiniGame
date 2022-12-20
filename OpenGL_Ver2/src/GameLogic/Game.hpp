#pragma once

#include <iostream>

using namespace std;

template <typename T>

class CLListNode
{
public:
	CLListNode():data(NULL),next(NULL){};
	~CLListNode();
	void PushElem(T* newE);
	T* getElem(int num) const
	{
		CLListNode* temp = this;
		for (int i = 0; i < num; i++)
		{
			temp = temp->next;
		}
		return temp->data;
	}
private:
	T* data;
	CLListNode* next;
};

template <typename T>
void CLListNode<T>::PushElem(T* newE)
{
	if (this->data == NULL)
	{
		this->data == T;
	}
	else
	{
		CLListNode* temp = this;
		while (temp->next != this)
		{
			temp = this->next;
		}
		temp->next = new CLListNode();
		temp->next->data = T;
		temp->next->next = this;
	}
	
}
template< typename T>
CLListNode<T>::~CLListNode()
{
	CLListNode* p=this->next, * pre=this;
	pre = p, p = p->next;
	while (p != this)
	{
		free(pre);
		pre = p, p->next;
	}
	free(pre);
	free(p);
}

