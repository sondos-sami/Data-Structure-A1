#include <iostream>

using namespace std;

template <class t>
class stack {
    struct Node {
        t item;
        Node* next;
    };
    Node* Stack_Top, *cur;

public:
    stack() {
        Stack_Top = NULL;
    }

    void push(t value) {
        Node* new_element = new Node;
        if (new_element == NULL)
            cout << "Stack cannot allocate memory";
        else {
            new_element->item = value;
            new_element->next = Stack_Top;
            Stack_Top = new_element;
        }
    }

    bool isEmpty() {
        if (Stack_Top == NULL)
            return true;
        else
            return false;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty, cannot pop";
        }
        else {
            Node* temp = Stack_Top;
            Stack_Top = Stack_Top->next;
            delete temp;
            temp = nullptr;
        }
    }

    void pop(t &poped_element) {
        if (isEmpty())
            cout << "Stack is empty, cannot pop";
        else {
            poped_element = Stack_Top->item;
            Node* temp = Stack_Top;
            Stack_Top = Stack_Top->next;
            delete temp;
            temp = nullptr;
            cout << "poped elemet is : " << poped_element;
        }
    }

    void get_top() {
        if (isEmpty())
            cout << "Stack is empty, cannot get top element" << endl;
        else
            cout << Stack_Top->item;
    }

    void print() {
        cur = Stack_Top;
        cout << "\nItems in the stack: ";
        if (cur == nullptr) {
            cout << "[ ]\n";
            return;
        }
        cout << "[ ";
        while (cur != nullptr) {
            cout << cur->item;
            if (cur->next != nullptr)
                cout << ", ";
            cur = cur->next;
        }
        cout << " ]\n";
    }
};

int main() {
    stack<int> s;

    s.push(5);
    s.push(7);
    s.push(10);
    s.push(12);
    s.pop();
    s.push(15);
    s.push(20);

    s.print();
    cout << endl;

    s.get_top();
    cout << endl;

    return 0;
}
