#include <iostream>
#include <cstdlib>
#include <cmath>
#include "/opt/homebrew/Cellar/libomp/18.1.8/include/omp.h"

using namespace std;

double generate() {
    return (double)rand() / RAND_MAX;
}

int check_shape() {
    double x = generate();
    double y = generate();
    return x * x + y * y <= 1;
}

int main() {
    long x[] = {10000};
    int num_threads = 8;

    omp_set_num_threads(num_threads);

    for (int i = 0; i < 1; ++i) {
        int total_points = x[i];
        int points_in_circle = 0;
        double t1 = omp_get_wtime();
        #pragma omp parallel reduction(+:points_in_circle)
        {
            unsigned int seed = omp_get_thread_num();
            srand(seed);

            int local_points_in_circle = 0;
            for (int j = 0; j < total_points / num_threads; ++j) {
                local_points_in_circle += check_shape();
            }
            points_in_circle += local_points_in_circle;
        }
        double t2 = omp_get_wtime();
        double pi_estimate = 4.0 * (double)points_in_circle / total_points;
        cout << "\nValue of Pi with " << total_points << " points is " << pi_estimate << " in time: " << double(t2-t1) << "\n";
    }
    return 0;
}