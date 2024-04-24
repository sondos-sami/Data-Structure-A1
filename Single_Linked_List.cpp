#include <iostream>
using namespace std;
class Single_linked_list {
	struct Node
	{
		int item;
		Node* next;
	};
	Node* Head;
	Node* Tail;
	int length;
public:
	Single_linked_list() {
		Head = Tail = NULL;
		length = 0;

	}
	bool isEmpty() {
		return length == 0;
	}
	void insertAtHead(int element)
	{
		Node* newNode = new Node;
		newNode->item = element;
		if (length == 0)
		{
			Head = Tail = newNode;
			newNode->next = NULL;
		}
		else {
			newNode->next = Head;
			Head = newNode;
		}
		length++;
	}
	void insertAtTail(int element)
	{
		Node* newNode = new Node;
		newNode->item = element;
		if (length == 0)
		{
			Head = Tail = newNode;
			newNode->next = NULL;
		}
		else
		{
			Tail->next = newNode;
			newNode->next = NULL;
			Tail = newNode;
		}
		length++;

	}
	void insertAt(int pos, int element)
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
			Prev->next = NULL;
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
				Node* Current = Head->next;
				Node* trailCurrent = Head;
				for (int i = 1;i < pos;i++)
				{
					trailCurrent = Current;
					Current = Current->next;
				}
				trailCurrent->next = Current->next;
				delete Current;
				length = length - 1;
			}
		}

	}
	int retrieveAt(int pos)
	{
		Node* Curr = Head;
		if (pos < 0 || pos >= length)
		{
			cout << "Out of range!" << endl;
			return -1;
		}
		else
		{
			int indx = 0;
			while (Curr != NULL)
			{
				if (pos == indx)
				{
					return Curr->item;
				}
				Curr = Curr->next;
				indx++;
			}
		}
	}
	void replaceAt(int element, int pos)
	{
		if (pos < 0 || pos >= length)
		{
			cout << "Out of range!" << endl;
		}
		else
		{
			Node* Curr = Head;
			int indx = 0;
			while (Curr != NULL)
			{
				if (pos == indx)
				{
					Curr->item = element;
					return;
				}
				Curr = Curr->next;
				indx++;
			}
		}
	}
	bool isItemAtEqual(int element, int pos)
	{
		Node* Curr = Head;
		int indx = 0;
		while (Curr != NULL)
		{
			if (pos == indx)
			{
				if (Curr->item == element)
					return true;
			}
			Curr = Curr->next;
			indx++;

		}
		return false;

	}
	bool isExist(int element)
	{
		Node* Curr = Head;
		while (Curr != NULL)
		{
			if (Curr->item == element)
			{
				return true;
			}
			Curr = Curr->next;

		}
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
			int indx = 0;
			while (CurrNode1 != NULL and indx < firstItemIdx)
			{
				/* i dont put equal in the past comparison as i want to put
				 the prev point to the previous of the index i want */
				prevNode1 = CurrNode1;
				CurrNode1 = CurrNode1->next;
				indx++;
			}
			int idx = 0;
			while (CurrNode2 != NULL and idx < secondItemIdx)
			{
				prevNode2 = CurrNode2;
				CurrNode2 = CurrNode2->next;
				idx++;

			}
			if (CurrNode1 == NULL || CurrNode2 == NULL)
			{
				cout << "The index of one of the nodes or both is out of the range" << endl;
				return;
			}
			if (prevNode1 == NULL)//it previous to the head(node1 is the head)
			{
				Head = CurrNode2;
			}
			else
			{
				prevNode1->next = CurrNode2; //as after swap the node2 be after the prevNode1
				// put the prevNode1 link to the previous of Node2
			}
			if (prevNode2 == NULL)//same as previous but for node2
			{
				Head = CurrNode1;
			}
			else
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
			else if (secondItemIdx == 0)
			{
				Head = CurrNode1;
			}

		}
	}
	int linkedListSize()
	{
		return length;
	}
	void clear()
	{
		while (Head != NULL)
		{
			Node* tmp = Head;
			Head = Head->next;
			delete tmp;
			length--;
		}
	}
	void print()
	{
		if (length == NULL)
		{
			cout << "The list is empty!" << endl;
			return;
		}
		else {
			Node* C = Head;
			while (C != NULL)
			{
				cout << C->item << " ";
				C = C->next;
			}
		}
	}

};
int main()
{
	Single_linked_list l;
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
	//l.swap(0, 1);
	//l.swap(0,3);
	//l.swap(2, 3);
	//l.print();
	/*******************************************************/
	//cout << l.linkedListSize() << endl;
	//l.print();
	//l.clear();
	//cout << endl;
	//cout << l.linkedListSize() << endl;
	//l.print();
	
}
