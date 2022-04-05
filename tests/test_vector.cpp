#define BOOST_TEST_MODULE vector test

#include <boost/test/unit_test.hpp>
#include <vector>
#include "../lib/utils/vectors_utils.h"


BOOST_AUTO_TEST_SUITE(vector)

BOOST_AUTO_TEST_CASE(move)
{
	std::vector<double> v{0,1,2};
    
    auto v2 = utils::vector_map(std::move(v), [](double x){return 2*x;});
    
    
	BOOST_CHECK_EQUAL(v.size(), 0);
	BOOST_CHECK_EQUAL(v2.size(), 3);
	BOOST_CHECK_EQUAL(v2[0], 0.0);
	BOOST_CHECK_EQUAL(v2[1], 2.0);
	BOOST_CHECK_EQUAL(v2[2], 4.0);

}

BOOST_AUTO_TEST_CASE(constvec)
{
	const std::vector<double> v{0,1,2};
    
    auto v2 = utils::vector_map(v, [](double x){return 2*x;});
    
    
	BOOST_CHECK_EQUAL(v.size(), 3);
	BOOST_CHECK_EQUAL(v2.size(), 3);
	BOOST_CHECK_EQUAL(v2[0], 0.0);
	BOOST_CHECK_EQUAL(v2[1], 2.0);
	BOOST_CHECK_EQUAL(v2[2], 4.0);

}




BOOST_AUTO_TEST_SUITE_END()

