#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <../../random_numbers/include/norm_rng.h>
#include <../../random_numbers/include/unif_rng.h>


#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

std::vector<double> norm_rand(unsigned int seed, size_t n) 
{
    rng::normal_inv_rng<rng::mersenne_twister, rng::acklam_inversion> rng{seed };
    std::vector<double> v(static_cast<size_t>(n));
    rng.fill_vector(v, static_cast<size_t>(n));
    return v;
}

namespace py = pybind11;

PYBIND11_MODULE(rand, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: rand
        .. autosummary::
           :toctree: _generate
           norm_rand
           
    )pbdoc";

    m.def("norm_rand", &norm_rand, R"pbdoc(
        Returns a vector of norm(0,1) random numbers
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