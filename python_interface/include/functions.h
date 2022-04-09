#include <../../random_numbers/include/norm_rng.h>
#include <../../random_numbers/include/unif_rng.h>
#include<../../montecarlo/mc_engine_mt.h>
#include<../../montecarlo/stochastic_processes/geometric_brownian_motion.h>
#include<../../montecarlo/evolution_schemes/euler_scheme.h>
#include<../../montecarlo/utils/stopwatch.h>




std::vector<double> black_scholes_mc(double S, double K, double T, double r, double sigma,
    unsigned int seed, double dt, size_t n_mc, size_t nthreads);

std::vector<double> norm_rand(unsigned int seed, size_t n);
