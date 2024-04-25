#include <iostream>

using namespace std;
template <class type>
struct node{
    type info;// data inside each node
    node<type> *next;
    node<type> *prev;
};
template <class type>
class circularDoubleLinkedList{
private:
    node<type> *first;
    node<type> *last;
    int count;//number of nodes in the list
public:
    circularDoubleLinkedList(){//default constructor initializes the list as an empty list
     first=NULL;
     last=NULL;
     count=0;
    }
    void insertAtHead(const type& insertItem);//2 cases:1)list is empty 2)list isn't empty
    void insertAtTail(const type& insertItem);
    void insertAt(const type& insertItem, int index);
    void removeAtHead();
    void removeAtTail();
    void removeAt(int index);
    type retrieveAt(int index) const;
    void replaceAt(const type& newElement, int index);
    bool isExist(const type& element);
    bool isItemAtEqual(const type& element, int index);
    void swap(int firstItemIdx, int secondItemIdx);
    void clear();
    void print() const;
    bool isEmpty();
    int circularDoubleLinkedListSize() const;
};
template <class type>
void circularDoubleLinkedList<type>::insertAtHead(const type& insertItem){
    node<type> *newNode;
    newNode = new node<type>;
    newNode->info = insertItem;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (first == last && first == NULL){//empty list
        first=last=newNode;
        first->next=last->next=first;
        first->prev=last->prev=first;
        count++;
    }
    else{
        newNode->next=first;
        newNode->prev=last;
        first->prev=newNode;
        last->next=newNode;
        first=newNode;
        count++;
    }
}

