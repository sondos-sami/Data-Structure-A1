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
    float gpa;

    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < numStudents; ++i) {
        std::getline(file, name);
        file >> id >> gpa;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        students.emplace_back(name, id, gpa);
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
            T temp = data[i];
            int j;
            comparisons++;
            for (j = i; j >= gap && comp(temp, data[j - gap]); j -= gap) {
                data[j] = data[j - gap];
            }
            data[j] = temp;
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

template <typename T, typename Comparator>
void countSort(vector<T>& data, Comparator comp,int& comparisons){
    int n=data.size();
    vector<float> temp(n);
    for(int i=0;i<n;i++){
        temp[i]=data[i].gpa;
    }
    float mx = *max_element(temp.begin(), temp.end());
    float minn = *min_element(temp.begin(), temp.end());
    float range=mx-minn;
    int cnt_size = static_cast<int>(mx) + 1;
    vector<int> countvec(cnt_size,0);//empty array initialized by zero,, has the size range of elements of data
    for(int i=0;i<n;i++){
        countvec[static_cast<int>(temp[i] - minn)]++;//calculate the occurunces of each value in data and assign it to its index in count
    }
    for(int i=1;i<=cnt_size;i++){
        countvec[i]+=countvec[i-1];
    }
    vector<float> finalvec(n);
    for(int i=n-1;i>=0;i--){
        finalvec[countvec[static_cast<int>(temp[i]-minn)] - 1]=temp[i];
        countvec[static_cast<int>(temp[i]-minn)]--;
    }
    comparisons+=n;
    findStudentByGPA(data, finalvec, "SortedByGPA.txt",comparisons);

}
template <typename T>
void findStudentByGPA(vector<T>& data, vector<float>& finalvec, const string& filename , int& comparisons){
    ofstream outFile(filename, std::ios::app);
    if (!outFile) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }
    outFile << "Algorithm: CountSort" << endl;
    outFile << "Number of comparisons: " << comparisons << endl;
    for(int i=0; i<finalvec.size();i++){
        for(const auto& student:data){
            if(student.gpa==finalvec[i]){
                outFile<< student.name << endl;
                outFile<< student.id << endl;
                outFile<< student.gpa << endl;
                break;
            }
        }
    }
    outFile.close();

}

int main(){
    int comparisons,n;
    long long duration;
    vector<student> Student;
    readStudentsFromFile("students.txt",Student);
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
//Count
    countSort(Student,compareByGPA,comparisons);



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
    print(Student,"SortedByName.txt", "Bubblesort", comparisons, duration);

//shellsort
    start = high_resolution_clock::now();
    ShellSort(Student, compareByName , comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start).count();
    print(Student, "SortedByName.txt", "ShellSort", comparisons, duration);




}
