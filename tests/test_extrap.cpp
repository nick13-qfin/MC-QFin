//#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE extrapolation test


#include <boost/test/unit_test.hpp>
#include <../interpolation/include/flat_extrapolation.h>


BOOST_AUTO_TEST_SUITE(extrap)


BOOST_AUTO_TEST_CASE(flat)
{
    std::vector<double> x{ 0.0, 1.0, 2.0 };
    std::vector<double> f{ -1.0, -3.0, 5.0 };

    //std::vector is a interp::vector_type
    static_assert(interp::vector_type<std::vector<double>>);
    //double is not
    static_assert(!interp::vector_type<double>);

    const auto extrap = interp::flat_extrap();
    const double val = extrap.left_extrap(0.0, x, f);
    BOOST_CHECK_EQUAL(val, f.front());
}




BOOST_AUTO_TEST_SUITE_END()
