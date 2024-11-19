// Implement odd even transposition sort algorithm in serial and parallel and compare their execution times.

#include <iostream>
#include <vector>
#include "/opt/homebrew/Cellar/libomp/18.1.8/include/omp.h"

using namespace std;

void oddEvenSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    do {
        swapped = false;
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}


void oddEvenSortParallel(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    do {
        swapped = false;
        #pragma omp parallel for shared(arr) reduction(||:swapped)
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        #pragma omp parallel for shared(arr) reduction(||:swapped)
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();

    cout << "Unsorted array: \n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    double t1 = omp_get_wtime();
    oddEvenSort(arr);
    double t2 = omp_get_wtime();

    cout << "Sorted array: \n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Serial execution time: " << t2-t1 << " microseconds" << endl;

    arr = {12, 11, 13, 5, 6, 7};
    t1 = omp_get_wtime();
    oddEvenSortParallel(arr);
    t2 = omp_get_wtime();

    cout << "Sorted array: \n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Parallel execution time: " << t2-t1 << " microseconds" << endl;

    return 0;
}


