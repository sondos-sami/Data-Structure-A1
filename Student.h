#include <iostream>
#include <vector>
#include <string>

#ifndef PART1_STUDENT_H
#define PART1_STUDENT_H

using namespace std;

class Student {
private:
    string name;
    string id;
    double gpa;

public:
    // Constructor
    Student(string name, string id, double gpa) : name(name), id(id), gpa(gpa) {}

    // Getters
    string getName() const { return name; }
    string getId() const { return id; }
    double getGpa() const { return gpa; }

    // Setters
    void setName(const string& name) { this->name = name; }
    void setId(const string& id) { this->id = id; }
    void setGpa(double gpa) { this->gpa = gpa; }

    // Overloading the '<' operator to compare Student objects by name
    bool operator<(const Student& other) const {
        return name < other.name;
    }

    // Overloading the '<<' operator to print Student object
    friend ostream& operator<<(ostream& os, const Student& student) {
        os << "Name: " << student.name << ", ID: " << student.id << ", GPA: " << student.gpa;
        return os;
    }

    // Sorting Methods
    void insertionSort(vector<Student>& students);
    void mergeSort(vector<Student>& students, int left, int right);
    void selectionSort(vector<Student>& students);
    void quickSort(vector<Student>& students, int low, int high);
    void BubbleSort(vector<Student>& students);
     void ShellSort(vector<Student>& students);

private:
    // Utility functions for sorting algorithms
    void merge(vector<Student>& students, int left, int mid, int right);
    int partition(vector<Student>& students, int low, int high);
};

#endif //PART1_STUDENT_H
