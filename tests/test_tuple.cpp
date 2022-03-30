#define BOOST_TEST_MODULE tuple test

#include <boost/test/unit_test.hpp>
#include <tuple>

BOOST_AUTO_TEST_SUITE(tuple)

BOOST_AUTO_TEST_CASE(tuple)
{
	double a = 0.1;
	int b = 0;
	double c = 0.2;
	std::tuple t(a, b, c);
	BOOST_CHECK_EQUAL(0.0, 0.0);

}




BOOST_AUTO_TEST_SUITE_END()
