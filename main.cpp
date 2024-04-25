#include <bits/stdc++.h>
#include <vector>
#include <chrono>

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
    outFile << "Running time: " << duration << " nanoseconds" << endl;

    for (const auto& student : students) {
        outFile << student.name << endl;
        outFile << student.id << endl;
        outFile << student.gpa << endl;
    }

    outFile.close();
}


template <typename T, typename Comparator>
void InsertionSort(vector<T>& data, Comparator comp, int& comparisons) {
    comparisons = 0;
    int n = data.size();
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            comparisons++;
            if (comp(data[i], data[j]))
                swap(data[i], data[j]);
        }
    }
}

template <typename T, typename Comparator>
void SelectionSort(vector<T>& data, Comparator comp, int& comparisons) {
    comparisons = 0;
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (comp(data[j], data[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(data[i], data[minIndex]);
        }
    }
}

template <typename T, typename Comparator>
void ShellSort(vector<T>& data, Comparator comp, int& comparisons) {
    comparisons = 0;
    int n = data.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            for (int j = i; j >= gap && comp(data[j], data[j - gap]); j -= gap) {
                comparisons++;
                swap(data[j], data[j - gap]);
            }
        }
    }
}

template <typename T, typename Comparator>
void BubbleSort(vector<T>& data, Comparator comp, int& comparisons) {
    comparisons = 0;
    bool f;
    int n = data.size();
    for (int i = 0; i < n - 1; ++i) {
        f = false;
        for (int j = n - 1; j > i; j--) {
            comparisons++;
            if (comp(data[j], data[j - 1])) {
                swap(data[j], data[j - 1]);
                f = true;
            }
        }
        if (!f) // to achieve best case O(n)
            return;
    }
}
template <typename T, typename Comparator>
void QuickSort(vector<T>& data, Comparator comp, int& comparisons) {
    int n = data.size();
    if (n <= 1) {
        return;
    }

    T pivot = data[n/2];

    vector<T> left;
    vector<T> right;

    for (int i = 0; i < n; i++) {
        if (i == n/2) {
            continue;
        }

        comparisons++;  // Increment comparison counter

        if (comp(data[i], pivot)) {
            left.push_back(data[i]);
        } else {
            right.push_back(data[i]);
        }
    }

    QuickSort(left, comp, comparisons);
    QuickSort(right, comp, comparisons);

    int index = 0;

    for (const T& val : left) {
        data[index++] = val;
    }

    data[index++] = pivot;

    for (const T& val : right) {
        data[index++] = val;
    }
}
template <typename T, typename Comparator>
void merge(vector<T>& data, int l, int m, int r, Comparator comp, int& comparisons) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<T> L;
    vector<T> R;
    for (i = 0; i < n1; i++) {
        L.push_back(data[l + i]);
    }
    for (j = 0; j < n2; j++) {
        R.push_back(data[m + 1 + j]);
    }
    i = j = 0;
    k = l;
    while (i < n1 && j < n2) {
        comparisons++;
        if (comp(L[i], R[j])) {
            data[k] = L[i];
            i++;
        } else {
            data[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }
}

template <typename T, typename Comparator>
void mergesort(vector<T>& data, int start, int end, Comparator comp, int& comparisons) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergesort(data, start, mid, comp, comparisons);
        mergesort(data, mid + 1, end, comp, comparisons);
        merge(data, start, mid, end, comp, comparisons);
    }
    return;
}


int main(){
      int comparisons,n;
    long long duration;
    vector<student> Student;
    readStudentsFromFile(Student);
    remove("SortedByGPA.txt");//to clear file
    remove("SortedByName.txt");
     //sorting by GPA
//insertion
   auto start = high_resolution_clock::now();
    InsertionSort(Student, compareByGPA, comparisons);
    auto stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student, "SortedByGPA.txt", "InsertionSort", comparisons, duration);
//selection
    start = high_resolution_clock::now();
    SelectionSort(Student, compareByGPA, comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student, "SortedByGPA.txt", "SelectionSort", comparisons, duration);
//quicksort
   start = high_resolution_clock::now();
    QuickSort(Student, compareByGPA, comparisons);
     stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
print(Student, "SortedByGPA.txt", "QuickSort", comparisons, duration);
    //mergesort
    start = high_resolution_clock::now();
    mergesort(Student,0,n-1, compareByGPA , comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student, "SortedByGPA.txt", "Mergesort", comparisons, duration);

//Bubblesort
    start = high_resolution_clock::now();
    BubbleSort(Student,compareByGPA , comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student, "SortedByGPA.txt", "Bubblesort", comparisons, duration);
//shell
    start = high_resolution_clock::now();
    ShellSort(Student, compareByGPA , comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student, "SortedByGPA.txt", "ShellSort", comparisons, duration);





    //sorting by Name
//insertion
    start = high_resolution_clock::now();
    InsertionSort(Student, compareByName, comparisons);
     stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student, "SortedByName.txt", "InsertionSort", comparisons, duration);
//selection
    start = high_resolution_clock::now();
    SelectionSort(Student, compareByName, comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student, "SortedByName.txt", "SelectionSort", comparisons, duration);
//quicksort
    start = high_resolution_clock::now();
    QuickSort(Student, compareByName, comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student, "SortedByName.txt", "QuickSort", comparisons, duration);
    //mergesort
    start = high_resolution_clock::now();
    mergesort(Student,0,n-1,compareByName , comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student, "SortedByName.txt", "Mergesort", comparisons, duration);
    //Bubblesort
    start = high_resolution_clock::now();
    BubbleSort(Student, compareByName , comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student,"SortedByName .txt", "Bubblesort", comparisons, duration);

//shellsort
    start = high_resolution_clock::now();
    ShellSort(Student, compareByName , comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student, "SortedByName.txt", "ShellSort", comparisons, duration);




}
