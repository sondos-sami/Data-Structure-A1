#include <iostream>
using namespace std;
const int  MAX_SIZE=100;
template<class t>
class stack{
private:
    int top;
    t items[MAX_SIZE];

public:
    stack(){
        top=-1;
    }
    bool isEmpty(){
        if(top==-1)
            return true;
        else
            return false;
    }
    void push(t element){
        if(top>=MAX_SIZE-1)
            cout<<"stack is full";
        else{
            top++;
            items[top]=element;
        }}

    void pop(){
        if(isEmpty()){
            cout<<"stack is empty";
        }
        else{
            top--;
        }}

    void pop(t &element){
        if(isEmpty()){
            cout<<"stack is empty";
        }
        else{
            element=items[top];
            top--;
        }}
    void get_top(t &top_element){
        if(isEmpty()){
            cout<<"stack is empty "<<endl;
        }
        top_element= items[top];
        cout<<top_element;
    }
    int size(){
        return top+1;
    }
    void print(){
        cout<<'[';
        for(int i=top;i>=0;--i){
            cout<<items[i]<<' ';
        }
        cout<<']';
    }
};

int main() {
    stack <string>s;

    s.push("mariam");
    s.push("marwan");
    s.push("sama");
    s.push("sondos");
    s.pop();
    s.push("rasha");
    s.push("hussein");
    s.push("ahmed");
    s.push("mohamed");
    s.print();
    cout<<endl;
    string y;
    s.get_top(y);
    cout<<endl;
    cout<<s.size();
    return 0;
}
