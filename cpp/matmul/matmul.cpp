#include "matmul.h"

int main( int argc, char  **argv){

    int N = std::atoi(argv[1]);

    std::cout << " Matrix moltiplication " << std::endl;
    std::cout << " OpenACC - C++ " << std::endl;
    std::cout << " Matrix dimension : " << N << "x" << N << std::endl;

    // dynamical allocation (equivalnt of malloc)
    double *A = new double[N*N];
    double *B = new double[N*N];
    double *C = new double[N*N];
    double *S = new double[N*N];

    assign_random_values_to_matrix(A, N);
    assign_random_values_to_matrix(B, N);
    //print_matrix(A, N, "A");
    //print_matrix(B, N, "B");

    matmul_CPU_serial(A, B, S, N);

    #pragma acc data create (A,B,C)
    matmul_openacc(A,B,C);

    #pragma acc data copyout (C)
    if (!check_correctness(C, S))
        std::cout << " ERROR! different solutions" << std::endl;

    return 0;

}