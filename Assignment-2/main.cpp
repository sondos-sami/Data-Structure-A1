#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class item{
private:
    int price;
    string name;
    string category;

public:
    item(int p,string n,string c);
    string getName() const;
    int getPrice() const;
    string getCategory() const;
    void SetName(const string &newName);
    void SetCategory(const string &newCategory);
    void SetPrice(const int &newPrice);
    bool operator<(const item &i) const;
    void print() const;
};

item::item(int p,string n,string c): price(p) , name(n), category(c){}

string item::getName() const{
    return name;
}
string item::getCategory() const{
    return category;
}
int item::getPrice() const{
    return price;
}
void item::SetName(const string &newName) {
    name=newName;
}
void item::SetCategory(const string &newCategory) {
    category=newCategory;
}
void item::SetPrice(const int &newPrice) {
    price=newPrice;
}
bool item::operator<(const item &i) const{
    return this->name < i.name;
}

bool compareByName(const item& i1, const item& i2) {
    return i1.getName() < i2.getName();
}

bool compareByCategory(const item& i1, const item& i2) {
    return i1.getCategory() < i2.getCategory();
}

bool compareByPrice(const item& i1, const item& i2) {
    return i1.getPrice() < i2.getPrice();
}
void item::print() const{
    cout<<"Item name: "<<name<<"  Item price: "<<price<<"  Item category: "<<category<<endl;
}
void readItems(const string &filename, vector<item> &items){
    ifstream file(filename);
    if(!file.is_open()){
        cout<<"Error opening the file, please try again."<<endl;
        return;
    }
    string line;
    int price;
    string name, category;
    while (file >> price) {
        file.ignore();
        getline(file, name);
        getline(file, category);
        items.emplace_back(price, name, category);
    }
    file.close();
}

void printVectorItems(const vector<item>& items) {
    for (const auto& item : items) {
        item.print();
    }
}


class Heap{
public:
    void Minheapify(vector<item>& items, int i, int n, bool (*comp)(const item&, const item&));
    void Maxheapify(vector<item>& items, int i, int n, bool (*comp)(const item&, const item&));
    void buildHeap(vector<item>& items, int n, bool (*comp)(const item&, const item&), bool ascending);
    void heapSort(vector<item>& items, int n, bool (*comp)(const item&, const item&), bool ascending);
    void insertNodeToHeap(vector<item>& items, int n,const item& newnode ,bool (*comp)(const item&, const item&),bool ascending);
    void deleteNodeFromHeap(vector<item>& items, int n,int idx,bool (*comp)(const item&, const item&),bool ascending);
};

void Heap::Minheapify(vector<item>& items, int i, int n, bool (*comp)(const item&, const item&)){
    item tmp=items[i];
    int smallIndex=i*2+1;
    while(smallIndex<=n){
        if(smallIndex<n){
            if(comp(items[smallIndex] , items[smallIndex+1])){
                smallIndex+=1;
            }
        }
        if(!comp(tmp , items[smallIndex])){
            break;
        }
        else{
            items[i]=items[smallIndex];
            i=smallIndex;
            smallIndex=2*i+1;
        }
    }
    items[i]=tmp;
}
void Heap::Maxheapify(vector<item>& items, int i, int n, bool (*comp)(const item&, const item&)){

    item tmp=items[i];
    int largeIndex=i*2+1;
    while(largeIndex<=n){
        if(largeIndex<n){
            if(!comp(items[largeIndex] , items[largeIndex+1])){
                largeIndex+=1;
            }
        }
        if(comp(tmp , items[largeIndex])){
            break;
        }
        else{
            items[i]=items[largeIndex];
            i=largeIndex;
            largeIndex=2*i+1;
        }
    }
    items[i]=tmp;
}

