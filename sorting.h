#ifndef DATASTRUCTURE_SORTING_H
#define DATASTRUCTURE_SORTING_H

#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

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

#endif //DATASTRUCTURE_SORTING_H
