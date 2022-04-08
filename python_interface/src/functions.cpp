#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <../../random_numbers/include/norm_rng.h>
#include <../../random_numbers/include/unif_rng.h>
#include<../../montecarlo/mc_engine.h>
#include<../../montecarlo/stochastic_processes/geometric_brownian_motion.h>
#include<../../montecarlo/evolution_schemes/euler_scheme.h>
#include<../../montecarlo/utils/stopwatch.h>


#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

std::vector<double> black_scholes_mc(double S, double K, double T, double r, double sigma,
    unsigned int seed, double dt, size_t n_mc)
{
    using gbm_t = mc::geometric_brownian_motion<mc::constant_param, mc::constant_param>;
    auto gbm = std::make_unique<gbm_t>(r, sigma, S);
    auto scheme = std::make_unique<mc::euler_scheme<gbm_t>>(0, T, dt, std::move(gbm));

    auto mc_engine = mc::make_mcengine(n_mc, std::move(scheme));
    utils::stopwatch sw{};
    mc::dummy_payoff payoff{};
    sw.start();
    auto mcresult = mc_engine.calculate(payoff);
    sw.stop();
    auto value = mcresult.get_estimate();
    auto time = sw.elapsed_millisec();
    std::vector<double> result{ value, time };
    return result;
}


std::vector<double> norm_rand(unsigned int seed, size_t n) 
{
    rng::normal_inv_rng<rng::mersenne_twister, rng::acklam_inversion> rng{seed };
    std::vector<double> v(static_cast<size_t>(n));
    rng.fill_vector(v, static_cast<size_t>(n));
    return v;
}

namespace py = pybind11;

PYBIND11_MODULE(qfin, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: qfin
        .. autosummary::
           :toctree: _generate
           norm_rand
           
    )pbdoc";

    m.def("norm_rand", &norm_rand, R"pbdoc(
        Returns a vector of norm(0,1) random numbers
    )pbdoc");

    m.def("black_scholes_mc", &black_scholes_mc, R"pbdoc(
        Returns a bs call price
    )pbdoc");
    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers
        Some other explanation about the subtract function.
    )pbdoc");

//#ifdef VERSION_INFO
//    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO)
//#else
//    m.attr("__version__") = "dev";
//#endif
}