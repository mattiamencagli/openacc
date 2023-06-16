#include "matmul.h"

int main( int argc, char  **argv){

    int N = std::atoi(argv[1]);
    bool check=false;

    std::cout << " Matrix moltiplication " << std::endl;
    std::cout << " OpenACC - C++ " << std::endl;
    std::cout << " Matrix dimension : " << N << "x" << N << std::endl;

    // dynamical allocation (equivalent of malloc)
    double *A = new double[N*N];
    double *B = new double[N*N];
    double *C = new double[N*N];
    double *S;
    if(check)
        S = new double[N*N];

    assign_random_values_to_matrix(A, N);
    assign_random_values_to_matrix(B, N);
    //print_matrix(A, N, "A");
    //print_matrix(B, N, "B");

    if(check)
        matmul_CPU_serial(A, B, S, N);

    // Single GPU version
    #pragma acc enter data create (A,B,C)
    matmul_openacc_1gpu(A,B,C,N);



    #pragma acc data copyout (C)
    if (check && !check_correctness(C, S, N))
        std::cout << " ERROR! different solutions" << std::endl;

    return 0;

}