#ifndef DATASTRUCTURE_SORTING_H
#define DATASTRUCTURE_SORTING_H
 #include <vector>
using namespace std;
template <typename T, typename Comparator>
void InsertionSort(vector<T>& data, Comparator comp) {
    int n = data.size();
    for (int i = 1; i < n; i++) {
        for (int j=0;j<i;j++){
            if(comp(data[i],data[j]))
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
 

#endif //DATASTRUCTURE_SORTING_H
