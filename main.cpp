   #include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
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
void readStudentsFromFile(const std::string& filename, std::vector<student>& students) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
        return;
    }

    int numStudents;
    file >> numStudents;
    students.reserve(numStudents); // Reserve space for efficiency

    std::string name;
    string id;
    double gpa;

    // Skip the end of line character after reading numStudents
    file.ignore( );

    for (int i = 0; i < numStudents; ++i) {
        std::getline(file, name);
        file >> id >> gpa;
        // Skip the end of line character after reading gpa
        file.ignore();
        students.emplace_back(name, id, gpa);
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
    readStudentsFromFile("students.txt", Student);
   SelectionSort(Student, compareByName);
    cout << "After Bubble Sort by Name:" << endl;
    print(Student);
}

