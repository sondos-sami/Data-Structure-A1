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
    void item::SetName(const string &newName);
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

bool sortByPriceAscendingly(const item &i ,const item &i2){
    return i.getPrice() < i2.getPrice();
}
bool sortByPriceDescendingly(const item &i ,const item &i2){
    return i.getPrice() > i2.getPrice();
}
bool sortByCategoryAscendingly(const item &i ,const item &i2){
    return i.getCategory() < i2.getCategory();
}
bool sortByCategoryDescendingly(const item &i ,const item &i2){
    return i.getCategory() > i2.getCategory();
}
void item::print() const{
    cout<<"Item name: "<<name<<"  Item price: "<<price<<"  Item category: "<<category<<endl;
}
void readItems(const string &filename, vector<item> &items){
    ifstream file(filename);
    if(!file.is_open()){
        cout << "Error opening the file, please try again." << endl;
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
int main(){
    vector<item> items;
    readItems("try.txt",items);
    printVectorItems(items); 

}
