#include <openacc.h>
#include <cuda.h>

#include <cstdlib>       /* srand, rand, atoi */
#include <time.h>        /* time */
#include <iostream>      /* cout */
#include <iomanip>       /* setprecision, setw */
#include <chrono>        /* high_resolution_clock */

#define _USE_MATH_DEFINES
#include <cmath>         /* M_PI */

double montecarlo_pi(const size_t &N, int seed = -1) {

    auto start = std::chrono::high_resolution_clock::now();

    if(seed == -1)
        seed = time(NULL);
    srand(seed);

    size_t circle = 0;
    for (size_t i = 0; i < N; ++i){
        double x = double(rand()) / RAND_MAX;
        double y = double(rand()) / RAND_MAX;
        //printf("x,y = %f %f\n",x, y);
        if( x * x + y * y <= 1 )
            circle += 4;
    }

    double pi = double(circle) / double(N);

    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << " montecarlo_pi time : " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() * 1e-6 << " s" << std::endl;

    return pi;
}

double montecarlo_pi_1GPU(const size_t &N, int seed = -1) {

    auto start = std::chrono::high_resolution_clock::now();

    if(seed == -1)
        seed = time(NULL);
    srand(seed);

    int *circle = new int[N];
    #pragma acc enter data create(circle)

    #pragma acc loop firstprivate(N)
    for (size_t i = 0; i < N; ++i){
        double x = double(rand()) / RAND_MAX;
        double y = double(rand()) / RAND_MAX;
        if( x * x + y * y <= 1 )
            circle[i] = 4;
    }

	size_t c = 0;
	#pragma acc loop reduction(+:c)
	for (size_t i = 0; i < N; ++i){
            c += circle[i];
    }

	#pragma acc data copyout(c)
    double pi = double(c) / double(N);

    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << " montecarlo_pi_1GPU time : " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() * 1e-6 << " s" << std::endl;

    return pi;
}

void check_correctness(const double &Pi_m) {
    std::cout << "my PI = " << Pi_m << " versus real PI = " << M_PI << "   (relative error = " << (Pi_m-M_PI)/M_PI << ")" << std::endl;
}


