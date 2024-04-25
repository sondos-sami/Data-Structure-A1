#include <iostream>
using namespace std;
template<typename T>
class C_Single_linked_list {
	struct Node
	{
		T item;
		Node* next;
	};
	Node* Head;
	Node* Tail;
	int length;
public:
	C_Single_linked_list() {
		Head = Tail = NULL;
		length = 0;

	}
	bool isEmpty() {
		return length == 0;
	}
	void insertAtHead(T element)
	{
		Node* newNode = new Node;
		newNode->item = element;
		if (length == 0)
		{
			Head = Tail = newNode;
			newNode->next = Head;
		}
		else {
			newNode->next = Head;
			Tail->next = newNode;
			Head = newNode;
		}
		length++;
	}
	void insertAtTail(T element)
	{
		Node* newNode = new Node;
		newNode->item = element;
		if (length == 0)
		{
			Head = Tail = newNode;
			newNode->next = Head;
		}
		else
		{
			Tail->next = newNode;
			newNode->next = Head;
			Tail = newNode;
		}
		length++;

	}
	void insertAt(int pos, T element)
	{
		if (pos<0 || pos>length)
		{
			cout << "Out of range can not be insert." << endl;
			return;
		}
		else
		{
			Node* newNode = new Node;
			newNode->item = element;
			if (pos == 0)
			{
				insertAtTail(element);
			}
			else if (pos == length)
			{
				insertAtTail(element);
			}
			else
			{
				// Current point to the node before the position i want to add in (Previous pos)
				Node* Current = Head;
				for (int i = 1;i < pos;i++)
				{
					Current = Current->next;
				}
				newNode->next = Current->next;
				Current->next = newNode;
				length++;
			}
		}
	}
	void removeAtHead()
	{
		if (length == 0)
		{
			cout << "The list is empty! Can not remove." << endl;
			return;
		}
		else if (length == 1)
		{
			delete Head;
			Tail = Head = NULL;
			length = length - 1;
		}
		else
		{
			Node* temp;
			temp = Head;
			Head = Head->next;
			Tail->next = Head;
			delete temp;
			length = length - 1;
		}
	}
	void removeAtTail()
	{
		if (length == 0)
		{
			cout << "The list is empty! Can not remove." << endl;
			return;
		}
		else if (length == 1)
		{
			delete Head;
			Head = Tail = NULL;
			length = length - 1;
		}
		else
		{
			Node* Prev = Head;//the previous position to i want to delete to make the Tail point to it
			Node* Curr = Head->next;//position i want to delete
			//after this loop the curr point to the pos to delete and the prev is previous of it
			while (Curr != Tail)
			{
				Prev = Curr;
				Curr = Curr->next;
			}
			delete Curr;
			Tail = Prev;
			Prev->next = Head;
			length = length - 1;
		}
	}
	void removeAt(int pos)
	{
		if (pos < 0 || pos >= length)
		{
			cout << "Out of range! Can not delete." << endl;
			return;
		}
		else
		{
			if (pos == 0)
			{
				removeAtHead();
			}
			else if (pos == length - 1)
			{
				removeAtTail();
			}
			else
			{
				Node* Current = Head;
				Node* trailCurrent = NULL;
				for (int i = 0;i < pos;i++)
				{
					trailCurrent = Current;
					Current = Current->next;
				}
				trailCurrent->next = Current->next;
				delete Current;
				length = length - 1;
			}
			if (length > 0)
				Tail->next = Head;//ensure that the list is circular
		}

	}
	T retrieveAt(int pos)
	{
		Node* Curr = Head;
		if (pos < 0 || pos >= length)
		{
			cout << "Out of range!" << endl;
			return -1;
		}
		else
		{
			for (int i = 0;i < pos;i++)
			{
				Curr = Curr->next;
			}
			return Curr->item;
		}
	}
	void replaceAt(T element, int pos)
	{
		if (pos < 0 || pos >= length)
		{
			cout << "Out of range!" << endl;
		}
		else
		{
			Node* Curr = Head;
			for (int i = 0;i < pos;i++)
			{
				Curr = Curr->next;
			}
			Curr->item = element;
		}
	}
	bool isItemAtEqual(T element, int pos)
	{
		Node* Curr = Head;
		for (int i = 0;i < pos;i++)
		{
			Curr = Curr->next;
		}
		return Curr->item == element;

	}
	bool isExist(T element)
	{
		Node* Curr = Head;
		//i will use do while as it circular and i want it exit when the curr point to head back
		do {
			if (Curr->item == element)
			{
				return true;
			}
			Curr = Curr->next;
		} while (Curr != Head);
		return false;
	}
	void swap(int firstItemIdx, int secondItemIdx)
	{
		if (firstItemIdx < 0 || firstItemIdx >= length || secondItemIdx < 0 || secondItemIdx >= length)
		{
			cout << "Out Of Range!" << endl;
			return;
		}
		else if (firstItemIdx == secondItemIdx)//if the two nodes are the same
		{
			return;
		}
		else
		{
			Node* prevNode1 = NULL;//initial value
			Node* prevNode2 = NULL;
			Node* CurrNode1 = Head;
			Node* CurrNode2 = Head;
			// Find the nodes to swap
			for (int i = 0; i < firstItemIdx; i++) {
				prevNode1 = CurrNode1;
				CurrNode1 = CurrNode1->next;
			}
			for (int i = 0;i < secondItemIdx;i++)
			{
				prevNode2 = CurrNode2;
				CurrNode2 = CurrNode2->next;
			}

			if (prevNode1 != NULL) // not prev to the head 
			{
				prevNode1->next = CurrNode2; //as after swap the node2 be after the prevNode1
				// put the prevNode1 link to the previous of Node2
			}

			if (prevNode2 != NULL)
			{
				prevNode2->next = CurrNode1;
			}
			//Swap the pointers of each node
			Node* tmp = CurrNode1->next;
			CurrNode1->next = CurrNode2->next;
			CurrNode2->next = tmp;
			//if the two nodes are adjacent 
			// the pointer of node1 will point to the node1 itself and it is wrong
			if (CurrNode1->next == CurrNode1)
			{
				CurrNode1->next = CurrNode2;
			}
			if (CurrNode2->next == CurrNode1)
			{
				CurrNode2->next = CurrNode1;
			}
			if (firstItemIdx == 0)
			{
				Head = CurrNode2;
			}
			if (secondItemIdx == 0)
			{
				Head = CurrNode1;
			}
			if (CurrNode1 == Tail) Tail = CurrNode2;
			if (CurrNode2 == Tail) Tail = CurrNode1;

			// Ensure the list is circular
			Tail->next = Head;

		}
	}
	int linkedListSize()
	{
		return length;
	}
	void clear()
	{
		while (length > 0)
		{
			removeAtHead();
		}
	}
	void print()
	{
		if (length == NULL)
		{
			cout << "The list is empty!" << endl;
		}
		else {
			Node* C = Head;
			do {
				cout << C->item << " ";
				C = C->next;
			} while (C != Head); // Continue until i back to the Head 
		}
	}


};
int main()
{
	C_Single_linked_list<int> l;
	l.insertAtHead(10);
	l.insertAtHead(90);
	l.insertAtHead(14);
	l.insertAtHead(33);
	/****************************************/
	//cout << l.retrieveAt(0) << endl;
	//cout << l.retrieveAt(2) << endl;
	 //cout << l.retrieveAt(3)<<endl;
	/********************************************************/
	//l.replaceAt(7, 0);
	//l.replaceAt(999, 2);
	//l.print();
	/*************************************/
	//cout<<l.isExist(90)<<endl;//1
	//cout<<l.isExist(-1)<<endl;//0
	/************************************/
	//cout << l.isItemAtEqual(33, 0) << endl;//1
	//cout << l.isItemAtEqual(70, 0) << endl;//0
	/****************************************************/
	//l.swap(0,1);
	//l.swap(0,3);
	//l.swap(2, 3);
	//l.swap(1, 2);
	//l.print();
	/*******************************************************/
	cout << l.linkedListSize() << endl;
	l.print();
	l.clear();
	cout << endl;
	cout << l.linkedListSize() << endl;
	l.print();

}
