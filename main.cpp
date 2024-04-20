#include <bits/stdc++.h>
#include "sorting.h"
using namespace std;
class student{
private:
    string name;
    string id;
    double gpa;
public:
    student(string name,string id,double gpa);
    string getName();
    string getId();
    double getGpa() ;
    void setName(string&n);
    void setId ( string &i);
    void setGpa(double&g);
    bool operator<(student ob1);
    void print(){
        cout<<"name:"<<name<<" ,"<<"id:"<<id<<" ,"<<"gpa:"<<gpa<<endl;
    }
};
 student::student(string name,string id,double gpa):name(name),id(id),gpa(gpa){};
string student:: getName(){
    return name;
}
string student:: getId() {
    return id;
}
double student:: getGpa() {
    return gpa;
}
void student::setName(string&n){
    n =name;
}
void student:: setId( string &i){
    i=id;
}
void student:: setGpa(double&g){
    g=gpa;
}
bool student:: operator<(student ob1){
        return this->name < ob1.name;
 }
class Student{
private:
     vector<student>s;
 public:
     Student();
     void addStudnet(string n,string i,double g );
     void display();
     
 };
 Student::Student() {
             ifstream file("students.txt");
             string Name, Id;
             double Gpa;
             int NumStud;
             // Check if the file is opened successfully
             if (!file.is_open()) {
                  cerr << "Failed to open file." <<endl;
             }
             // Read the number of students
             if (!(file >> NumStud)) {
                  cerr << "Failed to read the number of students." << endl;
             }
             // Clear the newline character from the stream
              file.ignore();
             while (NumStud > 0) {
                 // Read student details
                 getline(file, Name);
                 getline(file, Id);
                 file >> Gpa;
                 file.ignore();
                 NumStud--;
                 addStudnet(Name,Id,Gpa);
             }
             file.close();

 }
void Student::addStudnet(string n,string i,double g ){
    s.emplace_back(n, i, g);
}
void  Student::display() {
     for(student x:s){
         x.print();
     }
 }
int main(){
    Student ob;
ob.display() ;
}

