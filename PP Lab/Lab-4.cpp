// Implement Parallel Merge sort algorithm using open mp and compare its execution time with serial Merge sort.

#include <iostream>
#include <vector>
#include "/opt/homebrew/Cellar/libomp/18.1.8/include/omp.h"
using namespace std;

void merge(vector<int>& arr, int left, 
                     int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeP(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    #pragma omp parallel for
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    #pragma omp parallel for
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            while (i < n1 && j < n2) {
                if (L[i] <= R[j]) {
                    arr[k] = L[i];
                    i++;
                } else {
                    arr[k] = R[j];
                    j++;
                }
                k++;
            }
        }
        #pragma omp section
        {
            while (i < n1) {
                arr[k] = L[i];
                i++;
                k++;
            }
        }
        #pragma omp section
        {
            while (j < n2) {
                arr[k] = R[j];
                j++;
                k++;
            }
        }
    }
}


void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSortP(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSortP(arr, left, mid);
    mergeSortP(arr, mid + 1, right);
    mergeP(arr, left, mid, right);
}

void printVector(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    vector<int> arr = { 12, 11, 13, 5, 6, 7 };
    int n = arr.size();

    cout << "Array \n";
    printVector(arr);

    double t1 = omp_get_wtime();
    mergeSort(arr, 0, n - 1);
    double t2 = omp_get_wtime();

    cout << "\nSorted array sequential \n";
    printVector(arr);

    cout << "Time taken: " << t2-t1 << endl;

    t1 = omp_get_wtime();
    mergeSortP(arr, 0, n - 1);
    t2 = omp_get_wtime();

    cout << "\nSorted array Parallel \n";
    printVector(arr);

    cout << "Time taken: " << t2-t1;

    return 0;
}


