#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE parameters test


#include <boost/test/unit_test.hpp>
#include "../lib/parameter.h"

BOOST_AUTO_TEST_CASE(la) 
{
    const double ret = mc::ret(1.0);
    BOOST_CHECK_EQUAL(ret, 2.0);
}

BOOST_AUTO_TEST_CASE(parameter) 
{
    const mc::constant_param par = mc::constant_param();
    BOOST_CHECK_EQUAL(par.value(), 0.0);
}

BOOST_AUTO_TEST_CASE(parfunc) 
{
    const mc::constant_param par = mc::constant_param();
    const double result = mc::consume_parameter(par);
    BOOST_CHECK_EQUAL(result, 0.0);
}
