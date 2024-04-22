#include <iostream>
#include <string>
using namespace std;
template<class t>
class linkedQueue{
private:
    struct node{
        t item;
        node*next;
    };
    node*front,*back;
    int length;
public:
    linkedQueue(){
        front=back=NULL;
        length=0;
    }
    bool IsEmpty(){
        return length==0;
    }
    int QueueSize(){
        return length;
    }
    void Enqueue( t element){
        node*newnode=new node;
        newnode->item=element;
        newnode->next=NULL;
        if (length==0){
          front=back=newnode;
        }
        else{
            back->next=newnode;
            back=newnode;
        }
        length++;
    }
    t Dequeue(){
       if(IsEmpty()){cout<<"Cannot dequeue from an empty queue.";}
       if(length==1){
           t last =front->item;
          delete front;
           back=NULL;
           length=0;
           return last;
       }
       else{
           node*temp=front;
           t last =front->item;
           front=front->next;
           delete temp;
            length--;
           return last;
       }
    }
    t first(){
        if(!IsEmpty()){
        return front->item;}
    }
    void clear(){
        if (IsEmpty()) { cout<<"Queue is already empty.";}
        else{
        node*current = new node;
        while(front!=NULL){
            current=front;
            front=front->next;
            delete current;
        }
        back=NULL;
        length=0;
    }}
    void print(){
        if (IsEmpty()) { cout<<"Queue is empty,Nothing to display";}
        node*current=front;
        while(front!=NULL){
            cout<<current->item<<" ";
            current = current->next;
        }
    }
};

int main() {
    linkedQueue<int> q1;
    q1.Enqueue(20);
    q1.Enqueue(20);
    q1.Enqueue(20);
    q1.Enqueue(20);
    q1.Enqueue(20);
    q1.Enqueue(20);

    q1.print();

}
