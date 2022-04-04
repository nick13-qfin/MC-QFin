#define BOOST_TEST_MODULE normrng test

#include <boost/test/unit_test.hpp>
#include <../random_numbers/include/norm_rng.h>


BOOST_AUTO_TEST_SUITE(normrng)

BOOST_AUTO_TEST_CASE(test1)
{
    rng::normal_rng rand{ 1 };
    auto a = rand.next();
    auto b = rand.next();
    BOOST_CHECK_EQUAL(0.0, 0.0);

}




BOOST_AUTO_TEST_SUITE_END()
