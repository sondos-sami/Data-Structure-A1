#include "Student.h"
#include <iostream>
#include <vector>
#include <string>
void Student::insertionSort(vector<Student>& students) {
    int n = students.size();
    for (int i = 1; i < n; ++i) {
        Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].getName() > key.getName()) {
            students[j + 1] = students[j];
            j = j - 1;
        }
        students[j + 1] = key;
    }
}