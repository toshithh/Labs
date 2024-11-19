//Write a parallel program to implement quick sort algorithm
#include <iostream>
using namespace std;


void print(int arr[], int l){
    for (int i = 0; i < l  ; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int partition(int arr[], int l, int h){
    int i = l;
    int piv = arr[h];
    for (int j = l; j < h+1; j++){
        if (arr[j] < piv){
            int t = arr[j];
            arr[j] = arr[i];
            arr[i] = t;
            i++;
        }
    }
    arr[h] = arr[i];
    arr[i] = piv;
    return i;
}


void quickSort(int x[], int l, int n){
    if (l < n){
        int p = partition(x, l, n);
        quickSort(x, l, p-1);
        quickSort(x, p, n);
    }
}


int main(){
    int x[] = {1, 4, 5, 8, 2, 3};
    quickSort(x, 0, sizeof(x)/sizeof(int) - 1);
    print(x, sizeof(x)/4);
    return 1;
}