void Heap::buildHeap(vector<item>& items, int n, bool (*comp)(const item&, const item&), bool ascending){
    for(int index=n/2 -1; index>=0; index--){
        if(ascending){
            Minheapify(items,index, n-1,comp);
        }
        else{
            Maxheapify(items,index, n-1,comp);
        }
    }
}
void Heap::heapSort(vector<item>& items, int n, bool (*comp)(const item&, const item&), bool ascending){
    if(ascending){
        bool minHeap=true;
        buildHeap(items,n,comp,minHeap);
        for(int i=n-1;i>=0;i--){
            item tmp=items[i];
            items[i]=items[0];
            items[0]=tmp;
            if(ascending){
                Minheapify(items,0,i-1,comp);
            }else{
                Maxheapify(items,0,i-1,comp);
            }
        }
    }
    else{
        bool minHeap=false;
        buildHeap(items,n,comp,minHeap);
        for(int i=n-1;i>=0;i--){
            item tmp=items[0];
            items[0]=items[i];
            items[i]=tmp;
            Maxheapify(items,0,i-1,comp);
        }
    }
}
void Heap::insertNodeToHeap(vector<item>& items, int n,const item& newnode ,bool (*comp)(const item&, const item&),bool ascending){
    n+=1;
    items[n-1]=newnode;
    heapSort(items,n,comp,ascending);
}
void Heap::deleteNodeFromHeap(vector<item>& items, int n,int idx,bool (*comp)(const item&, const item&),bool ascending){
    if(idx>=n){
        cout<<"out of range, please enter another index"<<endl;
        return;
    }
    items[idx] = items.back();
    items.pop_back();
    n=items.size();
    heapSort(items,n,comp,ascending);
}
int main() {
    vector<item> items;
    readItems("try.txt",items);
    int choice=-1,input;
    bool ascending=true;
    Heap heap;
    while(choice!=0){
        cout << "Please enter what you would like to choose:\n"
         <<"1 - Print items before sorting\n"
         <<"2 - Sort items by name\n"
         <<"3 - Sort items by price\n"
         <<"4 - Sort items by category\n"
         <<"5 - Insert a new item\n"
         <<"6 - Delete an item\n"
         <<"0 - Exit\n";

    cin>>choice;
    switch (choice) {
        case 1:
            cout<<"Before sorting:\n";
              printVectorItems(items);
            cout<<endl;
            break;
        case 2:{
            cout<<"please enter if you want sorting ascending(1) or descending(2)\n";
            cin>>input;
            if(input==1){
                ascending=true;
            }else{
                ascending=false;
            }
            heap.heapSort(items, items.size(),compareByName,ascending);
            cout<<"Sorted by name:\n";
             printVectorItems(items);
            cout<<endl;
            break;
        }
        case 3:{
            cout<<"please enter if you want sorting ascending(1) or descending(2)\n";
            cin>>input;
            if(input==1){
                ascending=true;
            }else{
                ascending=false;
            }
            heap.heapSort(items, items.size(),compareByPrice,ascending);
            cout<<"Sorted by price:\n";
              printVectorItems(items);
            cout<<endl;
            break;
        }
        case 4:{
            cout<<"please enter if you want sorting ascending(1) or descending(2)\n";
            cin>>input;
            if(input==1){
                ascending=true;
            }else{
                ascending=false;
            }
            heap.heapSort(items, items.size(),compareByCategory,ascending);
            cout<<"Sorted by category:\n";
              printVectorItems(items);
            cout<<endl;
            break;
        }
        case 5:{
            cout<<"please enter the item contents you want to insert in order of price, name, category: \n";
            int price;
            string category, name;
            cin>>price>>name>>category;
            item i={price,name,category};
            cout<<"please enter if you want sorting ascending(1) or descending(2)\n";
            cin>>input;
            if(input==1){
                ascending=true;
            }else{
                ascending=false;
            }
            heap.insertNodeToHeap(items,items.size(),i ,compareByPrice,ascending);
            cout<<"Sorted by price after inserting a new node:\n";
              printVectorItems(items);
            cout<<"items size after insertion:"<<items.size()<<endl;
            break;
        }
        case 6:{
            int index;
            cout<<"please enter the index of the item you want to delete: \n";
            cin>>index;
            cout<<"please enter if you want sorting ascending(1) or descending(2)\n";
            cin>>input;
            if(input==1){
                ascending=true;
            }else{
                ascending=false;
            }
            heap.deleteNodeFromHeap(items,items.size(),index,compareByPrice,ascending);
             printVectorItems(items);
            cout<<"items size after deletion:"<<items.size()<<endl;
            break;
        }
        case 0:
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
            break;
    }
    }
}

