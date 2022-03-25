#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE state test


#include <boost/test/unit_test.hpp>
#include "../lib/state.h"



BOOST_AUTO_TEST_CASE(state) 
{
    BOOST_CHECK_EQUAL(par.value(), 0.0);
}

BOOST_AUTO_TEST_CASE(parfunc) 
{
    const mc::constant_param par = mc::constant_param();
    const double result = mc::consume_parameter(par);
    BOOST_CHECK_EQUAL(result, 0.0);
}
