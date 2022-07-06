#include "LinkedList.h"
#include <iostream>
#include <string>
using namespace std;

LinkedList::LinkedList() : mySize(0), first(nullptr), last(nullptr)
{
}

LinkedList &LinkedList::operator=(const LinkedList &oriList)
{
	//�������
	removeAll();

	//��ʼ��������
	this->mySize = oriList.mySize;
	if (oriList.mySize == 0)
	{
		this->first = nullptr;
		this->last = nullptr;
	}
	else
	{
		this->first = new Node(oriList.first->data);
		NodePtr current = this->first;
		NodePtr currentOri = oriList.first;

		while (currentOri->next != nullptr)
		{
			current->next = new Node(currentOri->next->data);
			current = current->next;
			currentOri = currentOri->next;
		}

		this->last = current;
	}

	return *this;
}

LinkedList::~LinkedList()
{
	removeAll();
}

void LinkedList::add(int index, ElementType dataVal)
{
	if (index > mySize)
	{
		cerr << "index (" << index << ") is larger than list size (" << mySize << ") !" << endl;
	}
	else
	{
		NodePtr newNode = new Node(dataVal);
		if (index == 0)
		{
			newNode->next = first;
			first = newNode;
		}
		else
		{
			NodePtr current = first;
			int cnt = 0;
			while (cnt < mySize - 1)
			{
				current = current->next;
				cnt++;
			}
			newNode->next = current->next;
			current->next = newNode;

			//ǡ�ó������һ��Ԫ��
			if (last->next == nullptr)
			{
				last = last->next;
			}
		}
		mySize++;
	}
}

void LinkedList::add(ElementType dataVal)
{
	NodePtr newNode = new Node(dataVal);
	if (first == nullptr)
	{
		first = newNode;
		last = newNode;
	}
	else
	{
		last->next = newNode;
		last = newNode;
	}
	mySize++;
}

ElementType LinkedList::get(int index) const
{
	if (index > mySize - 1)
	{
		cerr << "index (" << index << ") is larger than last index (" << mySize - 1 << ") !" << endl;
		return 0;
	}
	else
	{
		int cnt = 0;
		NodePtr current = first;
		while (cnt < index)
		{
			current = current->next;
			cnt++;
		}

		return current->data;
	}
}

ElementType LinkedList::getLast() const
{
	return first->data;
}

ElementType LinkedList::getFirst() const
{
	return last->data;
}

int LinkedList::getSize() const
{
	return mySize;
}

void LinkedList::remove(int index)
{
	if (index > mySize - 1)
	{
		cerr << "index (" << index << ") is larger than last index (" << mySize - 1 << ") !" << endl;
	}
	else
	{
		NodePtr delNode = nullptr;
		if (index == 0)
		{
			//ֻ��һ��Ԫ��
			if (first->next == nullptr)
			{
				delNode = first;
				first = nullptr;
				last = nullptr;
			}
			//��ֹһ��Ԫ��
			else
			{
				delNode = first;
				first = first->next;
			}
		}
		else
		{
			NodePtr current = first;
			int cnt = 0;
			while (cnt < index - 1)
			{
				current = current->next;
				cnt++;
			}
			delNode = current->next;
			current->next = current->next->next;

			//ɾ��ǡ�������һ��Ԫ��
			if (delNode->next == nullptr)
			{
				last = current;
			}
		}
		delete delNode;
		mySize--;
	}
}

void LinkedList::removeAll()
{
	if (first != nullptr)
	{
		NodePtr delPtr = first;
		NodePtr current = delPtr->next;
		while (delPtr->next != nullptr)
		{
			delete delPtr;
			delPtr = current;
			current = current->next;
		}
		delete delPtr;

		first = nullptr;
		last = nullptr;
	}
}

void LinkedList::display(std::ostream &os, const char *seperator = "\t") const
{
	if (first == nullptr)
	{
		os << "Empty List." << seperator;
	}
	else
	{
		int cnt = 0;
		NodePtr current = first;
		while (cnt < mySize)
		{
			os << *current << seperator;
			current = current->next;
			cnt++;
		}
		os << endl;
	}
}

void LinkedList::set(int index, int dataVal)
{
	if (index > mySize - 1)
	{
		cerr << "index (" << index << ") is larger than last index (" << mySize - 1 << ") !" << endl;
	}
	else
	{
		int cnt = 0;
		NodePtr current = first;
		while (cnt < index)
		{
			cnt++;
			current = current->next;
		}
		current->data = dataVal;
	}
}

void LinkedList::reverse()
{
	if (mySize < 2)
	{
		// ֻ��һ��Ԫ�ػ��߿��б��ɶ������
	}
	else if (mySize == 2)
	{
		last->next = first;
		first = last;
		last = last->next;
	}
	else if (mySize > 2)
	{
		NodePtr n1, n2, n3;
		n1 = first;
		n2 = first->next;
		n3 = first->next->next;
		first->next = nullptr;
		last = first;

		// �ܹ�n��Ԫ�أ���n-2�Ρ���ѭ���У�ֻ��n2�ĺ�̹ҽӵ�n1�ϡ�����˳�ѭ����ʱ��n1ָ�����ڶ���Ԫ�أ�n2ָ������һ��Ԫ�أ���ѭ���⽫n2�ҽӵ�n1,�ɷ�ֹn3ȥѰ�ҿ�ָ��ĺ�̡�

		int cnt = 0;
		while (cnt < mySize - 2)
		{
			cnt++;
			n2->next = n1;

			n1 = n2;
			n2 = n3;
			n3 = n3->next;
		}
		n2->next = n1;
		first = n2;
	}
}

std::ostream &operator<<(std::ostream &os, const Node &oriNode)
{
	// Node�д洢������Ԫ��������Ҫ����һ��<<�������Ҫ��Ȼ����Ļ���ָ��ָ��ĵ�ַ
	os << oriNode.data;
	return os;
}

std::ostream &operator<<(std::ostream &os, const LinkedList &oriList)
{
	oriList.display(os);
	return os;
}
