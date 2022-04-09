#include "../include/functions.h"


std::vector<double> black_scholes_mc(double S, double K, double T, double r, double sigma,
    unsigned int seed, double dt, size_t n_mc, size_t nthreads)
{
    using gbm_t = mc::geometric_brownian_motion<mc::constant_param, mc::constant_param>;
    auto gbm = std::make_unique<gbm_t>(r, sigma, S);
    auto scheme = std::make_unique<mc::euler_scheme<gbm_t>>(0, T, dt, std::move(gbm));

    auto mc_engine = mc::make_mcengine_mt(n_mc, seed, nthreads, std::move(scheme));
    utils::stopwatch sw{};
    mc::dummy_payoff payoff{};
    sw.start();
    mc_engine.calculate(payoff);
    sw.stop();
    auto value = mc_engine.get_result();
    auto mcerr = mc_engine.mc_err();
    auto time = sw.elapsed_millisec();
    std::vector<double> result{ value, mcerr, time };
    return result;
}


std::vector<double> norm_rand(unsigned int seed, size_t n) 
{
    rng::normal_inv_rng<rng::mersenne_twister, rng::acklam_inversion> rng{seed };
    std::vector<double> v(static_cast<size_t>(n));
    rng.fill_vector(v, static_cast<size_t>(n));
    return v;
}

