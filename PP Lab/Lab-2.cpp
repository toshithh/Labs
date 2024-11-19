#include <iostream>
#include <cstdlib>
#include "/opt/homebrew/Cellar/libomp/18.1.8/include/omp.h"
using namespace std;


double generate(){
    //return double(drand48());
    double x = (double)rand()/RAND_MAX;
    return (x);
}

int check_shape(){
    double x = generate();
    double y = generate();
    return x * x + y * y <= 1;
}

int main(){
   int x[] = {10, 100, 1000, 10000};
    int i = 0;
    while (i < 4) {
        double t1 = omp_get_wtime();
        int total_points = x[i] * x[i];
        int points_in_circle = 0;
        for (int j = 0; j < total_points; ++j) {
            points_in_circle += check_shape();
        }
        double t2 = omp_get_wtime();
        double pi_estimate = 4.0 * (double)points_in_circle / total_points;
        cout << "\nValue of Pi with " << total_points << " points is " << pi_estimate << " in time: " << double(t2-t1) << "\n";
        i++;
    }
    return 0;
}