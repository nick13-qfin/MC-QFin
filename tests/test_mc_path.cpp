#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE mc_path test


#include <boost/test/unit_test.hpp>
#include "../lib/mc_path.h"

BOOST_AUTO_TEST_SUITE(gbm)


BOOST_AUTO_TEST_CASE(parfunc) 
{
    mc::mc_path path(2, 2);
    BOOST_CHECK_EQUAL(0.0, 0.0);
}
BOOST_AUTO_TEST_SUITE_END()
