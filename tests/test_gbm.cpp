
#define BOOST_TEST_MODULE gbm test

#include <boost/test/unit_test.hpp>
#include "../lib/stochastic_processes/geometric_brownian_motion.h"


BOOST_AUTO_TEST_SUITE(gbm)

BOOST_AUTO_TEST_CASE(gbmtest1)
{
	mc::constant_param p();
	mc::geometric_brownian_motion<mc::constant_param, mc::constant_param> a();

	BOOST_CHECK_EQUAL(-3.0, -3.0);

}

BOOST_AUTO_TEST_SUITE_END()