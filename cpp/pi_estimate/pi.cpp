#include "pi.h"

int main(int argc, char  **argv){

    size_t N = std::stof(argv[1]);

    std::cout << " PI estimation with montecarlo " << std::endl;
    std::cout << " OpenACC - C++ " << std::endl;
    std::cout << " number of points : " << N << std::endl;

    // Single GPU version
    double PI_m = montecarlo_pi(N);

    check_correctness(PI_m);
    
	return 0;

}
