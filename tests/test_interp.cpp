//#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE interpolator test


#include <boost/test/unit_test.hpp>
#include "../lib/interpolation/interpolator_base.h"
#include "../lib/interpolation/pwc_interpolator.h"


BOOST_AUTO_TEST_SUITE(interp)
template<template<class> class derived_interp, class extrapolation>
double test_get_value(const utils::base_interp1d<derived_interp, extrapolation>& interp, double t)
{
    return interp.interpolate(t);
};

BOOST_AUTO_TEST_CASE(crtp)
{
    std::vector<double> x{ 0.0, 1.0, 2.0 };
    std::vector<double> f{ -1.0, -3.0, 5.0 };

    const auto interp = utils::pwc_interp<utils::unchecked_boundaries>(x, f);
    const double val = test_get_value(interp, 2.0);
    BOOST_CHECK_EQUAL(val, -3.0);
}

BOOST_AUTO_TEST_CASE(compiletimecheck)
{

//     utils::pwc_interp<utils::unchecked_boundaries>
    auto test2 = utils::is_interp2<utils::pwc_interp<utils::unchecked_boundaries>>::value;
    BOOST_CHECK_EQUAL(test2, true);
    
}

BOOST_AUTO_TEST_CASE(movevectors)
{
    std::vector<double> x{ 0.0, 1.0, 2.0 };
    std::vector<double> f{ -1.0, -3.0, 5.0 };

    const auto interp = utils::pwc_interp<utils::unchecked_boundaries>(std::move(x), std::move(f));
    BOOST_CHECK_EQUAL(x.size(), 0);
    BOOST_CHECK_EQUAL(f.size(), 0);

}



BOOST_AUTO_TEST_CASE(pwc1)
{
    std::vector<double> x{ 0.0, 1.0, 2.0 };
    std::vector<double> f{ -1.0, -3.0, 5.0 };

    const auto interp = utils::pwc_interp<utils::unchecked_boundaries>(x, f);
    BOOST_CHECK_EQUAL(x.size(), 3);
    BOOST_CHECK_EQUAL(f.size(), 3);

    BOOST_CHECK_EQUAL(interp.interpolate(0.0), -1.0);
    BOOST_CHECK_EQUAL(interp.interpolate(1.0), -3.0);
    BOOST_CHECK_EQUAL(interp.interpolate(2.0), -3.0); // TODO: check
}

BOOST_AUTO_TEST_SUITE_END()
