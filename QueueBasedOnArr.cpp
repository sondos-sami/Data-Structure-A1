#include <iostream>
#include <string>
using namespace std;
template<class t>
//******circular queue based on array
class QueueBasedArray{
private:
    int front;
    int back;
    int length;//counter in array
    t*arr;
    int maxsize;
public:
    QueueBasedArray( int size){
        // front and back indexes
        arr=new t[size];
        front=0;
        maxsize=size;
        back=size-1;
        length=0;
    }
    bool IsEmpty(){
        return length==0;
    }
    bool IsFull(){
        return length==maxsize;
    }
    int QueueSize(){
        return length;
    }
    void Enqueue( t element){
     if(IsFull()){
    cout<<"Can't add element. Queue is full.";
}
     else{
         back=(back+1)%maxsize;
         arr[back]=element;
         length++;
         }
     }
    t Dequeue(){
        if(IsEmpty()){
            cout<<"Can't delete element. Queue is empty";
        }
        else{
            t frontElement = arr[front];
            front = (front + 1) % maxsize;
            length--;
            return frontElement;
        }
    }
    t firstelement(){
        if(IsEmpty()){ cout<<"Can't get First element";}
        else {
        return arr[front];}
    }
    void print(){
        if(!IsEmpty()){
            for (int i = front; i !=back+1 ; i=(i+1)%maxsize) {
                cout << arr[i] << " "; // Add a space here
            }
        } else {
            cout << "Queue Is Empty";
        }
    }

   void clear(){// cleared queue but still
        if(IsEmpty()){cout<<"Unable To CLear it";}
        else{
            front = 0;
            back = maxsize - 1;
            length= 0;
//            cout << "Queue cleared ";
    }}
    };



int main() {
    QueueBasedArray<int> q1(5);
    q1.Enqueue(20);
    q1.Enqueue(5);
    q1.Enqueue(27);
    q1.Enqueue(29);

   cout<< q1.firstelement();




}
