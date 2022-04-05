#define BOOST_TEST_MODULE kernell test

#include <boost/test/unit_test.hpp>
#include "../lib/utils/kernells.h"


BOOST_AUTO_TEST_SUITE(kernells)

BOOST_AUTO_TEST_CASE(expkern)
{
    utils::exponential_kernell kern(0.5);
    
    
	BOOST_CHECK_EQUAL(0, 0);
}


BOOST_AUTO_TEST_CASE(qkern)
{
    utils::quartic_kernell kern(0.5);
    
    
	BOOST_CHECK_EQUAL(0, 0);
}




BOOST_AUTO_TEST_SUITE_END()


