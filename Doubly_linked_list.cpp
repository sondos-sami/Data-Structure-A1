#include <iostream>

using namespace std;
template <class type>
struct node{
    type info;// data inside each node
    node<type> *next;
    node<type> *prev;
};
template <class type>
class doubleLinkedList{
private:
    node<type> *first;
    node<type> *last;
    int count;//number of nodes in the list
public:
    doubleLinkedList(){//default constructor initializes the list as an empty list
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
    int doubleLinkedListSize() const;
};
template <class type>
void doubleLinkedList<type>::insertAtHead(const type& insertItem){

    node<type> *newNode;
    newNode =new node<type>;
    newNode->info=insertItem;
    newNode->next=NULL;
    newNode->prev=NULL;
    if(first==NULL){//empty list
        first=newNode;
        last=newNode;
        count++;
    }
    else{//list already has nodes
        first->prev=newNode;
        newNode->next=first;
        first=newNode;
        count++;
    }
}
template <class type>
void doubleLinkedList<type>:: insertAtTail(const type& insertItem){
    node<type> *newNode;
    newNode=new node<type>;
    newNode->info=insertItem;
    newNode->next=NULL;
    newNode->prev=NULL;
    if(first==NULL){
        first=newNode;
        last=newNode;
        count++;
    }
    else{
        last->next=newNode;
        newNode->prev=last;
        last=newNode;
        count++;
    }
}
template<class type>
void doubleLinkedList<type>:: insertAt(const type& insertItem, int index){
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
        while(current->next!=NULL && pos!=index){//loop to traverse the list and stop the current node at the given index
            current=current->next;
            pos++;
        }
        if(current->next==NULL && index==(count)){//we reached the end of the list and the given index is the end
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
void doubleLinkedList<type>:: removeAtHead(){
    node<type> *current;
    current=new node<type>;
    if(first==NULL){
        cout<<"can't delete from an empty list"<<endl;
        return;

    }
    current=first;
    if(current->next==NULL){//if the list contains one element
        delete current;
        first=NULL;
        count--;
    }
    else{
        current=first;//let current be the node to be deleted
        first=first->next;//now the head is the second node in th list
        first->prev=NULL;//head has no prev nodes so null
        delete current;
        count--;//decrement for the deleted node
    }
}
template <class type>
void doubleLinkedList<type>:: removeAtTail(){
    node<type> *current;
    current=new node<type>;
    if(first==NULL){
        cout<<"can't delete from an empty list"<<endl;
        return;

    }
    current=first;
    if(current->next==NULL){//if the list contains one element
        delete current;
        first=NULL;
        last=NULL;
        count--;
    }
    else{
        current=last;
        current->prev->next=NULL;
        last=current->prev;
        delete current;
        count--;

    }
}
template <class type>
void doubleLinkedList<type>:: removeAt(int index){
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
type doubleLinkedList<type>:: retrieveAt(int index) const{
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
       while(current->next!=NULL &&pos!=index){
        current=current->next;
        pos++;
        }
        if(pos==index){
            return current->info;
        }
    }
}
template<class type>
void doubleLinkedList<type>:: replaceAt(const type& newElement, int index){
    node<type> *current=first;
    int pos=0;
    if(index<0 || index>=count){
        cout<<"invalid position"<<endl;
        return;
    }
    else{
        while(current->next!=NULL &&pos!=index){
            current=current->next;
            pos++;
        }
        if(pos==index){
            current->info=newElement;
        }
    }
}
template<class type>
bool doubleLinkedList<type>:: isExist(const type& element){
    node<type> *current=first;
    while(current->next!=NULL){
        if(current->info==element){
            return true;
        }
        current=current->next;
    }
    return false;
}
template<class type>
bool doubleLinkedList<type>:: isItemAtEqual(const type& element, int index){
    if(index<0 || index>=count){
        cout<<"invalid position"<<endl;
        return false;
    }
    else{
        node<type> *current=first;
        int pos=0;
        while(current->next!=NULL && pos!=index){
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
void doubleLinkedList<type>:: swap(int firstItemIdx, int secondItemIdx){
    if(firstItemIdx<0 || firstItemIdx>=count ||secondItemIdx<0 || secondItemIdx>=count){
        cout<<"invalid position"<<endl;
        return;
    }
    node<type> *temp, *firstswap, *secondswap;
    temp=new node<type>;
    firstswap=first;
    int firstpos=0;
    bool firstfound=false;
    while(firstswap!=NULL && firstpos!=firstItemIdx ){
        firstswap=firstswap->next;
        firstpos++;
    }
    if(firstpos==firstItemIdx){
        firstfound=true;
    }
    secondswap=first;
    int secondpos=0;
    bool secondfound=false;

    while(secondswap!=NULL && secondpos!=secondItemIdx ){
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
void doubleLinkedList<type>::clear(){
    if(first==NULL){
        cout<<"the list is already empty"<<endl;
        return;
    }
    node<type> *current;
    while(first!=NULL){//if list not empty delete all nodes
        current=first;
        first=first->next;
        delete current;
    }
    last=NULL;
    count=0;
}
template <class type>
void doubleLinkedList<type>::print() const{
    if(first==NULL){
        cout<<"can't print an empty list"<<endl;
    }
    else{
        node<type> *current;
        current=first;
        while(current!=NULL){
            cout<<current->info<<" ";
            current=current->next;
        }
        cout<<endl;
    }
}
template <class type>
bool doubleLinkedList<type>::isEmpty(){
    return(first==NULL);
}
template <class type>
int doubleLinkedList<type>::doubleLinkedListSize() const{
    return count;
}

int main()
{
    doubleLinkedList<int> dl;
    dl.clear();
    dl.insertAtHead(1);
    dl.insertAtHead(2);
    dl.insertAtHead(3);
    dl.insertAtHead(4);
    dl.insertAtTail(5);
    dl.insertAt(20,2);
    dl.insertAtTail(200);
    dl.insertAt(100,4);
    dl.print();

    dl.removeAtHead();
    dl.print();

    dl.removeAtTail();
    dl.print();

    dl.removeAt(4);
    dl.print();

    cout<<"The given index contains the element= "<<dl.retrieveAt(4)<<endl;
    dl.replaceAt(33,4);
    dl.print();
    dl.swap(3,4);
    dl.print();

    cout<<"if exist 1, not exist 0: "<<dl.isExist(33)<<endl;
    cout<<"if Item At given index equal the item given 1, not exist 0: "<<dl.isItemAtEqual(5,3)<<endl;
    cout<<"if empty 1, not empty 0: "<<dl.isEmpty()<<endl;
    cout<<"The double linked list size= "<<dl.doubleLinkedListSize()<<endl;
    dl.clear();
    dl.print();
    return 0;
}

