 #include <iostream>
#include <string>
#include <vector>
using namespace std;
template <typename T, typename Comparator>
void InsertionSort(vector<T>& data, Comparator comp) {
    int n = data.size();
    for (int i = 1; i < n; i++) {
        for (int j=0;j<n&& comp(data[i], data[j]);j++){
            swap(data[i],data[j]);
        }

    }
}

template <typename T, typename Comparator>
void SelectionSort(vector<T>& data, Comparator comp) {
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (comp(data[j], data[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(data[i], data[minIndex]);
        }
    }
}


// Function Bubble Sort
template <typename T, typename Comparator>
void BubbleSort(vector<T>& data, Comparator comp) {
    bool f;
    int n = data.size();
    for (int i = 0; i < n - 1; ++i) {
        f = false;
        for (int j = n - 1; j > i; j--) {
            if (comp(data[j], data[j - 1])) //based on the comparator byName or byGPA and < or >
            {
                swap(data[j], data[j - 1]);
                f = true;
            }
        }
        if (!f)//to achieve best case o(n)
            return;
    }
}

