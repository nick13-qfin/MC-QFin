#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../include/functions.h"


#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


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