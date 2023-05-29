#include <cstdlib>       /* srand, rand, atoi */
#include <time.h>        /* time */
#include <iostream>      /* cout */
#include <iomanip>       /* setprecision, setw */

void matmul_CPU_serial(const double *M1, const double *M2, double *MS, const int &N) {

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            double *MS_ptr = MS + i + j * N;
            for (int k = 0; k < N; ++k)
                *MS_ptr += M1[k + j * N] * M2[i + k * N];
        }

}

bool check_correctness(const double *Sol, const double *SolTrue, const int &N) {
    const int N2 = N * N;
    for (int i = 0; i < N2; ++i)
        if (Sol[i] != SolTrue[i])
            return false;
    return true;
}

void assign_random_values_to_matrix(double *M, const int &N) {
    const int N2 = N * N;
    srand(time(NULL));
    for (int i = 0; i < N2; ++i)
        M[i] = rand() % 10;
}

void assign_fix_values_to_matrix(double *M, const int &N, const double val) {
    const int N2 = N * N;
    for (int i = 0; i < N2; ++i)
        M[i] = val;
}

void print_matrix(double *M, const int &N, const std::string s = "") {
    std::cout << ">>> matrix " << s << " :" << setprecision(1) << setw(8) << std::endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            std::cout << M[i + j * N];
        std::cout << std::endl
    }
}