template <class type>
void circularDoubleLinkedList<type>:: insertAtTail(const type& insertItem){
    node<type> *newNode;
    newNode=new node<type>;
    newNode->info=insertItem;
    newNode->next=NULL;
    newNode->prev=NULL;
    if(first==NULL){
        first=last=newNode;
        first->next=last->next=newNode;
        first->prev=last->prev=newNode;
        count++;
    }
    else{
        newNode->next=first;
        newNode->prev=last;
        last->next=newNode;
        first->prev=newNode;
        last=newNode;
        count++;
    }
}
template<class type>
void circularDoubleLinkedList<type>:: insertAt(const type& insertItem, int index){
    node<type> *newNode;
    newNode=new node<type>;
    newNode->info=insertItem;
    newNode->next=NULL;
    newNode->prev=NULL;
    if(index<0 || index>count){//not in the range of the linked list,, not >= bcz if index=count can be considered as inserting after the last element as index starts from 0 till count-1 so the range continues till count+1 as last element
        cout<<"invalid position"<<endl;
        return;
    }
    else if(first==NULL){
        return;
    }
    else if(index==0){//either an empty list or we insert before the head
        insertAtHead(insertItem);
        return;
    }

    else{
        node<type> *current;
        current= first;
        int pos=0;
        while(current->next!=first && pos!=index){//loop to traverse the list and stop the current node at the given index
            current=current->next;
            pos++;
        }
        if(current->next==first && index==count){//we reached the end of the list and the given index is the end
            insertAtTail(insertItem);
            return;
        }
        else if(pos==index){//if the index is in the middle of the list
            newNode->next=current;
            newNode->prev=current->prev;
            newNode->prev->next=newNode;
            current->prev=newNode;
            count++;
        }
        else{
            cout<<"position isn't found"<<endl;
        }
    }

}
template <class type>
void circularDoubleLinkedList<type>:: removeAtHead(){
    node<type> *current;//let current be the node to be deleted
    current=new node<type>;
    if(first==NULL){
        cout<<"can't delete from an empty list"<<endl;
        return;

    }
    current=first;
    if(current->next==current){//if the list contains one element
        delete current;
        first=last=NULL;
        count--;
    }

    else{
        current=first;
        first=first->next;//now the head is the second node in th list
        first->prev=last;
        last->next=first;
        delete current;
        count--;//decrement for the deleted node
    }
}
template <class type>
void circularDoubleLinkedList<type>:: removeAtTail(){
    node<type> *current;
    current=new node<type>;
    if(first==NULL){
        cout<<"can't delete from an empty list"<<endl;
        return;

    }
    current=first;
    if(current->next==current){//if the list contains one element
        delete current;
        first=NULL;
        last=NULL;
        count--;
    }
    else{
        current=last;
        last=last->prev;
        first->prev=last;
        last->next=first;

        delete current;
        count--;

    }
}
template <class type>
void circularDoubleLinkedList<type>:: removeAt(int index){
    if(index<0 || index>=count){//not in the range of the linked list
        cout<<"invalid position"<<endl;
        return;

    }
    else if(first==NULL){
        cout<<"can't delete from an empty list"<<endl;
        return;
    }
    else if(index==0){
        removeAtHead();
        return;
    }
    else{
        node<type> *current;
        current= first;
        int pos=0;
        while(current->next!=NULL && pos!=index){//loop to traverse the list and stop the current node at the given index
            current=current->next;
            pos++;
        }
        if(current->next==NULL && index==(count-1)){//we reached the end of the list and the given index is the end
            removeAtTail();
            return;
        }
        else if(pos==index){//if the index is in the middle of the list
            current->prev->next=current->next;
            current->next->prev=current->prev;
            delete current;
            count--;
        }
        else{
            cout<<"position isn't found"<<endl;
        }
    }

}
template<class type>
type circularDoubleLinkedList<type>:: retrieveAt(int index) const{
    node<type> *current=first;
    int pos=0;
    if(index<0 || index>=count){
        cout<<"invalid position"<<endl;
        return -1;
    }
    else if(index==0){
        return first->info;
    }
    else if(index==(count-1)){
        return last->info;
    }
    else{
       while(current->next!=first &&pos!=index){
        current=current->next;
        pos++;
        }
        if(pos==index){
            return current->info;
        }
    }
}
template<class type>
void circularDoubleLinkedList<type>:: replaceAt(const type& newElement, int index){
    node<type> *current=first;
    int pos=0;
    if(index<0 || index>=count){
        cout<<"invalid position"<<endl;
        return;
    }
    else{
        while(current->next!=first &&pos!=index){
            current=current->next;
            pos++;
        }
        if(pos==index){
            current->info=newElement;
        }
    }
}
template<class type>
bool circularDoubleLinkedList<type>:: isExist(const type& element){
    node<type> *current=first;
    do{
        if(current->info==element){
            return true;
        }
        current=current->next;

    }while(current!=first);
    return false;
}
template<class type>
bool circularDoubleLinkedList<type>:: isItemAtEqual(const type& element, int index){
    if(index<0 || index>=count){
        cout<<"invalid position"<<endl;
        return false;
    }
    else{
        node<type> *current=first;
        int pos=0;
        while(current->next!=first && pos!=index){
            current=current->next;
            pos++;
        }
        if(pos==index){
            if(current->info==element){
                return true;
            }
        }
        return false;

    }

}
template<class type>
void circularDoubleLinkedList<type>:: swap(int firstItemIdx, int secondItemIdx){
    if(firstItemIdx<0 || firstItemIdx>=count ||secondItemIdx<0 || secondItemIdx>=count){
        cout<<"invalid position"<<endl;
        return;
    }
    node<type> *temp, *firstswap, *secondswap;
    temp=new node<type>;
    firstswap=first;
    int firstpos=0;
    bool firstfound=false;
    while(firstswap->next!=first && firstpos!=firstItemIdx ){
        firstswap=firstswap->next;
        firstpos++;
    }
    if(firstpos==firstItemIdx){
        firstfound=true;
    }
    secondswap=first;
    int secondpos=0;
    bool secondfound=false;

    while(secondswap->next!=first && secondpos!=secondItemIdx ){
        secondswap=secondswap->next;
        secondpos++;
    }
    if(secondpos==secondItemIdx){
        secondfound=true;
    }
    if(firstfound==true && secondfound==true){
        temp->info=firstswap->info;
        firstswap->info=secondswap->info;
        secondswap->info=temp->info;
        delete temp;
    }

}
template <class type>
void circularDoubleLinkedList<type>::clear(){
    if(first==last && first==NULL){
        cout<<"the list is already empty"<<endl;
        return;
    }
    else{
        node<type> *current;
        current=first;
        do {
            node<type> *temp = current;
            current = current->next;
            delete temp;
        } while (current != first);
        first=last=NULL;
        count=0;
    }
}
template <class type>
void circularDoubleLinkedList<type>::print() const{
    if(first==last && first==NULL){
        cout<<"can't print an empty list"<<endl;
    }
    else{
        node<type> *current;
        current=first;
        do{
            cout<<current->info<<" ";
            current=current->next;
        }while(current!=first);
        cout<<endl;
    }
}
template <class type>
bool circularDoubleLinkedList<type>::isEmpty(){
    return(first==last & first==NULL);
}
template <class type>
int circularDoubleLinkedList<type>::circularDoubleLinkedListSize() const{
    return count;
}

int main()
{
    circularDoubleLinkedList<int> dl;
    cout<<"if empty 1, not empty 0: "<<dl.isEmpty()<<endl;
    dl.clear();
    dl.insertAtTail(8);
    dl.print();
    dl.insertAtHead(1);
    dl.insertAtTail(2);
    dl.print();
    cout<<dl.retrieveAt(2)<<endl;
    dl.insertAt(44,0);//first index
    dl.print();

    dl.insertAt(45,4);//last index
    dl.print();
    dl.insertAt(46,2);//middle
    dl.print();
    cout<<"if exist 1, not exist 0: "<<dl.isExist(1)<<endl;
    cout<<"if Item At given index equal the item given 1, not equal 0: "<<dl.isItemAtEqual(44,0)<<endl;
    dl.swap(2,3);// two in the middle
    dl.print();
    dl.swap(0,5);// first and last
    dl.print();
    dl.removeAt(1);
    dl.print();
    cout<<"The given index contains the element= "<<dl.retrieveAt(1)<<endl;
    dl.replaceAt(888,4);
    dl.print();
    dl.removeAtTail();
    dl.print();

    dl.clear();
    dl.insertAtHead(3);
    dl.insertAtHead(5);

    dl.print();

    dl.removeAtTail();
    dl.print();
    cout<<"if empty 1, not empty 0: "<<dl.isEmpty()<<endl;
    cout<<"The circular double linked list size= "<<dl.circularDoubleLinkedListSize()<<endl;
    dl.clear();
    dl.print();

    return 0;
}
