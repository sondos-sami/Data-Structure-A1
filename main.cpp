#include <bits/stdc++.h>
using namespace std;
class student{
private:
    string name;
    string id;
    double gpa;
public:
    student(string&name,string&id,double&gpa):name(name),id(id),gpa(gpa){
    }
    string getName(){
        return name;
    }
    string getId() {
        return id;
    }
    double getGpa() {
        return gpa;
    }
    void setName(string&n){
        n =name;
    }
    void setId(string &i){
        i=id;
    }
    void setGpa(double&g){
        g=gpa;
    }
};
int main() {

}
