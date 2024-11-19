// WAP to illustrate the use of first private clause.
// WAP to illustrate the use of last private clause.
// Consider an array of 10,000 elements all initialized to number 1. Find the sum of the array element using 8 threads which share the responsibility equally among them. Use critical directive in your program.
#include <iostream>
#include "/opt/homebrew/Cellar/libomp/18.1.8/include/omp.h"
using namespace std;


void first_priv(){
    int x = 100;
    #pragma omp parallel firstprivate(x) num_threads(1)
    {
        x*=100;
        cout << "Private Thread " << omp_get_thread_num() << ": " << x << endl;
    };
    cout << "Main Thread " << omp_get_thread_num() << ": " << x << endl;
}


void last_priv(){
    long x = 10;
    cout << "Orig Val: " << x << endl;
    #pragma omp parallel for lastprivate(x)
    for (int i = 0; i < 8; i++){
        x*10;
        cout << "T" << omp_get_thread_num() << ": " << x << endl;
    };
    cout << "Main Thread " << omp_get_thread_num() << ": " << x << endl;
}

void arr_sum(){
    int x[1000];
    for (int i=0; i<1000; i++){
        x[i] = 1;
    }

    int sum = 0;
    #pragma omp parallel reduction(+:sum) num_threads(8)
    {
        int local = 0;
        for (int i=omp_get_thread_num()*1000/8; i < (1+omp_get_thread_num())*1000/8; i++){
            local += x[i];
        }
        sum += local;
    }

    cout << sum;
}

int main(){
    cout << "FirstPrivate\n" << endl;
    first_priv();
    cout << "\n\nLastPrivate\n" << endl;
    last_priv();
    cout << "\n\nArray Sum\n" << endl;
    arr_sum();
    return 1;
}