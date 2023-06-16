#include <openacc.h>
#include <cuda.h>

#include <cstdlib>       /* srand, rand, atoi */
#include <time.h>        /* time */
#include <iostream>      /* cout */
#include <iomanip>       /* setprecision, setw */
#include <chrono>        /* high_resolution_clock */

void matmul_openacc_1gpu(const double *M1, const double *M2, double *MS, const int &N) {

    auto start = std::chrono::high_resolution_clock::now();

    #pragma acc parallel loop collapse(2) present(M1, M2, MS)
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {

            double sum = 0.0;
            #pragma acc loop reduction(+:sum)
            for (int k = 0; k < N; ++k)
                sum += M1[k + j * N] * M2[i + k * N];

            MS[i + j * N] = sum;

        }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << " matmul_openacc_1gpu time : " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() * 1e-6 << " s" << std::endl;

}

void matmul_CPU_serial(const double *M1, const double *M2, double *MS, const int &N) {

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            double *MS_ptr = MS + i + j * N;
            for (int k = 0; k < N; ++k)
                *MS_ptr += M1[k + j * N] * M2[i + k * N];
        }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << " matmul_CPU_serial time : " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() * 1e-6 << " s" << std::endl;

}

bool check_correctness(const double *Sol, const double *SolTrue, const int &N) {
    const int N2 = N * N;
    for (int i = 0; i < N2; ++i)
        if (Sol[i] != SolTrue[i])
            return false;
    return true;
}

void assign_random_values_to_matrix(double *M, const int &N, int seed = -1) {
    const int N2 = N * N;
    if(seed == -1)
        seed = time(NULL);
    srand(seed);
    for (int i = 0; i < N2; ++i)
        M[i] = rand() % 10;
}

void assign_fix_values_to_matrix(double *M, const int &N, const double val) {
    const int N2 = N * N;
    for (int i = 0; i < N2; ++i)
        M[i] = val;
}

void print_matrix(double *M, const int &N, const std::string s = "") {
    std::cout << ">>> matrix " << s << " :" << std::endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            std::cout << std::setw(8)<< M[i + j * N];
        std::cout << std::endl;
    }
}
