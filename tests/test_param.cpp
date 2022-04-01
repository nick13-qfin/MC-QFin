#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE parameters test


#include <boost/test/unit_test.hpp>
#include "../lib/parameters/parameters_utils.h"
#include "../lib/interpolation/pwc_interpolator.h"


BOOST_AUTO_TEST_SUITE(parameters)
BOOST_AUTO_TEST_CASE(timedepparm) 
{
    std::vector<double> x{ 0.0, 1.0, 2.0 };
    std::vector<double> f{ -1.0, -3.0, 5.0 };
    const auto par = mc::time_dep_param<utils::pwc_interp<utils::unchecked_boundaries>>(std::move(x), std::move(f));

    const mc::markovian_state state(0.5, std::vector<double>(1));
      BOOST_CHECK_EQUAL(par.value(state), -1.0);
}


BOOST_AUTO_TEST_CASE(movepointer)
{
    std::vector<double> x{ 0.0, 1.0, 2.0 };
    std::vector<double> f{ -1.0, -3.0, 5.0 };

    auto interp = std::make_unique<utils::pwc_interp<utils::unchecked_boundaries>>(std::move(x), std::move(f));

    mc::time_dep_param<utils::pwc_interp<utils::unchecked_boundaries>> par(std::move(interp));

    BOOST_CHECK_EQUAL(interp, nullptr);
    BOOST_CHECK_EQUAL(x.size(), 0);
    BOOST_CHECK_EQUAL(f.size(), 0);
   


}

BOOST_AUTO_TEST_CASE(parameter) 
{
    const mc::constant_param par = mc::constant_param(0.0);
    const mc::markovian_state state(0.0, std::vector<double>(1));
    BOOST_CHECK_EQUAL(par.value(state), 0.0);
}

BOOST_AUTO_TEST_CASE(parfunc) 
{
    const mc::constant_param par = mc::constant_param(0.0);
    const double result = mc::consume_parameter(par);
    BOOST_CHECK_EQUAL(result, 0.0);
}
BOOST_AUTO_TEST_SUITE_END()