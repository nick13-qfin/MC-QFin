#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE hello test


#include <boost/test/unit_test.hpp>
#include "../lib/parameter.h"

BOOST_AUTO_TEST_CASE(la) 
{
    const double ret = lib::ret(1.0);
    BOOST_CHECK_EQUAL(ret, 2.0);
}
