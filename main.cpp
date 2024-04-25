#include <bits/stdc++.h>

#include "sorting.h"
using namespace std;
using namespace chrono;
class student {
public:
    string name;
    string id;
    double gpa;

    student(string name, string id, double gpa);
    string getName();
    string getId();
    double getGpa();
    void setName(const string& n);
    void setId(const string& i);
    void setGpa(double g);
    bool operator<(const student& ob1);
};

student::student(string name, string id, double gpa) : name(name), id(id), gpa(gpa) {}

string student::getName() {
    return name;
}

string student::getId() {
    return id;
}

double student::getGpa() {
    return gpa;
}

void student::setName(const string& n) {
    name = n;
}

void student::setId(const string& i) {
    id = i;
}

void student::setGpa(double g) {
    gpa = g;
}

bool student::operator<(const student& ob1) {
    return this->name < ob1.name;
}

bool compareByName(const student& a, const student& b) {
    return a.name < b.name;
}

bool compareByGPA(const student& a, const student& b) {
    return a.gpa < b.gpa;
}

void readStudentsFromFile(vector<student>& students) {
    ifstream file("students.txt");
    string Name, Id;
    double Gpa;
    int NumStud;

    if (!file.is_open()) {
        cout<< "Failed to open file." << endl;
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

void print(vector<student>& students, string filename, string algorithmName, int comparisons, long long duration) {
    ofstream outFile(filename, ios::app);

    if (!outFile.is_open()) {
        cerr << "Failed to open output file." << endl;
        return;
    }

    outFile << "Algorithm: " << algorithmName << endl;
    outFile << "Number of comparisons: " << comparisons << endl;
    outFile << "Running time: " << duration << " microseconds" << endl;

    for (const auto& student : students) {
        outFile << student.name << endl;
        outFile << student.id << endl;
        outFile << student.gpa << endl;
    }

    outFile.close();
}


int main(){
      int comparisons;
    long long duration;
    vector<student> Student;
    readStudentsFromFile(Student);
    remove("SortedByGPA.txt");//to clear file
    remove("SortedByName.txt");
     //sorting by GPA

   auto start = high_resolution_clock::now();
    InsertionSort(Student, compareByGPA, comparisons);
    auto stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    print(Student, "SortedByGPA.txt", "InsertionSort", comparisons, duration);

    start = high_resolution_clock::now();
    SelectionSort(Student, compareByGPA, comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    print(Student, "SortedByGPA.txt", "SelectionSort", comparisons, duration);
    
   start = high_resolution_clock::now();
    QuickSort(Student, compareByGPA, comparisons);
     stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
print(Student, "SortedByGPA.txt", "QuickSort", comparisons, duration);

//    MergeSort(Student, compareByGPA);
//    print(Student, "SortedByGPA.txt", "MergeSort");






    //sorting by Name

    auto start = high_resolution_clock::now();
    InsertionSort(Student, compareByName, comparisons);
    auto stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    print(Student, "SortedByName.txt", "InsertionSort", comparisons, duration);

    start = high_resolution_clock::now();
    SelectionSort(Student, compareByName, comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    print(Student, "SortedByName.txt", "SelectionSort", comparisons, duration);
    
   start = high_resolution_clock::now();
    QuickSort(Student,compareByName, comparisons);
     stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
print(Student, "SortedByName.txt"", "QuickSort", comparisons, duration);

    
//    BubbleSort(Student, compareByName);
//    print(Student, "SortedByName.txt", "BubbleSort");


}

