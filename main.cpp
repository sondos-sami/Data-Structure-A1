#include <bits/stdc++.h>
#include "sorting.h"

using namespace std;
class student {
public:
    string name;
    string id;
    double gpa;
    student(string name,string id,double gpa);
    string getName();
    string getId();
    double getGpa() ;
    void setName(string&n);
    void setId ( string &i);
    void setGpa(double&g);
    bool operator<(student ob1);

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

bool compareByName(const student& a, const student& b) {
    return a.name < b.name;
}
bool compareByGPA(const student& a, const student& b) {
    return a.gpa < b.gpa;
}
void readStudentsFromFile( vector<student>& students) {
    ifstream file("students.txt");
    string Name, Id;
    double Gpa;
    int NumStud;
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
    }
    if (!(file >> NumStud)) {
        cerr << "Failed to read the number of students." << endl;
    }
    file.ignore();
    while (NumStud > 0) {
        getline(file, Name);
        getline(file, Id);
        file >> Gpa;
        file.ignore();
        NumStud--;
       students.emplace_back(Name, Id, Gpa);
    }
    file.close();
}
void print(const vector<student>& students) {
    for (const auto& student : students) {
        cout << "Name: " << student.name << ", ID: " << student.id << ", GPA: " << student.gpa << endl;
    }
}
int main(){
    vector<student>Student;
    readStudentsFromFile( Student);
    MergeSort(Student, compareByName);
    cout << "After Sorting:" << endl;
    print(Student);
}

