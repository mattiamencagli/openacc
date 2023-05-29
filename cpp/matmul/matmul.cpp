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

    assign_fix_values_to_matrix(A, N, 2);
    assign_fix_values_to_matrix(B, N, 3);
    print_matrix(A, N, "A");
    print_matrix(B, N, "B");


    matmul_CPU_serial(A, B, S, N);

    print_matrix(S, N, "S");

    return 0;

}